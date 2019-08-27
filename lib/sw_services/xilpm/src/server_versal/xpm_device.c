/******************************************************************************
*
* Copyright (C) 2018-2019 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
*
*
******************************************************************************/
#include "xplmi_dma.h"
#include "xpm_device.h"
#include "xpm_core.h"
#include "xpm_regs.h"
#include "xpm_prot.h"
#include "xpm_rpucore.h"
#include "xpm_notifier.h"
#include "xpm_api.h"
#include "xpm_pslpdomain.h"

/** PSM RAM Base address */
#define XPM_PSM_RAM_BASE_ADDR           (0xFFC00000U)
#define XPM_PSM_RAM_SIZE                (0x40000U)

const char *PmDevStates[] = {
	"UNUSED",
	"RUNNING",
	"PWR_ON",
	"CLK_ON",
	"RST_OFF",
	"RST_ON",
	"CLK_OFF",
	"PWR_OFF",
	"SUSPENDING",
	"RUNTIME_SUSPEND",
};

const char *PmDevEvents[] = {
	"BRINGUP_ALL",
	"BRINGUP_CLKRST",
	"SHUTDOWN",
	"TIMER",
};

static XPm_DeviceOps PmDeviceOps;
static XPm_Device *PmDevices[XPM_NODEIDX_DEV_MAX];
static u32 MaxDevices = XPM_NODEIDX_DEV_MAX;
static u32 PmNumDevices;

static const XPm_StateCap XPmGenericDeviceStates[] = {
	{
		.State = XPM_DEVSTATE_UNUSED,
		.Cap = XPM_MIN_CAPABILITY,
	}, {
		.State = XPM_DEVSTATE_RUNTIME_SUSPEND,
		.Cap = PM_CAP_UNUSABLE,
	}, {
		.State = XPM_DEVSTATE_RUNNING,
		.Cap = XPM_MAX_CAPABILITY | PM_CAP_UNUSABLE,
	},
};

static const XPm_StateTran XPmGenericDevTransitions[] = {
	{
		.FromState = XPM_DEVSTATE_RUNNING,
		.ToState = XPM_DEVSTATE_UNUSED,
		.Latency = XPM_DEF_LATENCY,
	}, {
		.FromState = XPM_DEVSTATE_UNUSED,
		.ToState = XPM_DEVSTATE_RUNNING,
		.Latency = XPM_DEF_LATENCY,
	}, {
		.FromState = XPM_DEVSTATE_RUNTIME_SUSPEND,
		.ToState = XPM_DEVSTATE_UNUSED,
		.Latency = XPM_DEF_LATENCY,
	}, {
		.FromState = XPM_DEVSTATE_RUNTIME_SUSPEND,
		.ToState = XPM_DEVSTATE_RUNNING,
		.Latency = XPM_DEF_LATENCY,
	}, {
		.FromState = XPM_DEVSTATE_UNUSED,
		.ToState = XPM_DEVSTATE_RUNTIME_SUSPEND,
		.Latency = XPM_DEF_LATENCY,
	}, {
		.FromState = XPM_DEVSTATE_RUNNING,
		.ToState = XPM_DEVSTATE_RUNTIME_SUSPEND,
		.Latency = XPM_DEF_LATENCY,
	},
};

static XPm_Requirement *FindReqm(XPm_Device *Device, XPm_Subsystem *Subsystem)
{
	XPm_Requirement *Reqm = NULL;

	Reqm = Device->Requirements;
	while (NULL != Reqm) {
		if (Reqm->Subsystem == Subsystem) {
			break;
		}
		Reqm = Reqm->NextSubsystem;
	}

	return Reqm;
}

static XStatus SetDeviceNode(u32 Id, XPm_Device *Device)
{
	u32 Status = XST_INVALID_PARAM;
	u32 NodeIndex = NODEINDEX(Id);

	/*
	 * We assume that the Node ID class, subclass and type has _already_
	 * been validated before, so only check bounds here against index
	 */
	if ((NULL != Device) && (XPM_NODEIDX_DEV_MAX > NodeIndex)) {
		PmDevices[NodeIndex] = Device;
		PmNumDevices++;
		Status = XST_SUCCESS;
	}

	return Status;
}

/****************************************************************************/
/**
 * @brief	Get subsystem ID of processor
 *
 * @param  Device	Processor whose subsystem needs to found
 *
 * @return	Subsystem ID of that processor
 *
 * @note	Core must be requested from single subsystem. If it is
 *		requested from multiple subsystems then it returns only one
 *		subsystem ID and if it is not requested from any subsystem
 *		then this function returns maximum subsystem ID which is
 *		invalid.
 *
 ****************************************************************************/
u32 XPmDevice_GetSubsystemIdOfCore(XPm_Device *Device)
{
	XPm_Requirement *Reqm;
	XPm_Subsystem *Subsystem = NULL;
	u32 Idx, SubSystemId;

	for (Idx = 0; Idx < XPM_NODEIDX_SUBSYS_MAX; Idx++) {
		Subsystem = XPmSubsystem_GetByIndex(Idx);
		Reqm = FindReqm(Device, Subsystem);
		if ((NULL != Reqm) && (TRUE == Reqm->Allocated)) {
			break;
		}
	}

	if(Idx == XPM_NODEIDX_SUBSYS_MAX) {
		SubSystemId = INVALID_SUBSYSID;
	} else {
		SubSystemId = Subsystem->Id;
	}

	return SubSystemId;
}

/****************************************************************************/
/**
 * @brief	Get maximum of all requested capabilities of device
 * @param Device	Device whose maximum required capabilities should be
 *			determined
 *
 * @return	32bit value encoding the capabilities
 *
 * @note	None
 *
 ****************************************************************************/
static u32 GetMaxCapabilities(const XPm_Device* const Device)
{
	XPm_Requirement* Reqm = Device->Requirements;
	u32 MaxCaps = 0U;

	while (NULL != Reqm) {
		MaxCaps |= Reqm->Curr.Capabilities;
		Reqm = Reqm->NextSubsystem;
	}

	return MaxCaps;
}

/****************************************************************************/
/**
 * @brief  This function checks device capability
 *
 * @param Device	Device for capability check
 * @param Caps		Capability
 *
 * @return XST_SUCCESS if desired Caps is available in Device
 *
 * @note   None
 *
 ****************************************************************************/
XStatus XPm_CheckCapabilities(XPm_Device *Device, u32 Caps)
{
	u32 Idx;
	u32 Status = XST_FAILURE;

	if (NULL == Device->DeviceFsm) {
		goto done;
	}

	for (Idx = 0U; Idx < Device->DeviceFsm->StatesCnt; Idx++) {
		/* Find the first state that contains all capabilities */
		if ((Caps & Device->DeviceFsm->States[Idx].Cap) == Caps) {
			Status = XST_SUCCESS;
			break;
		}
	}

done:
	if (Status != XST_SUCCESS) {
		Status = XPM_NO_PERMISSION;
	}
	return Status;
}

