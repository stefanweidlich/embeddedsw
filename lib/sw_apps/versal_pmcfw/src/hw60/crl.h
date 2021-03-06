/**
 * (c) 2013 Xilinx Inc.
 * XREGDB v0.91
 * XREGCHDR v0.15
 *
 * Generated on: 2018-06-19
 *
 * @file: crl.h
 *
 *
 * This file contains confidential and proprietary information
 * of Xilinx, Inc. and is protected under U.S. and
 * international copyright and other intellectual property
 * laws.
 *
 * DISCLAIMER
 * This disclaimer is not a license and does not grant any
 * rights to the materials distributed herewith. Except as
 * otherwise provided in a valid license issued to you by
 * Xilinx, and to the maximum extent permitted by applicable
 * law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
 * WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
 * AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
 * BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
 * INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
 * (2) Xilinx shall not be liable (whether in contract or tort,
 * including negligence, or under any other theory of
 * liability) for any loss or damage of any kind or nature
 * related to, arising under or in connection with these
 * materials, including for any direct, or any indirect,
 * special, incidental, or consequential loss or damage
 * (including loss of data, profits, goodwill, or any type of
 * loss or damage suffered as a result of any action brought
 * by a third party) even if such damage or loss was
 * reasonably foreseeable or Xilinx had been advised of the
 * possibility of the same.
 *
 * CRITICAL APPLICATIONS
 * Xilinx products are not designed or intended to be fail-
 * safe, or for use in any application requiring fail-safe
 * performance, such as life-support or safety devices or
 * systems, Class III medical devices, nuclear facilities,
 * applications related to the deployment of airbags, or any
 * other applications that could lead to death, personal
 * injury, or severe property or environmental damage
 * (individually and collectively, "Critical
 * Applications"). Customer assumes the sole risk and
 * liability of any use of Xilinx products in Critical
 * Applications, subject only to applicable laws and
 * regulations governing limitations on product liability.
 *
 * THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
 * PART OF THIS FILE AT ALL TIMES.
 *
 * Naming Convention: <MODULE>_<REGISTER>[_<FIELD>[_<DESC>]]
 *     <MODULE>       Module name (e.g. can or usb)
 *     <REGISTER>     Register within the current module
 *     [_<FIELD>]     Bit field within a register
 *     [_<DESC>]      Type of bit field define:
 *         SHIFT:     Least significant bit for the field
 *         WIDTH:     Size of field in bites
 *         MASK:      A masking over a range of bits or a bit to
 *                    be used for setting or clearing
 *
 */

#ifndef _CRL_H_
#define _CRL_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * CRL Base Address
 */
#define CRL_BASEADDR      0XFF5E0000

/**
 * Register: CRL_ERR_CTRL
 */
#define CRL_ERR_CTRL    ( ( CRL_BASEADDR ) + 0X00000000 )

#define CRL_ERR_CTRL_SLVERR_ENABLE_SHIFT   0
#define CRL_ERR_CTRL_SLVERR_ENABLE_WIDTH   1
#define CRL_ERR_CTRL_SLVERR_ENABLE_MASK    0X00000001

/**
 * Register: CRL_IR_STATUS
 */
#define CRL_IR_STATUS    ( ( CRL_BASEADDR ) + 0X00000004 )

#define CRL_IR_STATUS_ADDR_DECODE_ERR_SHIFT   0
#define CRL_IR_STATUS_ADDR_DECODE_ERR_WIDTH   1
#define CRL_IR_STATUS_ADDR_DECODE_ERR_MASK    0X00000001

/**
 * Register: CRL_IR_MASK
 */
#define CRL_IR_MASK    ( ( CRL_BASEADDR ) + 0X00000008 )

#define CRL_IR_MASK_ADDR_DECODE_ERR_SHIFT   0
#define CRL_IR_MASK_ADDR_DECODE_ERR_WIDTH   1
#define CRL_IR_MASK_ADDR_DECODE_ERR_MASK    0X00000001

/**
 * Register: CRL_IR_ENABLE
 */
#define CRL_IR_ENABLE    ( ( CRL_BASEADDR ) + 0X0000000C )

#define CRL_IR_ENABLE_ADDR_DECODE_ERR_SHIFT   0
#define CRL_IR_ENABLE_ADDR_DECODE_ERR_WIDTH   1
#define CRL_IR_ENABLE_ADDR_DECODE_ERR_MASK    0X00000001

/**
 * Register: CRL_IR_DISABLE
 */
#define CRL_IR_DISABLE    ( ( CRL_BASEADDR ) + 0X00000010 )

#define CRL_IR_DISABLE_ADDR_DECODE_ERR_SHIFT   0
#define CRL_IR_DISABLE_ADDR_DECODE_ERR_WIDTH   1
#define CRL_IR_DISABLE_ADDR_DECODE_ERR_MASK    0X00000001

/**
 * Register: CRL_ECO
 */
#define CRL_ECO    ( ( CRL_BASEADDR ) + 0X00000018 )

#define CRL_ECO_ECO_SHIFT   0
#define CRL_ECO_ECO_WIDTH   32
#define CRL_ECO_ECO_MASK    0XFFFFFFFF

/**
 * Register: CRL_WPROT
 */
#define CRL_WPROT    ( ( CRL_BASEADDR ) + 0X0000001C )

#define CRL_WPROT_ACTIVE_SHIFT   0
#define CRL_WPROT_ACTIVE_WIDTH   1
#define CRL_WPROT_ACTIVE_MASK    0X00000001

/**
 * Register: CRL_PLL_CLK_OTHER_DMN
 */
#define CRL_PLL_CLK_OTHER_DMN    ( ( CRL_BASEADDR ) + 0X00000020 )

#define CRL_PLL_CLK_OTHER_DMN_APLL_BYPASS_SHIFT   0
#define CRL_PLL_CLK_OTHER_DMN_APLL_BYPASS_WIDTH   1
#define CRL_PLL_CLK_OTHER_DMN_APLL_BYPASS_MASK    0X00000001

/**
 * Register: CRL_RPLL_CTRL
 */
#define CRL_RPLL_CTRL    ( ( CRL_BASEADDR ) + 0X00000040 )

#define CRL_RPLL_CTRL_POST_SRC_SHIFT   24
#define CRL_RPLL_CTRL_POST_SRC_WIDTH   3
#define CRL_RPLL_CTRL_POST_SRC_MASK    0X07000000

#define CRL_RPLL_CTRL_PRE_SRC_SHIFT   20
#define CRL_RPLL_CTRL_PRE_SRC_WIDTH   3
#define CRL_RPLL_CTRL_PRE_SRC_MASK    0X00700000

#define CRL_RPLL_CTRL_CLKOUTDIV_SHIFT   16
#define CRL_RPLL_CTRL_CLKOUTDIV_WIDTH   2
#define CRL_RPLL_CTRL_CLKOUTDIV_MASK    0X00030000

#define CRL_RPLL_CTRL_FBDIV_SHIFT   8
#define CRL_RPLL_CTRL_FBDIV_WIDTH   8
#define CRL_RPLL_CTRL_FBDIV_MASK    0X0000FF00

#define CRL_RPLL_CTRL_BYPASS_SHIFT   3
#define CRL_RPLL_CTRL_BYPASS_WIDTH   1
#define CRL_RPLL_CTRL_BYPASS_MASK    0X00000008

#define CRL_RPLL_CTRL_RESET_SHIFT   0
#define CRL_RPLL_CTRL_RESET_WIDTH   1
#define CRL_RPLL_CTRL_RESET_MASK    0X00000001

/**
 * Register: CRL_RPLL_CFG
 */
#define CRL_RPLL_CFG    ( ( CRL_BASEADDR ) + 0X00000044 )

#define CRL_RPLL_CFG_LOCK_DLY_SHIFT   25
#define CRL_RPLL_CFG_LOCK_DLY_WIDTH   7
#define CRL_RPLL_CFG_LOCK_DLY_MASK    0XFE000000

#define CRL_RPLL_CFG_LOCK_CNT_SHIFT   13
#define CRL_RPLL_CFG_LOCK_CNT_WIDTH   10
#define CRL_RPLL_CFG_LOCK_CNT_MASK    0X007FE000

#define CRL_RPLL_CFG_LFHF_SHIFT   10
#define CRL_RPLL_CFG_LFHF_WIDTH   2
#define CRL_RPLL_CFG_LFHF_MASK    0X00000C00

#define CRL_RPLL_CFG_CP_SHIFT   5
#define CRL_RPLL_CFG_CP_WIDTH   4
#define CRL_RPLL_CFG_CP_MASK    0X000001E0

#define CRL_RPLL_CFG_RES_SHIFT   0
#define CRL_RPLL_CFG_RES_WIDTH   4
#define CRL_RPLL_CFG_RES_MASK    0X0000000F

/**
 * Register: CRL_RPLL_FRAC_CFG
 */
#define CRL_RPLL_FRAC_CFG    ( ( CRL_BASEADDR ) + 0X00000048 )

#define CRL_RPLL_FRAC_CFG_ENABLED_SHIFT   31
#define CRL_RPLL_FRAC_CFG_ENABLED_WIDTH   1
#define CRL_RPLL_FRAC_CFG_ENABLED_MASK    0X80000000

#define CRL_RPLL_FRAC_CFG_SEED_SHIFT   22
#define CRL_RPLL_FRAC_CFG_SEED_WIDTH   3
#define CRL_RPLL_FRAC_CFG_SEED_MASK    0X01C00000

#define CRL_RPLL_FRAC_CFG_ALGRTHM_SHIFT   19
#define CRL_RPLL_FRAC_CFG_ALGRTHM_WIDTH   1
#define CRL_RPLL_FRAC_CFG_ALGRTHM_MASK    0X00080000

#define CRL_RPLL_FRAC_CFG_ORDER_SHIFT   18
#define CRL_RPLL_FRAC_CFG_ORDER_WIDTH   1
#define CRL_RPLL_FRAC_CFG_ORDER_MASK    0X00040000

#define CRL_RPLL_FRAC_CFG_DATA_SHIFT   0
#define CRL_RPLL_FRAC_CFG_DATA_WIDTH   16
#define CRL_RPLL_FRAC_CFG_DATA_MASK    0X0000FFFF

/**
 * Register: CRL_PLL_STATUS
 */
#define CRL_PLL_STATUS    ( ( CRL_BASEADDR ) + 0X00000050 )

#define CRL_PLL_STATUS_RPLL_STABLE_SHIFT   2
#define CRL_PLL_STATUS_RPLL_STABLE_WIDTH   1
#define CRL_PLL_STATUS_RPLL_STABLE_MASK    0X00000004

#define CRL_PLL_STATUS_RPLL_LOCK_SHIFT   0
#define CRL_PLL_STATUS_RPLL_LOCK_WIDTH   1
#define CRL_PLL_STATUS_RPLL_LOCK_MASK    0X00000001

/**
 * Register: CRL_PLL_REG0
 */
#define CRL_PLL_REG0    ( ( CRL_BASEADDR ) + 0X0000005C )

#define CRL_PLL_REG0_FREQ_COMP_SHIFT   22
#define CRL_PLL_REG0_FREQ_COMP_WIDTH   3
#define CRL_PLL_REG0_FREQ_COMP_MASK    0X01C00000

#define CRL_PLL_REG0_LOCK_SAT_HIGH_SHIFT   12
#define CRL_PLL_REG0_LOCK_SAT_HIGH_WIDTH   10
#define CRL_PLL_REG0_LOCK_SAT_HIGH_MASK    0X003FF000

#define CRL_PLL_REG0_UNLOCK_CNT_SHIFT   2
#define CRL_PLL_REG0_UNLOCK_CNT_WIDTH   10
#define CRL_PLL_REG0_UNLOCK_CNT_MASK    0X00000FFC

/**
 * Register: CRL_PLL_REG1
 */
#define CRL_PLL_REG1    ( ( CRL_BASEADDR ) + 0X00000060 )

#define CRL_PLL_REG1_EN_VCO_DIV1_SHIFT   29
#define CRL_PLL_REG1_EN_VCO_DIV1_WIDTH   1
#define CRL_PLL_REG1_EN_VCO_DIV1_MASK    0X20000000

#define CRL_PLL_REG1_EN_VCO_DIV6_SHIFT   28
#define CRL_PLL_REG1_EN_VCO_DIV6_WIDTH   1
#define CRL_PLL_REG1_EN_VCO_DIV6_MASK    0X10000000

#define CRL_PLL_REG1_EN_SYNC_CK_TEST_SHIFT   27
#define CRL_PLL_REG1_EN_SYNC_CK_TEST_WIDTH   1
#define CRL_PLL_REG1_EN_SYNC_CK_TEST_MASK    0X08000000

#define CRL_PLL_REG1_VCO_STARTUP_HYST_DISABLE_SHIFT   25
#define CRL_PLL_REG1_VCO_STARTUP_HYST_DISABLE_WIDTH   1
#define CRL_PLL_REG1_VCO_STARTUP_HYST_DISABLE_MASK    0X02000000

#define CRL_PLL_REG1_VCO_STARTUP_ALT_EN_SHIFT   24
#define CRL_PLL_REG1_VCO_STARTUP_ALT_EN_WIDTH   1
#define CRL_PLL_REG1_VCO_STARTUP_ALT_EN_MASK    0X01000000

#define CRL_PLL_REG1_VCO_STARTUP_ADJ_SHIFT   23
#define CRL_PLL_REG1_VCO_STARTUP_ADJ_WIDTH   1
#define CRL_PLL_REG1_VCO_STARTUP_ADJ_MASK    0X00800000

#define CRL_PLL_REG1_VCO_KICK_DISABLE_SHIFT   22
#define CRL_PLL_REG1_VCO_KICK_DISABLE_WIDTH   1
#define CRL_PLL_REG1_VCO_KICK_DISABLE_MASK    0X00400000

#define CRL_PLL_REG1_VCO_GATE_CCI_B_SHIFT   21
#define CRL_PLL_REG1_VCO_GATE_CCI_B_WIDTH   1
#define CRL_PLL_REG1_VCO_GATE_CCI_B_MASK    0X00200000

#define CRL_PLL_REG1_VCO_HIGH_RANGE_EN_SHIFT   20
#define CRL_PLL_REG1_VCO_HIGH_RANGE_EN_WIDTH   1
#define CRL_PLL_REG1_VCO_HIGH_RANGE_EN_MASK    0X00100000

#define CRL_PLL_REG1_PFD_STARTUP_SHIFT   19
#define CRL_PLL_REG1_PFD_STARTUP_WIDTH   1
#define CRL_PLL_REG1_PFD_STARTUP_MASK    0X00080000

#define CRL_PLL_REG1_PFD_SHIFT   12
#define CRL_PLL_REG1_PFD_WIDTH   7
#define CRL_PLL_REG1_PFD_MASK    0X0007F000

#define CRL_PLL_REG1_SEL_SLIPD_SHIFT   11
#define CRL_PLL_REG1_SEL_SLIPD_WIDTH   1
#define CRL_PLL_REG1_SEL_SLIPD_MASK    0X00000800

#define CRL_PLL_REG1_SENSE_TEST_EN_SHIFT   10
#define CRL_PLL_REG1_SENSE_TEST_EN_WIDTH   1
#define CRL_PLL_REG1_SENSE_TEST_EN_MASK    0X00000400

#define CRL_PLL_REG1_SPARE_ANALOG_SHIFT   5
#define CRL_PLL_REG1_SPARE_ANALOG_WIDTH   5
#define CRL_PLL_REG1_SPARE_ANALOG_MASK    0X000003E0

#define CRL_PLL_REG1_SPARE_DIGITAL_SHIFT   0
#define CRL_PLL_REG1_SPARE_DIGITAL_WIDTH   5
#define CRL_PLL_REG1_SPARE_DIGITAL_MASK    0X0000001F

/**
 * Register: CRL_PLL_REG2
 */
#define CRL_PLL_REG2    ( ( CRL_BASEADDR ) + 0X00000064 )