static u32 IsRunning(XPm_Device *Device)
{
	u32 Running = 0;
	XPm_Requirement *Reqm = Device->Requirements;

	while (NULL != Reqm) {
		if (Reqm->Allocated > 0) {
			if (Reqm->Curr.Capabilities > 0) {
				Running = 1;
				break;
			}
		}
		Reqm = Reqm->NextSubsystem;
	}

	return Running;
}

XStatus XPmDevice_BringUp(XPm_Node *Node)
{
	u32 Status = XPM_ERR_DEVICE_BRINGUP;
	XPm_Device *Device = (XPm_Device *)Node;

	if (NULL == Device->Power) {
		goto done;
	}

	/* Check if device is already up and running */
	if(Node->State == XPM_DEVSTATE_RUNNING)
	{
		Status = XST_SUCCESS;
		goto done;
	}

	Device->WfPwrUseCnt = Device->Power->UseCount + 1;
	Status = Device->Power->Node.HandleEvent(
		&Device->Power->Node, XPM_POWER_EVENT_PWR_UP);
	if (XST_SUCCESS == Status) {
		Node->State = XPM_DEVSTATE_PWR_ON;
		/* Todo: Start timer to poll the power node */
		/* Hack */
		Status = Node->HandleEvent(Node, XPM_DEVEVENT_TIMER);
	}

done:
	return Status;
}

static XStatus SetClocks(XPm_Device *Device, u32 Enable)
{
	XPm_ClockHandle *ClkHandle = Device->ClkHandles;

	/* Enable all the clock gates, skip over others */
	if (TRUE == Enable) {
		XPmClock_Request(ClkHandle);
	} else {
		XPmClock_Release(ClkHandle);
	}

	return XST_SUCCESS;
}

static XStatus HandleDeviceEvent(XPm_Node *Node, u32 Event)
{
	u32 Status = XST_FAILURE;
	XPm_Device *Device = (XPm_Device *)Node;

	PmDbg("State=%s, Event=%s\n\r", PmDevStates[Node->State], PmDevEvents[Event]);

	switch(Node->State)
	{
		case XPM_DEVSTATE_UNUSED:
			if (XPM_DEVEVENT_BRINGUP_ALL == Event) {
				Status = Device->DeviceFsm->EnterState(Device, XPM_DEVSTATE_RUNNING);
			} else if (XPM_DEVEVENT_SHUTDOWN == Event) {
				Status = XST_SUCCESS;
			}
			break;
		case XPM_DEVSTATE_PWR_ON:
			if (XPM_DEVEVENT_TIMER == Event) {
				Status = XST_SUCCESS;
				if (Device->WfPwrUseCnt == Device->Power->UseCount) {
					Node->State = XPM_DEVSTATE_CLK_ON;
					/* Enable clock */
					Status = SetClocks(Device, TRUE);
					if (XST_SUCCESS != Status) {
						break;
					}
					/* Todo: Start timer to poll the clock node */
					/* Hack */
					Status = Node->HandleEvent(Node, XPM_DEVEVENT_TIMER);
				} else {
					/* Todo: Start timer to poll the power node */
				}
			} else {
				Status = XST_DEVICE_BUSY;
			}
			break;
		case XPM_DEVSTATE_CLK_ON:
			if (XPM_DEVEVENT_TIMER == Event) {
				Status = XST_SUCCESS;
				/* Todo: Check if clock is enabled */
				if (1 /* Hack: Clock enabled */) {
					Node->State = XPM_DEVSTATE_RST_OFF;

					XPm_PsLpDomain *PsLpd;
					PsLpd = (XPm_PsLpDomain *)XPmPower_GetById(XPM_POWERID_LPD);
					if (NULL == PsLpd) {
						Status = XST_FAILURE;
						break;
					}

					/*
					 * Configure ADMA as non-secure so Linux
					 * can use it.
					 * TODO: Remove this when security config
					 * support is added through CDO
					 */
					if (Device->Node.Id >= XPM_DEVID_ADMA_0 &&
							Device->Node.Id <= XPM_DEVID_ADMA_7) {
						XPm_Out32(PsLpd->LpdSlcrSecureBaseAddr +
							  LPD_SLCR_SECURE_WPROT0_OFFSET, 0x0);
						XPm_Out32(PsLpd->LpdSlcrSecureBaseAddr +
							  LPD_SLCR_SECURE_ADMA_0_OFFSET +
							  (Device->Node.Id - XPM_DEVID_ADMA_0) * 4, 0x1);
						XPm_Out32(PsLpd->LpdSlcrSecureBaseAddr +
							  LPD_SLCR_SECURE_WPROT0_OFFSET, 0x1);
					}

					/* De-assert reset for peripheral devices */
					if (XPM_NODESUBCL_DEV_PERIPH ==
						NODESUBCLASS(Device->Node.Id)) {
						Status = XPmDevice_Reset(Device,
							PM_RESET_ACTION_RELEASE);
						if (XST_SUCCESS != Status) {
							break;
						}
					} else if(Node->Id == XPM_DEVID_R50_0 || Node->Id == XPM_DEVID_R50_1) {
						/*RPU has a special handling */
						XPmRpuCore_Halt(Device);
					} else if(Node->Id == XPM_DEVID_PSM) {
						/* Ecc initialize PSM RAM*/
						XPlmi_EccInit(XPM_PSM_RAM_BASE_ADDR, XPM_PSM_RAM_SIZE);
					}
					/* Todo: Start timer to poll the reset node */
					/* Hack */
					Status = Node->HandleEvent(Node, XPM_DEVEVENT_TIMER);
				} else {
					/* Todo: Start timer to poll the clock node */
				}
			} else {
				Status = XST_DEVICE_BUSY;
			}
			break;
		case XPM_DEVSTATE_RST_OFF:
			if (XPM_DEVEVENT_TIMER == Event) {
				Status = XST_SUCCESS;
				/* Todo: Check if reset is de-asserted */
				if (1 /* Hack: Reset de-asserted */) {
					XPm_RequiremntUpdate(Device->PendingReqm);
					Node->State = XPM_DEVSTATE_RUNNING;
					Device->PendingReqm = NULL;
				} else {
					/* Todo: Start timer to poll the reset node */
				}
			} else {
				Status = XST_DEVICE_BUSY;
			}
			break;
		case XPM_DEVSTATE_RUNNING:
			if (XPM_DEVEVENT_BRINGUP_ALL == Event) {
				Status = XPmDevice_BringUp(Node);
			} else if (XPM_DEVEVENT_BRINGUP_CLKRST == Event) {
				Node->State = XPM_DEVSTATE_CLK_ON;
				/* Enable all clocks */
				Status = SetClocks(Device, TRUE);
				if (XST_SUCCESS != Status) {
					break;
				}
				/* Todo: Start timer to poll the clock node */
				/* Hack */
				Status = Node->HandleEvent(Node, XPM_DEVEVENT_TIMER);
			} else if (XPM_DEVEVENT_SHUTDOWN == Event) {
				Node->State = XPM_DEVSTATE_RST_ON;
				/* Assert reset for peripheral devices */
				if (XPM_NODESUBCL_DEV_PERIPH ==
						NODESUBCLASS(Device->Node.Id)) {
					Status = XPmDevice_Reset(Device,
							PM_RESET_ACTION_ASSERT);
					if (XST_SUCCESS != Status) {
						break;
					}
				}
				/* Todo: Start timer to poll reset node */
				/* Hack */
				Status = Node->HandleEvent(Node, XPM_DEVEVENT_TIMER);
			} else if (XPM_DEVEVENT_RUNTIME_SUSPEND == Event) {
				Node->State = XPM_DEVSTATE_RUNTIME_SUSPEND;
				/* Disable all clocks */
				Status = SetClocks(Device, FALSE);
				if (XST_SUCCESS != Status) {
					break;
				}
			} else {
				/* Required by MISRA */
			}
			break;
		case XPM_DEVSTATE_RST_ON:
			if (XPM_DEVEVENT_TIMER == Event) {
				Status = XST_SUCCESS;
				/* Todo: Check if reset is asserted */
				if (1 /* Hack: asserted */) {
					Node->State = XPM_DEVSTATE_CLK_OFF;
					/* Disable all clocks */
					Status = SetClocks(Device, FALSE);
					if (XST_SUCCESS != Status) {
						break;
					}
					/* Todo: Start timer to poll clock node */
					/* Hack */
					Status = Node->HandleEvent(Node, XPM_DEVEVENT_TIMER);
				} else {
					/* Todo: Start timer to poll reset node */
				}
			}
			break;
		case XPM_DEVSTATE_CLK_OFF:
			if (XPM_DEVEVENT_TIMER == Event) {
				Status = XST_SUCCESS;
				/* Todo: Check if clock is disabled */
				if (1 /* Hack: Clock disabled */) {
					Node->State = XPM_DEVSTATE_PWR_OFF;
					Device->WfPwrUseCnt = Device->Power->UseCount - 1U;
					Status = Device->Power->Node.HandleEvent(
						&Device->Power->Node, XPM_POWER_EVENT_PWR_DOWN);
					/* Todo: Start timer to poll power node use count */
					/* Hack */
					Status = Node->HandleEvent(Node, XPM_DEVEVENT_TIMER);
				} else {
					/* Todo: Start timer to poll clock node */
				}
			}
			break;
		case XPM_DEVSTATE_PWR_OFF:
			if (XPM_DEVEVENT_TIMER == Event) {
				Status = XST_SUCCESS;
				Device->Node.Flags &= ~NODE_IDLE_DONE;
				if (Device->WfPwrUseCnt == Device->Power->UseCount) {
					if (Device->WfDealloc) {
						Device->PendingReqm->Allocated = 0;
						Device->WfDealloc = 0;
					}
					if(Device->PendingReqm != NULL) {
						XPm_RequiremntUpdate(Device->PendingReqm);
						Device->PendingReqm = NULL;
					}
					if (0 == IsRunning(Device)) {
						Node->State = XPM_DEVSTATE_UNUSED;
					} else {
						Node->State = XPM_DEVSTATE_RUNNING;
					}
				} else {
					/* Todo: Start timer to poll power node use count */
				}
			} else if (XPM_DEVEVENT_SHUTDOWN == Event) {
				/* Device is already in power off state */
				Status = XST_SUCCESS;
			}
			break;
		case XPM_DEVSTATE_RUNTIME_SUSPEND:
			if (XPM_DEVEVENT_SHUTDOWN == Event) {
				/* Assert reset for peripheral devices */
				if (XPM_NODESUBCL_DEV_PERIPH ==
						NODESUBCLASS(Device->Node.Id)) {
					Status = XPmDevice_Reset(Device,
							PM_RESET_ACTION_ASSERT);
					if (XST_SUCCESS != Status) {
						break;
					}
				}
				/*
				 * Change device's state to clock off since all
				 * clocks are disabled during runtime suspend.
				 */
				Node->State = XPM_DEVSTATE_CLK_OFF;
				Status = Node->HandleEvent(Node, XPM_DEVEVENT_TIMER);
			} else if (XPM_DEVEVENT_BRINGUP_ALL == Event) {
				/* Enable all clocks */
				Status = SetClocks(Device, TRUE);
				if (XST_SUCCESS != Status) {
					break;
				}
				Node->State = XPM_DEVSTATE_RUNNING;
			} else {
				/* Required by MISRA */
			}
			break;
		default:
			Status = XPM_INVALID_STATE;
			break;
	}

	if(Status != XST_SUCCESS) {
		PmErr("Returned: 0x%x\n\r", Status);
	}
	return Status;
}

static XStatus HandleDeviceState(XPm_Device* const Device, const u32 NextState)
{
	XStatus Status = XST_SUCCESS;

	switch (Device->Node.State) {
	case XPM_DEVSTATE_UNUSED:
		if (XPM_DEVSTATE_RUNNING == NextState) {
			Status = XPmDevice_BringUp(&Device->Node);
		}
		break;
	case XPM_DEVSTATE_RUNNING:
		if (XPM_DEVSTATE_UNUSED == NextState) {
			Status = Device->Node.HandleEvent((XPm_Node *)Device,
							  XPM_DEVEVENT_SHUTDOWN);
		} else if (XPM_DEVSTATE_RUNTIME_SUSPEND == NextState) {
			Status = Device->Node.HandleEvent((XPm_Node *)Device,
							  XPM_DEVEVENT_RUNTIME_SUSPEND);
		} else {
			/* Required by MISRA */
		}
		break;
	case XPM_DEVSTATE_RUNTIME_SUSPEND:
		if (XPM_DEVSTATE_RUNNING == NextState) {
			Status = Device->Node.HandleEvent((XPm_Node *)Device,
							  XPM_DEVEVENT_BRINGUP_ALL);
		} else if (XPM_DEVSTATE_UNUSED == NextState) {
			Status = Device->Node.HandleEvent((XPm_Node *)Device,
							  XPM_DEVEVENT_SHUTDOWN);
		} else {
			/* Required by MISRA */
		}
		break;
	default:
		Status = XPM_INVALID_STATE;
		break;
	}

	if(Status != XST_SUCCESS) {
		PmErr("Returned: 0x%x\n\r", Status);
	}
	return Status;
}

static const XPm_DeviceFsm XPmGenericDeviceFsm = {
	DEFINE_DEV_STATES(XPmGenericDeviceStates),
	DEFINE_DEV_TRANS(XPmGenericDevTransitions),
	.EnterState = HandleDeviceState,
};