#define CRL_PLL_REG2_SUP_SEL_VCCINT_SHIFT   28
#define CRL_PLL_REG2_SUP_SEL_VCCINT_WIDTH   1
#define CRL_PLL_REG2_SUP_SEL_VCCINT_MASK    0X10000000

#define CRL_PLL_REG2_SUP_SEL_VCCAUX_SHIFT   27
#define CRL_PLL_REG2_SUP_SEL_VCCAUX_WIDTH   1
#define CRL_PLL_REG2_SUP_SEL_VCCAUX_MASK    0X08000000

#define CRL_PLL_REG2_SUP_SEL_VBG_SHIFT   26
#define CRL_PLL_REG2_SUP_SEL_VBG_WIDTH   1
#define CRL_PLL_REG2_SUP_SEL_VBG_MASK    0X04000000

#define CRL_PLL_REG2_SUP_SEL_AVDD_SHIFT   25
#define CRL_PLL_REG2_SUP_SEL_AVDD_WIDTH   1
#define CRL_PLL_REG2_SUP_SEL_AVDD_MASK    0X02000000

#define CRL_PLL_REG2_SUP_SEL_VBGHALF_SHIFT   24
#define CRL_PLL_REG2_SUP_SEL_VBGHALF_WIDTH   1
#define CRL_PLL_REG2_SUP_SEL_VBGHALF_MASK    0X01000000

#define CRL_PLL_REG2_VLF_HIGH_SEL_SHIFT   18
#define CRL_PLL_REG2_VLF_HIGH_SEL_WIDTH   2
#define CRL_PLL_REG2_VLF_HIGH_SEL_MASK    0X000C0000

#define CRL_PLL_REG2_VLF_VALID_SEL_SHIFT   15
#define CRL_PLL_REG2_VLF_VALID_SEL_WIDTH   3
#define CRL_PLL_REG2_VLF_VALID_SEL_MASK    0X00038000

#define CRL_PLL_REG2_VLF_VALID_PWDN_SHIFT   14
#define CRL_PLL_REG2_VLF_VALID_PWDN_WIDTH   1
#define CRL_PLL_REG2_VLF_VALID_PWDN_MASK    0X00004000

#define CRL_PLL_REG2_VLF_HIGH_PWDN_B_SHIFT   13
#define CRL_PLL_REG2_VLF_HIGH_PWDN_B_WIDTH   1
#define CRL_PLL_REG2_VLF_HIGH_PWDN_B_MASK    0X00002000

#define CRL_PLL_REG2_LF_LOW_SEL_SHIFT   12
#define CRL_PLL_REG2_LF_LOW_SEL_WIDTH   1
#define CRL_PLL_REG2_LF_LOW_SEL_MASK    0X00001000

#define CRL_PLL_REG2_LF_NEN_SHIFT   10
#define CRL_PLL_REG2_LF_NEN_WIDTH   2
#define CRL_PLL_REG2_LF_NEN_MASK    0X00000C00

#define CRL_PLL_REG2_LF_PEN_SHIFT   8
#define CRL_PLL_REG2_LF_PEN_WIDTH   2
#define CRL_PLL_REG2_LF_PEN_MASK    0X00000300

#define CRL_PLL_REG2_MAN_LF_SHIFT   4
#define CRL_PLL_REG2_MAN_LF_WIDTH   3
#define CRL_PLL_REG2_MAN_LF_MASK    0X00000070

#define CRL_PLL_REG2_ANALOG_MISC_SHIFT   0
#define CRL_PLL_REG2_ANALOG_MISC_WIDTH   4
#define CRL_PLL_REG2_ANALOG_MISC_MASK    0X0000000F

/**
 * Register: CRL_PLL_REG3
 */
#define CRL_PLL_REG3    ( ( CRL_BASEADDR ) + 0X00000068 )

#define CRL_PLL_REG3_REGLPF_RES_SHORT_SHIFT   24
#define CRL_PLL_REG3_REGLPF_RES_SHORT_WIDTH   1
#define CRL_PLL_REG3_REGLPF_RES_SHORT_MASK    0X01000000

#define CRL_PLL_REG3_CP_RES_L_SHIFT   22
#define CRL_PLL_REG3_CP_RES_L_WIDTH   2
#define CRL_PLL_REG3_CP_RES_L_MASK    0X00C00000

#define CRL_PLL_REG3_CP_RES_H_SHIFT   20
#define CRL_PLL_REG3_CP_RES_H_WIDTH   2
#define CRL_PLL_REG3_CP_RES_H_MASK    0X00300000

#define CRL_PLL_REG3_CP_OPAMP_BN_SHIFT   19
#define CRL_PLL_REG3_CP_OPAMP_BN_WIDTH   1
#define CRL_PLL_REG3_CP_OPAMP_BN_MASK    0X00080000

#define CRL_PLL_REG3_CP_BIAS_TRIP_SET_SHIFT   18
#define CRL_PLL_REG3_CP_BIAS_TRIP_SET_WIDTH   1
#define CRL_PLL_REG3_CP_BIAS_TRIP_SET_MASK    0X00040000

#define CRL_PLL_REG3_HVLF_CNT_TEST_EN_SHIFT   17
#define CRL_PLL_REG3_HVLF_CNT_TEST_EN_WIDTH   1
#define CRL_PLL_REG3_HVLF_CNT_TEST_EN_MASK    0X00020000

#define CRL_PLL_REG3_HVLF_CNT_TEST_SHIFT   11
#define CRL_PLL_REG3_HVLF_CNT_TEST_WIDTH   6
#define CRL_PLL_REG3_HVLF_CNT_TEST_MASK    0X0001F800

#define CRL_PLL_REG3_AVDD_COMP_SET_SHIFT   8
#define CRL_PLL_REG3_AVDD_COMP_SET_WIDTH   3
#define CRL_PLL_REG3_AVDD_COMP_SET_MASK    0X00000700

#define CRL_PLL_REG3_AVDD_VBG_PD_SHIFT   5
#define CRL_PLL_REG3_AVDD_VBG_PD_WIDTH   3
#define CRL_PLL_REG3_AVDD_VBG_PD_MASK    0X000000E0

#define CRL_PLL_REG3_AVDD_VBG_SEL_SHIFT   0
#define CRL_PLL_REG3_AVDD_VBG_SEL_WIDTH   5
#define CRL_PLL_REG3_AVDD_VBG_SEL_MASK    0X0000001F

/**
 * Register: CRL_PLL_REG4
 */
#define CRL_PLL_REG4    ( ( CRL_BASEADDR ) + 0X0000006C )

#define CRL_PLL_REG4_FORCE_SENSE_SHORT_SHIFT   29
#define CRL_PLL_REG4_FORCE_SENSE_SHORT_WIDTH   1
#define CRL_PLL_REG4_FORCE_SENSE_SHORT_MASK    0X20000000

#define CRL_PLL_REG4_FRACT_TEST_SEL_SHIFT   26
#define CRL_PLL_REG4_FRACT_TEST_SEL_WIDTH   3
#define CRL_PLL_REG4_FRACT_TEST_SEL_MASK    0X1C000000

#define CRL_PLL_REG4_FRACT_TEST_EN_SHIFT   25
#define CRL_PLL_REG4_FRACT_TEST_EN_WIDTH   1
#define CRL_PLL_REG4_FRACT_TEST_EN_MASK    0X02000000

#define CRL_PLL_REG4_TC_GEN_MODE_SHIFT   24
#define CRL_PLL_REG4_TC_GEN_MODE_WIDTH   1
#define CRL_PLL_REG4_TC_GEN_MODE_MASK    0X01000000

#define CRL_PLL_REG4_TESTOUT3_MUX_SEL_SHIFT   18
#define CRL_PLL_REG4_TESTOUT3_MUX_SEL_WIDTH   6
#define CRL_PLL_REG4_TESTOUT3_MUX_SEL_MASK    0X00FC0000

#define CRL_PLL_REG4_TESTOUT2_MUX_SEL_SHIFT   12
#define CRL_PLL_REG4_TESTOUT2_MUX_SEL_WIDTH   6
#define CRL_PLL_REG4_TESTOUT2_MUX_SEL_MASK    0X0003F000