static XStatus Request(XPm_Device *Device, XPm_Subsystem *Subsystem,
		       u32 Capabilities, const u32 QoS)
{
	u32 Status = XPM_ERR_DEVICE_REQ;
	XPm_Requirement *Reqm;
	u32 UsagePolicy = 0;
	if ((XPM_DEVSTATE_UNUSED != Device->Node.State) &&
		(XPM_DEVSTATE_RUNNING != Device->Node.State) &&
		(XPM_DEVSTATE_RUNTIME_SUSPEND != Device->Node.State)) {
			Status = XST_DEVICE_BUSY;
			goto done;
	}

	/* Check whether this device assigned to the subsystem */
	Reqm = FindReqm(Device, Subsystem);
	if (NULL == Reqm) {
		goto done;
	}

	if (1 == Reqm->Allocated) {
		Status = XST_SUCCESS;
		goto done;
	}

	/* Check whether this device is shareable */
	UsagePolicy = Reqm->Flags & REG_FLAGS_USAGE_MASK;
	if (UsagePolicy == REQ_TIME_SHARED) {
			//Check if it already requested by other subsystem. If yes, return
			XPm_Requirement *NextReqm = Reqm->NextSubsystem;
			while (NULL != NextReqm) {
				if (TRUE == NextReqm->Allocated) {
					Status = XST_FAILURE;
					goto done;
				}
				NextReqm = NextReqm->NextSubsystem;
			}
	}

	/* Allocated device for the subsystem */
	Reqm->Allocated = 1;

	Status = Device->DeviceOps->SetRequirement(Device, Subsystem,
						   Capabilities, QoS);

	if (XST_SUCCESS != Status) {
		goto done;
	}

	Status = XPmProt_Configure(Reqm, TRUE);

done:
	if(Status != XST_SUCCESS) {
		PmErr("Returned: 0x%x\n\r", Status);
	}
	return Status;
}

static XStatus SetRequirement(XPm_Device *Device, XPm_Subsystem *Subsystem,
			      u32 Capabilities, const u32 QoS)
{
	u32 Status = XPM_ERR_SET_REQ;;
	XPm_ReqmInfo TempReqm;

	if ((XPM_DEVSTATE_UNUSED != Device->Node.State) &&
		(XPM_DEVSTATE_RUNNING != Device->Node.State) &&
		(XPM_DEVSTATE_RUNTIME_SUSPEND != Device->Node.State)) {
			Status = XST_DEVICE_BUSY;
			goto done;
	}

	Device->PendingReqm = FindReqm(Device, Subsystem);
	if (NULL == Device->PendingReqm) {
		goto done;
	}

	/*
	 * If subsystem state is suspending then do not change device's state
	 * according to capabilities, only schedule requirements by setting
	 * device's next requirements.
	 */
	if (SUSPENDING == Subsystem->State) {
		Device->PendingReqm->Next.Capabilities = Capabilities;
		Device->PendingReqm->Next.QoS = QoS;
		Status = XST_SUCCESS;
		goto done;
	} else {
		/*
		 * Store current requirements as a backup in case something
		 * fails.
		 */
		TempReqm.Capabilities = Device->PendingReqm->Curr.Capabilities;
		TempReqm.QoS = Device->PendingReqm->Curr.QoS;

		Device->PendingReqm->Curr.Capabilities = Capabilities;
		Device->PendingReqm->Curr.QoS = QoS;
	}

	Status = XPmDevice_UpdateStatus(Device);

	if (XST_SUCCESS != Status) {
		Device->PendingReqm->Curr.Capabilities = TempReqm.Capabilities;
		Device->PendingReqm->Curr.QoS = TempReqm.QoS;
	} else if (PM_CAP_UNUSABLE == Capabilities) {
		/* Schedual next requirement to 0 */
		Device->PendingReqm->Next.Capabilities = 0;
		Device->PendingReqm->Next.QoS = QoS;
	} else {
		XPm_RequiremntUpdate(Device->PendingReqm);
	}

done:
	if(Status != XST_SUCCESS) {
		PmErr("Returned: 0x%x\n\r", Status);
	}
	return Status;
}

static XStatus Release(XPm_Device *Device,
		XPm_Subsystem *Subsystem)
{
	u32 Status = XPM_ERR_DEVICE_RELEASE;

	if ((XPM_DEVSTATE_UNUSED != Device->Node.State) &&
		(XPM_DEVSTATE_RUNNING != Device->Node.State) &&
		(XPM_DEVSTATE_RUNTIME_SUSPEND != Device->Node.State)) {
			Status = XST_DEVICE_BUSY;
			goto done;
	}

	Device->PendingReqm = FindReqm(Device, Subsystem);
	if (NULL == Device->PendingReqm) {
		goto done;
	}

	if (0 == Device->PendingReqm->Allocated) {
		Status = XST_SUCCESS;
		goto done;
	}

	Device->WfDealloc = 1;

	Status = Device->DeviceOps->SetRequirement(Device, Subsystem, 0,
						   XPM_DEF_QOS);

	if (XST_SUCCESS == Status) {
		XPmRequirement_Clear(Device->PendingReqm);
		Device->WfDealloc = 0;
	}
	else {
		Status = XPM_ERR_DEVICE_RELEASE;
	}

	Status = XPmProt_Configure(Device->PendingReqm, FALSE);

done:
	if(Status != XST_SUCCESS) {
		PmErr("Returned: 0x%x\n\r", Status);
	}
	return Status;
}

XStatus XPmDevice_Init(XPm_Device *Device,
		u32 Id,
		u32 BaseAddress,
		XPm_Power *Power, XPm_ClockNode * Clock, XPm_ResetNode *Reset)
{
	XStatus Status = XPM_ERR_DEVICE_INIT;

	if (NULL != XPmDevice_GetById(Id)) {
		Status = XST_DEVICE_BUSY;
		goto done;
	}

	Status = XPmNode_Init(&Device->Node,
		Id, XPM_DEVSTATE_UNUSED, BaseAddress);
	if (XST_SUCCESS != Status) {
		goto done;
	}

	/* Add requirement by default for PMC subsystem */
	Status = XPmRequirement_Add(XPmSubsystem_GetByIndex(XPM_NODEIDX_SUBSYS_PMC), Device, ((REQ_ACCESS_SECURE_NONSECURE << REG_FLAGS_SECURITY_OFFSET) |REQ_NO_RESTRICTION), NULL, 0);
	if (XST_SUCCESS != Status) {
		goto done;
	}

	Device->Power = Power;
	Device->PendingReqm = NULL;
	Device->WfDealloc = 0;
	Device->WfPwrUseCnt = 0;

	Status = XPmDevice_AddClock(Device, Clock);
	if (XST_SUCCESS != Status) {
		goto done;
	}

	Status = XPmDevice_AddReset(Device, Reset);
	if (XST_SUCCESS != Status) {
		goto done;
	}

	Device->Node.HandleEvent = HandleDeviceEvent;

	PmDeviceOps.Request = Request;
	PmDeviceOps.SetRequirement = SetRequirement;
	PmDeviceOps.Release = Release;
	Device->DeviceOps = &PmDeviceOps;
	if (NULL == Device->DeviceFsm)
		Device->DeviceFsm = &XPmGenericDeviceFsm;

	Status = SetDeviceNode(Id, Device);
	if (XST_SUCCESS != Status) {
		goto done;
	}
	Status = XST_SUCCESS;

done:
	if(Status != XST_SUCCESS) {
		PmErr("Returned: 0x%x\n\r", Status);
	}
	return Status;
}


XStatus XPmDevice_AddClock(XPm_Device *Device, XPm_ClockNode *Clock)
{
	XStatus Status = XST_SUCCESS;
	XPm_ClockHandle *ClkHandle;

	if (NULL == Device) {
		Status = XPM_ERR_DEVICE;
		goto done;
	}

	if (NULL == Clock) {
		goto done;
	}

	ClkHandle = (XPm_ClockHandle *)XPm_AllocBytes(sizeof(XPm_ClockHandle));
	if (NULL == ClkHandle) {
		Status = XST_BUFFER_TOO_SMALL;
                goto done;
	}

	ClkHandle->Clock = Clock;
	ClkHandle->Device = Device;

	/* Prepend the new handle to the device's clock handle list */
	ClkHandle->NextClock = Device->ClkHandles;
	Device->ClkHandles = ClkHandle;

	/* Prepend the new handle to the clock's device handle list */
	ClkHandle->NextDevice = Clock->ClkHandles;
	Clock->ClkHandles = ClkHandle;

done:
	if(Status != XST_SUCCESS) {
		PmErr("Returned: 0x%x\n\r", Status);
	}
	return Status;
}

XStatus XPmDevice_AddReset(XPm_Device *Device, XPm_ResetNode *Reset)
{
	u32 Status = XST_SUCCESS;
	XPm_ResetHandle *RstHandle;

	if (NULL == Device) {
		Status = XPM_ERR_DEVICE;
		goto done;
	}

	if (NULL == Reset) {
		goto done;
	}

	RstHandle = (XPm_ResetHandle *)XPm_AllocBytes(sizeof(XPm_ResetHandle));
	if (NULL == RstHandle) {
		Status = XST_BUFFER_TOO_SMALL;
		goto done;
	}

	RstHandle->Reset = Reset;
	RstHandle->Device = Device;

	/* Prepend the new handle to the device's reset handle list */
	RstHandle->NextReset = Device->RstHandles;
	Device->RstHandles = RstHandle;

	/* Prepend the new handle to the reset's device handle list */
	RstHandle->NextDevice = Reset->RstHandles;
	Reset->RstHandles = RstHandle;

done:
	if(Status != XST_SUCCESS) {
		PmErr("Returned: 0x%x\n\r", Status);
	}
	return Status;
}

XStatus XPmDevice_Reset(XPm_Device *Device, const XPm_ResetActions Action)
{
	u32 Status = XST_SUCCESS;
	XPm_ResetHandle *RstHandle;

	if (NULL == Device) {
		Status = XPM_ERR_DEVICE;
		goto done;
	}

	RstHandle = Device->RstHandles;
	while (NULL != RstHandle) {
		RstHandle->Reset->Ops->SetState(RstHandle->Reset, Action);
		RstHandle = RstHandle->NextReset;
	}

done:
	if(Status != XST_SUCCESS) {
		PmErr("Returned: 0x%x\n\r", Status);
	}
	return Status;
}

int XPmDevice_CheckPermissions(XPm_Subsystem *Subsystem, u32 DeviceId)
{
	int Status = XST_FAILURE;
	XPm_Requirement *Reqm;
	XPm_Device *Device = XPmDevice_GetById(DeviceId);

	if (NULL == Device) {
		Status = XST_INVALID_PARAM;
		goto done;
	}

	Reqm = FindReqm(Device, Subsystem);
	if (NULL == Reqm) {
		goto done;
	}

	if (TRUE == Reqm->Allocated) {
		Status = XST_SUCCESS;
		goto done;
	}

done:
	if(Status != XST_SUCCESS) {
		PmErr("Returned: 0x%x\n\r", Status);
	}
	return Status;
}

/****************************************************************************/
/**
 * @brief	Get handle to requested device node by "complete" Node ID
 *
 * @param DeviceId	Device Node ID
 *
 * @return	Pointer to requested XPm_Device
 *              NULL otherwise
 *
 * @note	Requires Complete Node ID
 *
 ****************************************************************************/
XPm_Device *XPmDevice_GetById(const u32 DeviceId)
{
	XPm_Device *Device = NULL;

	if ((XPM_NODECLASS_DEVICE != NODECLASS(DeviceId)) ||
	    (XPM_NODEIDX_DEV_MAX <= NODEINDEX(DeviceId))) {
		goto done;
	}

	Device = PmDevices[NODEINDEX(DeviceId)];
	/* Check that Device's ID is same as given ID or not. */
	if ((NULL != Device) && (DeviceId != Device->Node.Id)) {
		Device = NULL;
	}

done:
	return Device;
}

/****************************************************************************/
/**
 * @brief	Get handle to requested device node by "only" Node INDEX
 *
 * @param DeviceIndex	Device Node Index
 *
 * @return	Pointer to requested XPm_Device, NULL otherwise
 *
 * @note	Requires ONLY Node Index
 *
 * Caller should be _careful_ while using this function as it skips the checks
 * for validating the class, subclass and type of the device before and after
 * retrieving the node from the database. Use this only where it is absolutely
 * necessary, otherwise use XPmDevice_GetById() which is more strict
 * and requires 'complete' Node ID for retrieving the handle.
 *
 ****************************************************************************/
XPm_Device *XPmDevice_GetByIndex(const u32 DeviceIndex)
{
	XPm_Device *Device = NULL;
	/* Make sure we are working with only Index. */
	u32 Index = (DeviceIndex & NODE_INDEX_MASK);

	if (XPM_NODEIDX_DEV_MAX <= Index) {
		goto done;
	}

	Device = PmDevices[Index];
	/* Check that Device's Index is same as given Index or not. */
	if ((NULL != Device) && (Index != NODEINDEX(Device->Node.Id))) {
		Device = NULL;
	}

done:
	return Device;
}


XStatus XPmDevice_Request(const u32 SubsystemId,
			const u32 DeviceId,
			const u32 Capabilities,
			const u32 QoS)
{
	u32 Status = XPM_ERR_DEVICE_REQ;
	XPm_Device *Device;
	XPm_Subsystem *Subsystem;

	/* Todo: Check if policy allows this request */

	if (XPM_NODECLASS_DEVICE != NODECLASS(DeviceId)) {
		Status = XPM_INVALID_DEVICEID;
		goto done;
	}

	Device = XPmDevice_GetById(DeviceId);
	if (NULL == Device) {
		Status = XPM_INVALID_DEVICEID;
		goto done;
	}

	if (Device->Node.Id != DeviceId) {
		Status = XPM_INVALID_DEVICEID;
		goto done;
	}

	Subsystem = XPmSubsystem_GetById(SubsystemId);
	if (Subsystem == NULL || Subsystem->State != ONLINE) {
		Status = XPM_INVALID_SUBSYSID;
		goto done;
	}

	Status = Device->DeviceOps->Request(Device, Subsystem, Capabilities,
					    QoS);
done:
	if(Status != XST_SUCCESS) {
		PmErr("Returned: 0x%x\n\r", Status);
	}
	return Status;
}