#define CRL_PLL_REG4_TESTOUT1_MUX_SEL_SHIFT   6
#define CRL_PLL_REG4_TESTOUT1_MUX_SEL_WIDTH   6
#define CRL_PLL_REG4_TESTOUT1_MUX_SEL_MASK    0X00000FC0

#define CRL_PLL_REG4_TESTOUT0_MUX_SEL_SHIFT   0
#define CRL_PLL_REG4_TESTOUT0_MUX_SEL_WIDTH   6
#define CRL_PLL_REG4_TESTOUT0_MUX_SEL_MASK    0X0000003F

/**
 * Register: CRL_PLL_REG5
 */
#define CRL_PLL_REG5    ( ( CRL_BASEADDR ) + 0X00000070 )

#define CRL_PLL_REG5_VLF_SWITCH_SEL_SHIFT   9
#define CRL_PLL_REG5_VLF_SWITCH_SEL_WIDTH   3
#define CRL_PLL_REG5_VLF_SWITCH_SEL_MASK    0X00000E00

#define CRL_PLL_REG5_VCO_SINGLE_BAND_DEFAULT_SHIFT   8
#define CRL_PLL_REG5_VCO_SINGLE_BAND_DEFAULT_WIDTH   1
#define CRL_PLL_REG5_VCO_SINGLE_BAND_DEFAULT_MASK    0X00000100

#define CRL_PLL_REG5_VCO_BAND_MODE_SHIFT   7
#define CRL_PLL_REG5_VCO_BAND_MODE_WIDTH   1
#define CRL_PLL_REG5_VCO_BAND_MODE_MASK    0X00000080

#define CRL_PLL_REG5_VLF_HIGH_EN_SHIFT   6
#define CRL_PLL_REG5_VLF_HIGH_EN_WIDTH   1
#define CRL_PLL_REG5_VLF_HIGH_EN_MASK    0X00000040

#define CRL_PLL_REG5_VLF_SWITCH_PWDN_SHIFT   5
#define CRL_PLL_REG5_VLF_SWITCH_PWDN_WIDTH   1
#define CRL_PLL_REG5_VLF_SWITCH_PWDN_MASK    0X00000020

#define CRL_PLL_REG5_TEST_PLL_CK_SEL_SHIFT   2
#define CRL_PLL_REG5_TEST_PLL_CK_SEL_WIDTH   3
#define CRL_PLL_REG5_TEST_PLL_CK_SEL_MASK    0X0000001C

#define CRL_PLL_REG5_FRACT_TEST_CK_SEL_SHIFT   1
#define CRL_PLL_REG5_FRACT_TEST_CK_SEL_WIDTH   1
#define CRL_PLL_REG5_FRACT_TEST_CK_SEL_MASK    0X00000002

#define CRL_PLL_REG5_FBCLK_PREDIV2_SHIFT   0
#define CRL_PLL_REG5_FBCLK_PREDIV2_WIDTH   1
#define CRL_PLL_REG5_FBCLK_PREDIV2_MASK    0X00000001

/**
 * Register: CRL_PLL_REG6
 */
#define CRL_PLL_REG6    ( ( CRL_BASEADDR ) + 0X00000074 )

#define CRL_PLL_REG6_CONTROL_1_SHIFT   16
#define CRL_PLL_REG6_CONTROL_1_WIDTH   16
#define CRL_PLL_REG6_CONTROL_1_MASK    0XFFFF0000

#define CRL_PLL_REG6_CONTROL_0_SHIFT   0
#define CRL_PLL_REG6_CONTROL_0_WIDTH   16
#define CRL_PLL_REG6_CONTROL_0_MASK    0X0000FFFF

/**
 * Register: CRL_PLL_REG7
 */
#define CRL_PLL_REG7    ( ( CRL_BASEADDR ) + 0X00000078 )

#define CRL_PLL_REG7_CONTROL_3_SHIFT   16
#define CRL_PLL_REG7_CONTROL_3_WIDTH   16
#define CRL_PLL_REG7_CONTROL_3_MASK    0XFFFF0000

#define CRL_PLL_REG7_CONTROL_2_SHIFT   0
#define CRL_PLL_REG7_CONTROL_2_WIDTH   16
#define CRL_PLL_REG7_CONTROL_2_MASK    0X0000FFFF

/**
 * Register: CRL_PLL_REG8
 */
#define CRL_PLL_REG8    ( ( CRL_BASEADDR ) + 0X00000080 )

#define CRL_PLL_REG8_CONTROL_5_SHIFT   16
#define CRL_PLL_REG8_CONTROL_5_WIDTH   16
#define CRL_PLL_REG8_CONTROL_5_MASK    0XFFFF0000

#define CRL_PLL_REG8_CONTROL_4_SHIFT   0
#define CRL_PLL_REG8_CONTROL_4_WIDTH   16
#define CRL_PLL_REG8_CONTROL_4_MASK    0X0000FFFF

/**
 * Register: CRL_PLL_REG9
 */
#define CRL_PLL_REG9    ( ( CRL_BASEADDR ) + 0X00000084 )

#define CRL_PLL_REG9_CONTROL_7_SHIFT   16
#define CRL_PLL_REG9_CONTROL_7_WIDTH   16
#define CRL_PLL_REG9_CONTROL_7_MASK    0XFFFF0000

#define CRL_PLL_REG9_CONTROL_6_SHIFT   0
#define CRL_PLL_REG9_CONTROL_6_WIDTH   16
#define CRL_PLL_REG9_CONTROL_6_MASK    0X0000FFFF

/**
 * Register: CRL_RPLL_TO_XPD_CTRL
 */
#define CRL_RPLL_TO_XPD_CTRL    ( ( CRL_BASEADDR ) + 0X00000100 )

#define CRL_RPLL_TO_XPD_CTRL_CLKACT_SHIFT   25
#define CRL_RPLL_TO_XPD_CTRL_CLKACT_WIDTH   1
#define CRL_RPLL_TO_XPD_CTRL_CLKACT_MASK    0X02000000

#define CRL_RPLL_TO_XPD_CTRL_DIVISOR0_SHIFT   8
#define CRL_RPLL_TO_XPD_CTRL_DIVISOR0_WIDTH   10
#define CRL_RPLL_TO_XPD_CTRL_DIVISOR0_MASK    0X0003FF00

/**
 * Register: CRL_LPD_TOP_SWITCH_CTRL
 */
#define CRL_LPD_TOP_SWITCH_CTRL    ( ( CRL_BASEADDR ) + 0X00000104 )

#define CRL_LPD_TOP_SWITCH_CTRL_CLKACT_ADMA_SHIFT   26
#define CRL_LPD_TOP_SWITCH_CTRL_CLKACT_ADMA_WIDTH   1
#define CRL_LPD_TOP_SWITCH_CTRL_CLKACT_ADMA_MASK    0X04000000

#define CRL_LPD_TOP_SWITCH_CTRL_CLKACT_SHIFT   25
#define CRL_LPD_TOP_SWITCH_CTRL_CLKACT_WIDTH   1
#define CRL_LPD_TOP_SWITCH_CTRL_CLKACT_MASK    0X02000000

#define CRL_LPD_TOP_SWITCH_CTRL_DIVISOR0_SHIFT   8
#define CRL_LPD_TOP_SWITCH_CTRL_DIVISOR0_WIDTH   10
#define CRL_LPD_TOP_SWITCH_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_LPD_TOP_SWITCH_CTRL_SRCSEL_SHIFT   0
#define CRL_LPD_TOP_SWITCH_CTRL_SRCSEL_WIDTH   3
#define CRL_LPD_TOP_SWITCH_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_LPD_LSBUS_CTRL
 */
#define CRL_LPD_LSBUS_CTRL    ( ( CRL_BASEADDR ) + 0X00000108 )

#define CRL_LPD_LSBUS_CTRL_CLKACT_SHIFT   25
#define CRL_LPD_LSBUS_CTRL_CLKACT_WIDTH   1
#define CRL_LPD_LSBUS_CTRL_CLKACT_MASK    0X02000000