XStatus XPmDevice_Release(const u32 SubsystemId, const u32 DeviceId)
{
	u32 Status = XPM_ERR_DEVICE_RELEASE;
	XPm_Device *Device;
	XPm_Subsystem *Subsystem;

	/* Todo: Check if subsystem has permission */

	if (XPM_NODECLASS_DEVICE != NODECLASS(DeviceId)) {
		Status = XPM_INVALID_DEVICEID;
		goto done;
	}

	Device = XPmDevice_GetById(DeviceId);
	if (NULL == Device) {
		Status = XPM_INVALID_DEVICEID;
		goto done;
	}

	if (Device->Node.Id != DeviceId) {
		Status = XPM_INVALID_DEVICEID;
		goto done;
	}

	Subsystem = XPmSubsystem_GetById(SubsystemId);
	if (Subsystem == NULL || Subsystem->State != ONLINE) {
		Status = XPM_INVALID_SUBSYSID;
		goto done;
	}

	Status = Device->DeviceOps->Release(Device, Subsystem);

done:
	if(Status != XST_SUCCESS) {
		PmErr("Returned: 0x%x\n\r", Status);
	}
	return Status;
}

XStatus XPmDevice_SetRequirement(const u32 SubsystemId, const u32 DeviceId,
				 const u32 Capabilities, const u32 QoS)
{
	u32 Status = XPM_ERR_SET_REQ;
	XPm_Device *Device;
	XPm_Subsystem *Subsystem;

	/* Todo: Check if subsystem has permission */

	if (XPM_NODECLASS_DEVICE != NODECLASS(DeviceId)) {
		Status = XPM_INVALID_DEVICEID;
		goto done;
	}

	Device = XPmDevice_GetById(DeviceId);
	if (NULL == Device) {
		Status = XPM_INVALID_DEVICEID;
		goto done;
	}

	if (Device->Node.Id != DeviceId) {
		Status = XPM_INVALID_DEVICEID;
		goto done;
	}

	Subsystem = XPmSubsystem_GetById(SubsystemId);
	if (Subsystem == NULL || Subsystem->State != ONLINE) {
		Status = XPM_INVALID_SUBSYSID;
		goto done;
	}

	Status = Device->DeviceOps->SetRequirement(Device, Subsystem,
						   Capabilities, QoS);

done:
	if(Status != XST_SUCCESS) {
		PmErr("Returned: 0x%x\n\r", Status);
	}
	return Status;
}

XStatus XPmDevice_GetStatus(const u32 SubsystemId,
			const u32 DeviceId,
			XPm_DeviceStatus *const DeviceStatus)
{
	XStatus Status = XPM_ERR_DEVICE_STATUS;
	XPm_Subsystem *Subsystem;
	XPm_Device *Device;
	XPm_Requirement *Reqm;

	Subsystem = XPmSubsystem_GetById(SubsystemId);
	if (Subsystem == NULL || Subsystem->State != ONLINE) {
		Status = XPM_INVALID_SUBSYSID;
		goto done;
	}

	Device = XPmDevice_GetById(DeviceId);
	if (NULL == Device) {
		Status = XPM_INVALID_DEVICEID;
		goto done;
	}

	DeviceStatus->Status = Device->Node.State;

	Reqm = FindReqm(Device, Subsystem);
	if (NULL != Reqm) {
		DeviceStatus->Requirement = Reqm->Curr.Capabilities;
	}

	DeviceStatus->Usage = XPmDevice_GetUsageStatus(Subsystem, Device);

	Status = XST_SUCCESS;
done:
	if(Status != XST_SUCCESS) {
		PmErr("Returned: 0x%x\n\r", Status);
	}
	return Status;
}

XStatus XPmDevice_AddParent(u32 Id, u32 *Parents, u32 NumParents)
{
	XStatus Status = XST_SUCCESS;
	u32 i = 0;
	u32 DeviceIndex = NODEINDEX(Id);
	XPm_Device *DevPtr = XPmDevice_GetById(Id);

	if(DevPtr == NULL || DeviceIndex > MaxDevices || NumParents == 0)
	{
		Status = XST_INVALID_PARAM;
		goto done;
	}

	for(i=0;i<NumParents;i++)
	{
		if(NODECLASS(Parents[i]) == XPM_NODECLASS_CLOCK)
		{
			XPm_ClockNode *Clk = XPmClock_GetById(Parents[i]);
			if (NULL == Clk) {
				Status = XST_INVALID_PARAM;
				goto done;
			}

			Status = XPmDevice_AddClock(DevPtr, Clk);
			if (XST_SUCCESS != Status) {
				goto done;
			}
		}
		else if(NODECLASS(Parents[i]) == XPM_NODECLASS_RESET)
		{
			XPm_ResetNode *Rst = XPmReset_GetById(Parents[i]);
			if (NULL == Rst) {
				Status = XST_INVALID_PARAM;
				goto done;
			}

			Status = XPmDevice_AddReset(DevPtr, Rst);
			if (XST_SUCCESS != Status) {
				goto done;
			}
		}
		else if(NODECLASS(Parents[i]) == XPM_NODECLASS_POWER)
		{
			if (DevPtr->Power != NULL) {
				Status = XST_INVALID_PARAM;
				goto done;
			} else {
				DevPtr->Power = XPmPower_GetById(Parents[i]);
				if (NULL == DevPtr->Power) {
					Status = XST_DEVICE_NOT_FOUND;
					goto done;
				}
			}
		}
		else
		{
			Status = XST_INVALID_PARAM;
			goto done;
		}
	}
done:
	return Status;
}

XStatus XPmDevice_GetPermissions(XPm_Device *Device, u32 *PermissionMask)
{
	XStatus Status = XST_SUCCESS;
	XPm_Requirement *Reqm;
	u32 Idx;

	if ((NULL == Device) || (NULL == PermissionMask)) {
		Status = XST_INVALID_PARAM;
		goto done;
	}

	Reqm = Device->Requirements;
	while (NULL != Reqm) {
		if (TRUE == Reqm->Allocated) {
			for (Idx = 0; Idx < XPM_NODEIDX_SUBSYS_MAX; Idx++) {
				if (Reqm->Subsystem == XPmSubsystem_GetByIndex(Idx)) {
					*PermissionMask |= (1 << Idx);
				}
			}
		}
		Reqm = Reqm->NextSubsystem;
	}

done:
	return Status;
}

/****************************************************************************/
/**
 * @brief  Set maximum allowed latency for the device
 *
 * @param  SubsystemId	Initiator of the request who must previously requested
 *			the device
 * @param  DeviceId	Device whose latency is specified
 * @param  Latency	Maximum allowed latency in microseconds
 *
 * @return XST_SUCCESS if successful else XST_FAILURE or an error code
 * or a reason code
 *
 ****************************************************************************/
int XPmDevice_SetMaxLatency(const u32 SubsystemId, const u32 DeviceId,
			    const u32 Latency)
{
	int Status = XST_SUCCESS;
	XPm_Requirement *Reqm;
	XPm_Subsystem *Subsystem = XPmSubsystem_GetById(SubsystemId);
	XPm_Device *Device = XPmDevice_GetById(DeviceId);

	if ((NULL == Subsystem) || (NULL == Device)) {
		Status = XST_INVALID_PARAM;
		goto done;
	}

	Reqm = FindReqm(Device, Subsystem);
	if (NULL == Reqm) {
		Status = XPM_ERR_DEVICE_REQ;
		goto done;
	}

	Reqm->Next.Latency = Latency;
	Reqm->SetLatReq = 1;

	Status = XPmDevice_UpdateStatus(Device);
	if (XST_SUCCESS != Status) {
		Reqm->SetLatReq = 0;
		goto done;
	}

	Reqm->Curr.Latency = Latency;

done:
	return Status;
}

/****************************************************************************/
/**
 * @brief	Change state of a device
 *
 * @param Device	Device pointer whose state should be changed
 * @param NextState		New state
 *
 * @return	XST_SUCCESS if transition was performed successfully.
 *              Error otherwise.
 *
 * @note	None
 *
 ****************************************************************************/
XStatus XPmDevice_ChangeState(XPm_Device *Device, const u32 NextState)
{
	XStatus Status = XPM_ERR_SETSTATE;
	const XPm_DeviceFsm* Fsm = Device->DeviceFsm;
	u32 OldState = Device->Node.State;
	u32 Trans;

	if (0U == Fsm->TransCnt) {
		/* Device's FSM has no transitions when it has only one state */
		Status = XST_SUCCESS;
		goto done;
	}

	for (Trans = 0U; Trans < Fsm->TransCnt; Trans++) {
		/* Find transition from current state to next state */
		if ((Fsm->Trans[Trans].FromState != Device->Node.State) ||
			(Fsm->Trans[Trans].ToState != NextState)) {
			continue;
		}

		if (NULL != Device->DeviceFsm->EnterState) {
			/* Execute transition action of device's FSM */
			Status = Device->DeviceFsm->EnterState(Device, NextState);
		} else {
			Status = XST_SUCCESS;
		}

		break;
	}

	if ((OldState != NextState) && (XST_SUCCESS == Status)) {
		Device->Node.State = NextState;

		/* Send notification about device state change */
		XPmNotifier_Event(Device, EVENT_STATE_CHANGE);
	}

done:
	return Status;
}

/****************************************************************************/
/**
 * @brief	Get state with provided capabilities
 *
 * @param Device	Device whose states are searched
 * @param Caps		Capabilities the state must have
 * @param State		Pointer to a u32 variable where the result is put if
 *			state is found
 *
 * @return	Status of the operation
 *		- XST_SUCCESS if state is found
 *
 * @note	None
 *
 ****************************************************************************/
static XStatus GetStateWithCaps(const XPm_Device* const Device, const u32 Caps,
				u32* const State)
{
	u32 Idx;
	XStatus Status = XPM_ERR_GETSTATE;

	for (Idx = 0U; Idx < Device->DeviceFsm->StatesCnt; Idx++) {
		/* Find the first state that contains all capabilities */
		if ((Caps & Device->DeviceFsm->States[Idx].Cap) == Caps) {
			Status = XST_SUCCESS;
			if (NULL != State) {
				*State = Device->DeviceFsm->States[Idx].State;
			}
			break;
		}
	}

	return Status;
}

/****************************************************************************/
/**
 * @brief  Find minimum of all latency requirements
 *
 * @Param  Device	Device whose min required latency is requested
 *
 * @return Latency in microseconds
 *
 ****************************************************************************/
static u32 GetMinRequestedLatency(const XPm_Device *const Device)
{
	XPm_Requirement *Reqm = Device->Requirements;
	u32 MinLatency = XPM_MAX_LATENCY;

	while (NULL != Reqm) {
		if ((TRUE == Reqm->SetLatReq) &&
		    (MinLatency > Reqm->Next.Latency)) {
			MinLatency = Reqm->Next.Latency;
		}
		Reqm = Reqm->NextSubsystem;
	}

	return MinLatency;
}

/****************************************************************************/
/**
 * @brief  Get latency from given state to the highest state
 *
 * @param  Device	Pointer to the device whose states are in question
 * @param  State	State from which the latency is calculated
 *
 * @return Return value for the found latency
 *
 ****************************************************************************/
static u32 GetLatencyFromState(const XPm_Device *const Device, const u32 State)
{
	u32 Idx;
	u32 Latency = 0U;
	u32 HighestState = Device->DeviceFsm->StatesCnt - 1;

	for (Idx = 0U; Idx < Device->DeviceFsm->TransCnt; Idx++) {
		if ((State == Device->DeviceFsm->Trans[Idx].FromState) &&
		    (HighestState == Device->DeviceFsm->Trans[Idx].ToState)) {
			Latency = Device->DeviceFsm->Trans[Idx].Latency;
			break;
		}
	}

	return Latency;
}

/****************************************************************************/
/**
 * @brief  Find a higher power state which satisfies latency requirements
 *
 * @param  Device	Device whose state may be constrained
 * @param  State	Chosen state which does not satisfy latency requirements
 * @param  CapsToSet	Capabilities that the state must have
 * @param  MinLatency	Latency requirements to be satisfied
 *
 * @return Status showing whether the higher power state is found or not.
 * State may not be found if multiple subsystem have contradicting requirements,
 * then XST_FAILURE is returned. Otherwise, function returns success.
 *
 ****************************************************************************/
static int ConstrainStateByLatency(const XPm_Device *const Device,
				   u32 *const State, const u32 CapsToSet,
				   const u32 MinLatency)
{
	int Status = XST_FAILURE;
	u32 WkupLat;
	u32 Idx = 0;

	/*
	 * Need to find higher power state, so ignore lower power states
	 * and find index for chosen state
	 */
	while (Device->DeviceFsm->States[Idx].State != *State)
	{
		Idx++;
	}

	for (; Idx < Device->DeviceFsm->StatesCnt; Idx++) {
		if ((CapsToSet & Device->DeviceFsm->States[Idx].Cap) != CapsToSet) {
			/* State candidate has no required capabilities */
			continue;
		}
		WkupLat = GetLatencyFromState(Device, Device->DeviceFsm->States[Idx].State);
		if (WkupLat > MinLatency) {
			/* State does not satisfy latency requirement */
			continue;
		}

		Status = XST_SUCCESS;
		*State = Device->DeviceFsm->States[Idx].State;
		break;
	}

	return Status;
}