#define CRL_LPD_LSBUS_CTRL_DIVISOR0_SHIFT   8
#define CRL_LPD_LSBUS_CTRL_DIVISOR0_WIDTH   10
#define CRL_LPD_LSBUS_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_LPD_LSBUS_CTRL_SRCSEL_SHIFT   0
#define CRL_LPD_LSBUS_CTRL_SRCSEL_WIDTH   3
#define CRL_LPD_LSBUS_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_CPU_R5_CTRL
 */
#define CRL_CPU_R5_CTRL    ( ( CRL_BASEADDR ) + 0X0000010C )

#define CRL_CPU_R5_CTRL_CLKACT_OCM2_SHIFT   28
#define CRL_CPU_R5_CTRL_CLKACT_OCM2_WIDTH   1
#define CRL_CPU_R5_CTRL_CLKACT_OCM2_MASK    0X10000000

#define CRL_CPU_R5_CTRL_CLKACT_OCM_SHIFT   27
#define CRL_CPU_R5_CTRL_CLKACT_OCM_WIDTH   1
#define CRL_CPU_R5_CTRL_CLKACT_OCM_MASK    0X08000000

#define CRL_CPU_R5_CTRL_CLKACT_CORE_SHIFT   26
#define CRL_CPU_R5_CTRL_CLKACT_CORE_WIDTH   1
#define CRL_CPU_R5_CTRL_CLKACT_CORE_MASK    0X04000000

#define CRL_CPU_R5_CTRL_CLKACT_SHIFT   25
#define CRL_CPU_R5_CTRL_CLKACT_WIDTH   1
#define CRL_CPU_R5_CTRL_CLKACT_MASK    0X02000000

#define CRL_CPU_R5_CTRL_DIVISOR0_SHIFT   8
#define CRL_CPU_R5_CTRL_DIVISOR0_WIDTH   10
#define CRL_CPU_R5_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_CPU_R5_CTRL_SRCSEL_SHIFT   0
#define CRL_CPU_R5_CTRL_SRCSEL_WIDTH   3
#define CRL_CPU_R5_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_IOU_SWITCH_CTRL
 */
#define CRL_IOU_SWITCH_CTRL    ( ( CRL_BASEADDR ) + 0X00000114 )

#define CRL_IOU_SWITCH_CTRL_CLKACT_SHIFT   25
#define CRL_IOU_SWITCH_CTRL_CLKACT_WIDTH   1
#define CRL_IOU_SWITCH_CTRL_CLKACT_MASK    0X02000000

#define CRL_IOU_SWITCH_CTRL_DIVISOR0_SHIFT   8
#define CRL_IOU_SWITCH_CTRL_DIVISOR0_WIDTH   10
#define CRL_IOU_SWITCH_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_IOU_SWITCH_CTRL_SRCSEL_SHIFT   0
#define CRL_IOU_SWITCH_CTRL_SRCSEL_WIDTH   3
#define CRL_IOU_SWITCH_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_GEM0_REF_CTRL
 */
#define CRL_GEM0_REF_CTRL    ( ( CRL_BASEADDR ) + 0X00000118 )

#define CRL_GEM0_REF_CTRL_CLKACT_RX_SHIFT   27
#define CRL_GEM0_REF_CTRL_CLKACT_RX_WIDTH   1
#define CRL_GEM0_REF_CTRL_CLKACT_RX_MASK    0X08000000

#define CRL_GEM0_REF_CTRL_CLKACT_TX_SHIFT   26
#define CRL_GEM0_REF_CTRL_CLKACT_TX_WIDTH   1
#define CRL_GEM0_REF_CTRL_CLKACT_TX_MASK    0X04000000

#define CRL_GEM0_REF_CTRL_CLKACT_SHIFT   25
#define CRL_GEM0_REF_CTRL_CLKACT_WIDTH   1
#define CRL_GEM0_REF_CTRL_CLKACT_MASK    0X02000000

#define CRL_GEM0_REF_CTRL_DIVISOR0_SHIFT   8
#define CRL_GEM0_REF_CTRL_DIVISOR0_WIDTH   10
#define CRL_GEM0_REF_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_GEM0_REF_CTRL_SRCSEL_SHIFT   0
#define CRL_GEM0_REF_CTRL_SRCSEL_WIDTH   3
#define CRL_GEM0_REF_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_GEM1_REF_CTRL
 */
#define CRL_GEM1_REF_CTRL    ( ( CRL_BASEADDR ) + 0X0000011C )

#define CRL_GEM1_REF_CTRL_CLKACT_RX_SHIFT   27
#define CRL_GEM1_REF_CTRL_CLKACT_RX_WIDTH   1
#define CRL_GEM1_REF_CTRL_CLKACT_RX_MASK    0X08000000

#define CRL_GEM1_REF_CTRL_CLKACT_TX_SHIFT   26
#define CRL_GEM1_REF_CTRL_CLKACT_TX_WIDTH   1
#define CRL_GEM1_REF_CTRL_CLKACT_TX_MASK    0X04000000

#define CRL_GEM1_REF_CTRL_CLKACT_SHIFT   25
#define CRL_GEM1_REF_CTRL_CLKACT_WIDTH   1
#define CRL_GEM1_REF_CTRL_CLKACT_MASK    0X02000000

#define CRL_GEM1_REF_CTRL_DIVISOR0_SHIFT   8
#define CRL_GEM1_REF_CTRL_DIVISOR0_WIDTH   10
#define CRL_GEM1_REF_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_GEM1_REF_CTRL_SRCSEL_SHIFT   0
#define CRL_GEM1_REF_CTRL_SRCSEL_WIDTH   3
#define CRL_GEM1_REF_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_GEM_TSU_REF_CTRL
 */
#define CRL_GEM_TSU_REF_CTRL    ( ( CRL_BASEADDR ) + 0X00000120 )

#define CRL_GEM_TSU_REF_CTRL_CLKACT_SHIFT   25
#define CRL_GEM_TSU_REF_CTRL_CLKACT_WIDTH   1
#define CRL_GEM_TSU_REF_CTRL_CLKACT_MASK    0X02000000

#define CRL_GEM_TSU_REF_CTRL_DIVISOR0_SHIFT   8
#define CRL_GEM_TSU_REF_CTRL_DIVISOR0_WIDTH   10
#define CRL_GEM_TSU_REF_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_GEM_TSU_REF_CTRL_SRCSEL_SHIFT   0
#define CRL_GEM_TSU_REF_CTRL_SRCSEL_WIDTH   3
#define CRL_GEM_TSU_REF_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_USB0_BUS_REF_CTRL
 */
#define CRL_USB0_BUS_REF_CTRL    ( ( CRL_BASEADDR ) + 0X00000124 )

#define CRL_USB0_BUS_REF_CTRL_CLKACT_SHIFT   25
#define CRL_USB0_BUS_REF_CTRL_CLKACT_WIDTH   1
#define CRL_USB0_BUS_REF_CTRL_CLKACT_MASK    0X02000000

#define CRL_USB0_BUS_REF_CTRL_DIVISOR0_SHIFT   8
#define CRL_USB0_BUS_REF_CTRL_DIVISOR0_WIDTH   10
#define CRL_USB0_BUS_REF_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_USB0_BUS_REF_CTRL_SRCSEL_SHIFT   0
#define CRL_USB0_BUS_REF_CTRL_SRCSEL_WIDTH   3
#define CRL_USB0_BUS_REF_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_UART0_REF_CTRL
 */
#define CRL_UART0_REF_CTRL    ( ( CRL_BASEADDR ) + 0X00000128 )

#define CRL_UART0_REF_CTRL_CLKACT_SHIFT   25
#define CRL_UART0_REF_CTRL_CLKACT_WIDTH   1
#define CRL_UART0_REF_CTRL_CLKACT_MASK    0X02000000

#define CRL_UART0_REF_CTRL_DIVISOR0_SHIFT   8
#define CRL_UART0_REF_CTRL_DIVISOR0_WIDTH   10
#define CRL_UART0_REF_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_UART0_REF_CTRL_SRCSEL_SHIFT   0
#define CRL_UART0_REF_CTRL_SRCSEL_WIDTH   3
#define CRL_UART0_REF_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_UART1_REF_CTRL
 */
#define CRL_UART1_REF_CTRL    ( ( CRL_BASEADDR ) + 0X0000012C )

#define CRL_UART1_REF_CTRL_CLKACT_SHIFT   25
#define CRL_UART1_REF_CTRL_CLKACT_WIDTH   1
#define CRL_UART1_REF_CTRL_CLKACT_MASK    0X02000000

#define CRL_UART1_REF_CTRL_DIVISOR0_SHIFT   8
#define CRL_UART1_REF_CTRL_DIVISOR0_WIDTH   10
#define CRL_UART1_REF_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_UART1_REF_CTRL_SRCSEL_SHIFT   0
#define CRL_UART1_REF_CTRL_SRCSEL_WIDTH   3
#define CRL_UART1_REF_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_SPI0_REF_CTRL
 */
#define CRL_SPI0_REF_CTRL    ( ( CRL_BASEADDR ) + 0X00000130 )

#define CRL_SPI0_REF_CTRL_CLKACT_SHIFT   25
#define CRL_SPI0_REF_CTRL_CLKACT_WIDTH   1
#define CRL_SPI0_REF_CTRL_CLKACT_MASK    0X02000000

#define CRL_SPI0_REF_CTRL_DIVISOR0_SHIFT   8
#define CRL_SPI0_REF_CTRL_DIVISOR0_WIDTH   10
#define CRL_SPI0_REF_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_SPI0_REF_CTRL_SRCSEL_SHIFT   0
#define CRL_SPI0_REF_CTRL_SRCSEL_WIDTH   3
#define CRL_SPI0_REF_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_SPI1_REF_CTRL
 */
#define CRL_SPI1_REF_CTRL    ( ( CRL_BASEADDR ) + 0X00000134 )

#define CRL_SPI1_REF_CTRL_CLKACT_SHIFT   25
#define CRL_SPI1_REF_CTRL_CLKACT_WIDTH   1
#define CRL_SPI1_REF_CTRL_CLKACT_MASK    0X02000000

#define CRL_SPI1_REF_CTRL_DIVISOR0_SHIFT   8
#define CRL_SPI1_REF_CTRL_DIVISOR0_WIDTH   10
#define CRL_SPI1_REF_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_SPI1_REF_CTRL_SRCSEL_SHIFT   0
#define CRL_SPI1_REF_CTRL_SRCSEL_WIDTH   3
#define CRL_SPI1_REF_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_CAN0_REF_CTRL
 */
#define CRL_CAN0_REF_CTRL    ( ( CRL_BASEADDR ) + 0X00000138 )

#define CRL_CAN0_REF_CTRL_CLKACT_SHIFT   25
#define CRL_CAN0_REF_CTRL_CLKACT_WIDTH   1
#define CRL_CAN0_REF_CTRL_CLKACT_MASK    0X02000000

#define CRL_CAN0_REF_CTRL_DIVISOR0_SHIFT   8
#define CRL_CAN0_REF_CTRL_DIVISOR0_WIDTH   10
#define CRL_CAN0_REF_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_CAN0_REF_CTRL_SRCSEL_SHIFT   0
#define CRL_CAN0_REF_CTRL_SRCSEL_WIDTH   3
#define CRL_CAN0_REF_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_CAN1_REF_CTRL
 */
#define CRL_CAN1_REF_CTRL    ( ( CRL_BASEADDR ) + 0X0000013C )

#define CRL_CAN1_REF_CTRL_CLKACT_SHIFT   25
#define CRL_CAN1_REF_CTRL_CLKACT_WIDTH   1
#define CRL_CAN1_REF_CTRL_CLKACT_MASK    0X02000000

#define CRL_CAN1_REF_CTRL_DIVISOR0_SHIFT   8
#define CRL_CAN1_REF_CTRL_DIVISOR0_WIDTH   10
#define CRL_CAN1_REF_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_CAN1_REF_CTRL_SRCSEL_SHIFT   0
#define CRL_CAN1_REF_CTRL_SRCSEL_WIDTH   3
#define CRL_CAN1_REF_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_I2C0_REF_CTRL
 */
#define CRL_I2C0_REF_CTRL    ( ( CRL_BASEADDR ) + 0X00000140 )

#define CRL_I2C0_REF_CTRL_CLKACT_SHIFT   25
#define CRL_I2C0_REF_CTRL_CLKACT_WIDTH   1
#define CRL_I2C0_REF_CTRL_CLKACT_MASK    0X02000000

#define CRL_I2C0_REF_CTRL_DIVISOR0_SHIFT   8
#define CRL_I2C0_REF_CTRL_DIVISOR0_WIDTH   10
#define CRL_I2C0_REF_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_I2C0_REF_CTRL_SRCSEL_SHIFT   0
#define CRL_I2C0_REF_CTRL_SRCSEL_WIDTH   3
#define CRL_I2C0_REF_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_I2C1_REF_CTRL
 */
#define CRL_I2C1_REF_CTRL    ( ( CRL_BASEADDR ) + 0X00000144 )

#define CRL_I2C1_REF_CTRL_CLKACT_SHIFT   25
#define CRL_I2C1_REF_CTRL_CLKACT_WIDTH   1
#define CRL_I2C1_REF_CTRL_CLKACT_MASK    0X02000000

#define CRL_I2C1_REF_CTRL_DIVISOR0_SHIFT   8
#define CRL_I2C1_REF_CTRL_DIVISOR0_WIDTH   10
#define CRL_I2C1_REF_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_I2C1_REF_CTRL_SRCSEL_SHIFT   0
#define CRL_I2C1_REF_CTRL_SRCSEL_WIDTH   3
#define CRL_I2C1_REF_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_DBG_LPD_CTRL
 */
#define CRL_DBG_LPD_CTRL    ( ( CRL_BASEADDR ) + 0X00000148 )

#define CRL_DBG_LPD_CTRL_CLKACT_SHIFT   25
#define CRL_DBG_LPD_CTRL_CLKACT_WIDTH   1
#define CRL_DBG_LPD_CTRL_CLKACT_MASK    0X02000000

#define CRL_DBG_LPD_CTRL_DIVISOR0_SHIFT   8
#define CRL_DBG_LPD_CTRL_DIVISOR0_WIDTH   10
#define CRL_DBG_LPD_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_DBG_LPD_CTRL_SRCSEL_SHIFT   0
#define CRL_DBG_LPD_CTRL_SRCSEL_WIDTH   3
#define CRL_DBG_LPD_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_TIMESTAMP_REF_CTRL
 */
#define CRL_TIMESTAMP_REF_CTRL    ( ( CRL_BASEADDR ) + 0X0000014C )

#define CRL_TIMESTAMP_REF_CTRL_CLKACT_SHIFT   25
#define CRL_TIMESTAMP_REF_CTRL_CLKACT_WIDTH   1
#define CRL_TIMESTAMP_REF_CTRL_CLKACT_MASK    0X02000000

#define CRL_TIMESTAMP_REF_CTRL_DIVISOR0_SHIFT   8
#define CRL_TIMESTAMP_REF_CTRL_DIVISOR0_WIDTH   10
#define CRL_TIMESTAMP_REF_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_TIMESTAMP_REF_CTRL_SRCSEL_SHIFT   0
#define CRL_TIMESTAMP_REF_CTRL_SRCSEL_WIDTH   3
#define CRL_TIMESTAMP_REF_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_SAFETY_CHK
 */
#define CRL_SAFETY_CHK    ( ( CRL_BASEADDR ) + 0X00000150 )

#define CRL_SAFETY_CHK_CHK_VAL_SHIFT   0
#define CRL_SAFETY_CHK_CHK_VAL_WIDTH   32
#define CRL_SAFETY_CHK_CHK_VAL_MASK    0XFFFFFFFF

/**
 * Register: CRL_PSM_REF_CTRL
 */
#define CRL_PSM_REF_CTRL    ( ( CRL_BASEADDR ) + 0X00000154 )