/****************************************************************************/
/**
 * @brief  Device updates its power parent about latency req
 *
 * @param  Device	Device whose latency requirement have changed
 *
 * @return If the change of the latency requirement caused the power up of the
 * power parent, the status of performing power up operation is returned,
 * otherwise XST_SUCCESS is returned.
 *
 ****************************************************************************/
static int UpdatePwrLatencyReq(const XPm_Device *const Device)
{
	int Status = XST_SUCCESS;
	XPm_Power* Power = Device->Power;

	if (XPM_POWER_STATE_ON == Power->Node.State) {
		goto done;
	}

	/* Power is down, check if latency requirements trigger the power up */
	if (Device->Node.LatencyMarg <
	    (Power->PwrDnLatency + Power->PwrUpLatency)) {
		Power->Node.LatencyMarg = 0U;
		Status = Power->Node.HandleEvent(&Power->Node,
						 XPM_POWER_EVENT_PWR_UP);
	}

done:
	return Status;
}

/****************************************************************************/
/**
 * @brief	Update the device's state according to the current requirements
 *		from all subsystems
 * @param Device	Device whose state is about to be updated
 *
 * @return      Status of operation of updating device's state.
 *
 * @note	None
 *
 ****************************************************************************/
XStatus XPmDevice_UpdateStatus(XPm_Device *Device)
{
	XStatus Status = XPM_ERR_DEVICE_STATUS;
	u32 Caps = GetMaxCapabilities(Device);
	u32 WkupLat, MinLat;
	u32 State = 0;

	if ((XPM_DEVSTATE_UNUSED != Device->Node.State) &&
	    (XPM_DEVSTATE_RUNNING != Device->Node.State) &&
	    (XPM_DEVSTATE_RUNTIME_SUSPEND != Device->Node.State)) {
			Status = XST_DEVICE_BUSY;
			goto done;
	}

	Status = GetStateWithCaps(Device, Caps, &State);
	if (XST_SUCCESS != Status) {
		goto done;
	}

	MinLat = GetMinRequestedLatency(Device);
	WkupLat = GetLatencyFromState(Device, State);
	if (WkupLat > MinLat) {
		/* State does not satisfy latency requirement, find another */
		Status = ConstrainStateByLatency(Device, &State, Caps, MinLat);
		if (XST_SUCCESS != Status) {
			goto done;
		}

		WkupLat = GetLatencyFromState(Device, State);
	}

	Device->Node.LatencyMarg = MinLat - WkupLat;

	if (State != Device->Node.State) {
		Status = XPmDevice_ChangeState(Device, State);
	} else {
		if ((XPM_DEVSTATE_UNUSED == Device->Node.State) &&
		    (NULL != Device->Power)) {
			/* Notify power parent (changed latency requirement) */
			Status = UpdatePwrLatencyReq(Device);
		}
	}

done:
	return Status;
}

/****************************************************************************/
/**
 * @brief  Get the current usage status for a given device.
 * @param  Subsystem   Subsystem for which usage status is in query
 * @slave  Device      Device for which usage status need to be calculated
 *
 * @return  Usage status:
 *          - 0: No subsystem is currently using the device
 *          - 1: Only requesting subsystem is currently using the device
 *          - 2: Only other subsystems are currently using the device
 *          - 3: Both the current and at least one other subsystem is currently
 *               using the device
 *
 ****************************************************************************/
int XPmDevice_GetUsageStatus(XPm_Subsystem *Subsystem, XPm_Device *Device)
{
	int UsageStatus = 0;
	XPm_Requirement *Reqm = Device->Requirements;

	while (NULL != Reqm) {
		if (TRUE == Reqm->Allocated) {
			/* This subsystem is currently using this device */
			if (Subsystem == Reqm->Subsystem) {
				UsageStatus |= PM_USAGE_CURRENT_SUBSYSTEM;
			} else {
				UsageStatus |= PM_USAGE_OTHER_SUBSYSTEM;
			}
		}
		Reqm = Reqm->NextSubsystem;
	}

	return UsageStatus;
}

/****************************************************************************/
/**
 * @brief  Check if any clock for a given device is active
 * @param  Device      Device whose clocks need to be checked
 *
 * @return XST_SUCCESS if any one clock for given device is active
 *         XST_FAILURE if all clocks for given device are inactive
 *
 ****************************************************************************/
int XPmDevice_IsClockActive(XPm_Device *Device)
{
	int Status = XST_FAILURE;
	XPm_ClockHandle *ClkHandle = Device->ClkHandles;
	XPm_OutClockNode *Clk;
	u32 Enable;

	while (NULL != ClkHandle) {
		if ((NULL != ClkHandle->Clock) &&
		    (ISOUTCLK(ClkHandle->Clock->Node.Id))) {
			Clk = (XPm_OutClockNode *)ClkHandle->Clock;
			Status = XPmClock_GetClockData(Clk, TYPE_GATE, &Enable);
			if (XST_SUCCESS == Status) {
				if (1U == Enable) {
					Status = XST_SUCCESS;
					goto done;
				}
			} else if (XPM_INVALID_CLK_SUBNODETYPE == Status) {
				PmDbg("Clock 0x%x does not have Clock Gate\n\r",
						ClkHandle->Clock->Node.Id);
				Status = XST_SUCCESS;
			} else {
				PmErr("XPmClock_GetClockData failed with Status 0x%x"
						" for clock id: 0x%x\r\n",
						Status,
						ClkHandle->Clock->Node.Id);
			}
		}
		ClkHandle = ClkHandle->NextClock;
	}

done:
	return Status;
}

/****************************************************************************/
/**
 * @brief  Check if any subsystem requested perticular device or not.
 *
 * @param  DeviceId	Device ID
 * @param  SubsystemId	Subsystem ID
 *
 * @return XST_SUCCESS if device is requested from subsystem
 *         XST_FAILURE if device is not requested or error code
 *
 ****************************************************************************/
int XPmDevice_IsRequested(const u32 DeviceId, const u32 SubsystemId)
{
	int Status = XST_FAILURE;
	XPm_Device *Device = XPmDevice_GetById(DeviceId);
	XPm_Subsystem *Subsystem = XPmSubsystem_GetById(SubsystemId);
	XPm_Requirement *Reqm;

	if ((NULL == Device) || (NULL == Subsystem)) {
		Status = XST_INVALID_PARAM;
		goto done;
	}

	Reqm = FindReqm(Device, Subsystem);
	if ((NULL != Reqm) && (TRUE == Reqm->Allocated)) {
		Status = XST_SUCCESS;
	}

done:
	return Status;
}