#define CRL_PSM_REF_CTRL_DIVISOR0_SHIFT   8
#define CRL_PSM_REF_CTRL_DIVISOR0_WIDTH   10
#define CRL_PSM_REF_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_PSM_REF_CTRL_SRCSEL_SHIFT   0
#define CRL_PSM_REF_CTRL_SRCSEL_WIDTH   3
#define CRL_PSM_REF_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_DBG_TSTMP_CTRL
 */
#define CRL_DBG_TSTMP_CTRL    ( ( CRL_BASEADDR ) + 0X00000158 )

#define CRL_DBG_TSTMP_CTRL_CLKACT_SHIFT   25
#define CRL_DBG_TSTMP_CTRL_CLKACT_WIDTH   1
#define CRL_DBG_TSTMP_CTRL_CLKACT_MASK    0X02000000

#define CRL_DBG_TSTMP_CTRL_DIVISOR0_SHIFT   8
#define CRL_DBG_TSTMP_CTRL_DIVISOR0_WIDTH   10
#define CRL_DBG_TSTMP_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_DBG_TSTMP_CTRL_SRCSEL_SHIFT   0
#define CRL_DBG_TSTMP_CTRL_SRCSEL_WIDTH   3
#define CRL_DBG_TSTMP_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_CPM_TOPSW_REF_CTRL
 */
#define CRL_CPM_TOPSW_REF_CTRL    ( ( CRL_BASEADDR ) + 0X0000015C )

#define CRL_CPM_TOPSW_REF_CTRL_CLKACT_SHIFT   25
#define CRL_CPM_TOPSW_REF_CTRL_CLKACT_WIDTH   1
#define CRL_CPM_TOPSW_REF_CTRL_CLKACT_MASK    0X02000000

#define CRL_CPM_TOPSW_REF_CTRL_DIVISOR0_SHIFT   8
#define CRL_CPM_TOPSW_REF_CTRL_DIVISOR0_WIDTH   10
#define CRL_CPM_TOPSW_REF_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_CPM_TOPSW_REF_CTRL_SRCSEL_SHIFT   0
#define CRL_CPM_TOPSW_REF_CTRL_SRCSEL_WIDTH   3
#define CRL_CPM_TOPSW_REF_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_USB3_DUAL_REF_CTRL
 */
#define CRL_USB3_DUAL_REF_CTRL    ( ( CRL_BASEADDR ) + 0X00000160 )

#define CRL_USB3_DUAL_REF_CTRL_CLKACT_SHIFT   25
#define CRL_USB3_DUAL_REF_CTRL_CLKACT_WIDTH   1
#define CRL_USB3_DUAL_REF_CTRL_CLKACT_MASK    0X02000000

#define CRL_USB3_DUAL_REF_CTRL_DIVISOR0_SHIFT   8
#define CRL_USB3_DUAL_REF_CTRL_DIVISOR0_WIDTH   10
#define CRL_USB3_DUAL_REF_CTRL_DIVISOR0_MASK    0X0003FF00

#define CRL_USB3_DUAL_REF_CTRL_SRCSEL_SHIFT   0
#define CRL_USB3_DUAL_REF_CTRL_SRCSEL_WIDTH   3
#define CRL_USB3_DUAL_REF_CTRL_SRCSEL_MASK    0X00000007

/**
 * Register: CRL_RCLK_CTRL
 */
#define CRL_RCLK_CTRL    ( ( CRL_BASEADDR ) + 0X000001A0 )

#define CRL_RCLK_CTRL_CLKACT_SHIFT   8
#define CRL_RCLK_CTRL_CLKACT_WIDTH   6
#define CRL_RCLK_CTRL_CLKACT_MASK    0X00003F00

#define CRL_RCLK_CTRL_SELECT_SHIFT   0
#define CRL_RCLK_CTRL_SELECT_WIDTH   6
#define CRL_RCLK_CTRL_SELECT_MASK    0X0000003F

/**
 * Register: CRL_RST_CPU_R5
 */
#define CRL_RST_CPU_R5    ( ( CRL_BASEADDR ) + 0X00000300 )

#define CRL_RST_CPU_R5_RESET_PGE_SHIFT   4
#define CRL_RST_CPU_R5_RESET_PGE_WIDTH   1
#define CRL_RST_CPU_R5_RESET_PGE_MASK    0X00000010

#define CRL_RST_CPU_R5_RESET_AMBA_SHIFT   2
#define CRL_RST_CPU_R5_RESET_AMBA_WIDTH   1
#define CRL_RST_CPU_R5_RESET_AMBA_MASK    0X00000004

#define CRL_RST_CPU_R5_RESET_CPU1_SHIFT   1
#define CRL_RST_CPU_R5_RESET_CPU1_WIDTH   1
#define CRL_RST_CPU_R5_RESET_CPU1_MASK    0X00000002

#define CRL_RST_CPU_R5_RESET_CPU0_SHIFT   0
#define CRL_RST_CPU_R5_RESET_CPU0_WIDTH   1
#define CRL_RST_CPU_R5_RESET_CPU0_MASK    0X00000001

/**
 * Register: CRL_RST_ADMA
 */
#define CRL_RST_ADMA    ( ( CRL_BASEADDR ) + 0X00000304 )

#define CRL_RST_ADMA_RESET_SHIFT   0
#define CRL_RST_ADMA_RESET_WIDTH   1
#define CRL_RST_ADMA_RESET_MASK    0X00000001

/**
 * Register: CRL_RST_GEM0
 */
#define CRL_RST_GEM0    ( ( CRL_BASEADDR ) + 0X00000308 )

#define CRL_RST_GEM0_RESET_SHIFT   0
#define CRL_RST_GEM0_RESET_WIDTH   1
#define CRL_RST_GEM0_RESET_MASK    0X00000001

/**
 * Register: CRL_RST_GEM1
 */
#define CRL_RST_GEM1    ( ( CRL_BASEADDR ) + 0X0000030C )

#define CRL_RST_GEM1_RESET_SHIFT   0
#define CRL_RST_GEM1_RESET_WIDTH   1
#define CRL_RST_GEM1_RESET_MASK    0X00000001

/**
 * Register: CRL_RST_SPARE
 */
#define CRL_RST_SPARE    ( ( CRL_BASEADDR ) + 0X00000310 )

#define CRL_RST_SPARE_RESET_SHIFT   0
#define CRL_RST_SPARE_RESET_WIDTH   1
#define CRL_RST_SPARE_RESET_MASK    0X00000001

/**
 * Register: CRL_RST_USB0
 */
#define CRL_RST_USB0    ( ( CRL_BASEADDR ) + 0X00000314 )

#define CRL_RST_USB0_RESET_SHIFT   0
#define CRL_RST_USB0_RESET_WIDTH   1
#define CRL_RST_USB0_RESET_MASK    0X00000001

/**
 * Register: CRL_RST_UART0
 */
#define CRL_RST_UART0    ( ( CRL_BASEADDR ) + 0X00000318 )

#define CRL_RST_UART0_RESET_SHIFT   0
#define CRL_RST_UART0_RESET_WIDTH   1
#define CRL_RST_UART0_RESET_MASK    0X00000001

/**
 * Register: CRL_RST_UART1
 */
#define CRL_RST_UART1    ( ( CRL_BASEADDR ) + 0X0000031C )

#define CRL_RST_UART1_RESET_SHIFT   0
#define CRL_RST_UART1_RESET_WIDTH   1
#define CRL_RST_UART1_RESET_MASK    0X00000001

/**
 * Register: CRL_RST_SPI0
 */
#define CRL_RST_SPI0    ( ( CRL_BASEADDR ) + 0X00000320 )

#define CRL_RST_SPI0_RESET_SHIFT   0
#define CRL_RST_SPI0_RESET_WIDTH   1
#define CRL_RST_SPI0_RESET_MASK    0X00000001

/**
 * Register: CRL_RST_SPI1
 */
#define CRL_RST_SPI1    ( ( CRL_BASEADDR ) + 0X00000324 )

#define CRL_RST_SPI1_RESET_SHIFT   0
#define CRL_RST_SPI1_RESET_WIDTH   1
#define CRL_RST_SPI1_RESET_MASK    0X00000001

/**
 * Register: CRL_RST_CAN0
 */
#define CRL_RST_CAN0    ( ( CRL_BASEADDR ) + 0X00000328 )

#define CRL_RST_CAN0_RESET_SHIFT   0
#define CRL_RST_CAN0_RESET_WIDTH   1
#define CRL_RST_CAN0_RESET_MASK    0X00000001

/**
 * Register: CRL_RST_CAN1
 */
#define CRL_RST_CAN1    ( ( CRL_BASEADDR ) + 0X0000032C )

#define CRL_RST_CAN1_RESET_SHIFT   0
#define CRL_RST_CAN1_RESET_WIDTH   1
#define CRL_RST_CAN1_RESET_MASK    0X00000001

/**
 * Register: CRL_RST_I2C0
 */
#define CRL_RST_I2C0    ( ( CRL_BASEADDR ) + 0X00000330 )

#define CRL_RST_I2C0_RESET_SHIFT   0
#define CRL_RST_I2C0_RESET_WIDTH   1
#define CRL_RST_I2C0_RESET_MASK    0X00000001

/**
 * Register: CRL_RST_I2C1
 */
#define CRL_RST_I2C1    ( ( CRL_BASEADDR ) + 0X00000334 )

#define CRL_RST_I2C1_RESET_SHIFT   0
#define CRL_RST_I2C1_RESET_WIDTH   1
#define CRL_RST_I2C1_RESET_MASK    0X00000001

/**
 * Register: CRL_RST_DBG_LPD
 */
#define CRL_RST_DBG_LPD    ( ( CRL_BASEADDR ) + 0X00000338 )

#define CRL_RST_DBG_LPD_RPU_DBG1_RESET_SHIFT   5
#define CRL_RST_DBG_LPD_RPU_DBG1_RESET_WIDTH   1
#define CRL_RST_DBG_LPD_RPU_DBG1_RESET_MASK    0X00000020

#define CRL_RST_DBG_LPD_RPU_DBG0_RESET_SHIFT   4
#define CRL_RST_DBG_LPD_RPU_DBG0_RESET_WIDTH   1
#define CRL_RST_DBG_LPD_RPU_DBG0_RESET_MASK    0X00000010

#define CRL_RST_DBG_LPD_RESET_HSDP_SHIFT   1
#define CRL_RST_DBG_LPD_RESET_HSDP_WIDTH   1
#define CRL_RST_DBG_LPD_RESET_HSDP_MASK    0X00000002

#define CRL_RST_DBG_LPD_RESET_SHIFT   0
#define CRL_RST_DBG_LPD_RESET_WIDTH   1
#define CRL_RST_DBG_LPD_RESET_MASK    0X00000001

/**
 * Register: CRL_RST_GPIO
 */
#define CRL_RST_GPIO    ( ( CRL_BASEADDR ) + 0X0000033C )

#define CRL_RST_GPIO_RESET_SHIFT   0
#define CRL_RST_GPIO_RESET_WIDTH   1
#define CRL_RST_GPIO_RESET_MASK    0X00000001

/**
 * Register: CRL_RST_TTC
 */
#define CRL_RST_TTC    ( ( CRL_BASEADDR ) + 0X00000344 )

#define CRL_RST_TTC_TTC3_RESET_SHIFT   3
#define CRL_RST_TTC_TTC3_RESET_WIDTH   1
#define CRL_RST_TTC_TTC3_RESET_MASK    0X00000008

#define CRL_RST_TTC_TTC2_RESET_SHIFT   2
#define CRL_RST_TTC_TTC2_RESET_WIDTH   1
#define CRL_RST_TTC_TTC2_RESET_MASK    0X00000004

#define CRL_RST_TTC_TTC1_RESET_SHIFT   1
#define CRL_RST_TTC_TTC1_RESET_WIDTH   1
#define CRL_RST_TTC_TTC1_RESET_MASK    0X00000002

#define CRL_RST_TTC_TTC0_RESET_SHIFT   0
#define CRL_RST_TTC_TTC0_RESET_WIDTH   1
#define CRL_RST_TTC_TTC0_RESET_MASK    0X00000001

/**
 * Register: CRL_RST_TIMESTAMP
 */
#define CRL_RST_TIMESTAMP    ( ( CRL_BASEADDR ) + 0X00000348 )

#define CRL_RST_TIMESTAMP_RESET_SHIFT   0
#define CRL_RST_TIMESTAMP_RESET_WIDTH   1
#define CRL_RST_TIMESTAMP_RESET_MASK    0X00000001

/**
 * Register: CRL_RST_SWDT
 */
#define CRL_RST_SWDT    ( ( CRL_BASEADDR ) + 0X0000034C )

#define CRL_RST_SWDT_RESET_SHIFT   0
#define CRL_RST_SWDT_RESET_WIDTH   1
#define CRL_RST_SWDT_RESET_MASK    0X00000001

/**
 * Register: CRL_RST_OCM
 */
#define CRL_RST_OCM    ( ( CRL_BASEADDR ) + 0X00000350 )

#define CRL_RST_OCM_RESET_SHIFT   0
#define CRL_RST_OCM_RESET_WIDTH   1
#define CRL_RST_OCM_RESET_MASK    0X00000001

/**
 * Register: CRL_RST_IPI
 */
#define CRL_RST_IPI    ( ( CRL_BASEADDR ) + 0X00000354 )

#define CRL_RST_IPI_RESET_SHIFT   0
#define CRL_RST_IPI_RESET_WIDTH   1
#define CRL_RST_IPI_RESET_MASK    0X00000001

/**
 * Register: CRL_RST_SYSMON
 */
#define CRL_RST_SYSMON    ( ( CRL_BASEADDR ) + 0X00000358 )

#define CRL_RST_SYSMON_SEQ_RST_SHIFT   1
#define CRL_RST_SYSMON_SEQ_RST_WIDTH   1
#define CRL_RST_SYSMON_SEQ_RST_MASK    0X00000002

#define CRL_RST_SYSMON_CFG_RST_SHIFT   0
#define CRL_RST_SYSMON_CFG_RST_WIDTH   1
#define CRL_RST_SYSMON_CFG_RST_MASK    0X00000001

/**
 * Register: CRL_RST_FPD
 */
#define CRL_RST_FPD    ( ( CRL_BASEADDR ) + 0X00000360 )

#define CRL_RST_FPD_SRST_SHIFT   1
#define CRL_RST_FPD_SRST_WIDTH   1
#define CRL_RST_FPD_SRST_MASK    0X00000002

#define CRL_RST_FPD_POR_SHIFT   0
#define CRL_RST_FPD_POR_WIDTH   1
#define CRL_RST_FPD_POR_MASK    0X00000001

/**
 * Register: CRL_RST_OCM2
 */
#define CRL_RST_OCM2    ( ( CRL_BASEADDR ) + 0X00000364 )

#define CRL_RST_OCM2_SRST_SHIFT   1
#define CRL_RST_OCM2_SRST_WIDTH   1
#define CRL_RST_OCM2_SRST_MASK    0X00000002

#define CRL_RST_OCM2_POR_SHIFT   0
#define CRL_RST_OCM2_POR_WIDTH   1
#define CRL_RST_OCM2_POR_MASK    0X00000001

/**
 * Register: CRL_PSM_RST_MODE
 */
#define CRL_PSM_RST_MODE    ( ( CRL_BASEADDR ) + 0X00000370 )

#define CRL_PSM_RST_MODE_WAKEUP_SHIFT   2
#define CRL_PSM_RST_MODE_WAKEUP_WIDTH   1
#define CRL_PSM_RST_MODE_WAKEUP_MASK    0X00000004

#define CRL_PSM_RST_MODE_RST_MODE_SHIFT   0
#define CRL_PSM_RST_MODE_RST_MODE_WIDTH   2
#define CRL_PSM_RST_MODE_RST_MODE_MASK    0X00000003

#ifdef __cplusplus
}
#endif


#endif /* _CRL_H_ */
