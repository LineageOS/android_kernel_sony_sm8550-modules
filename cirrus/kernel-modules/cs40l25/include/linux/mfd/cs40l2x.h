/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Internal data for CS40L20/CS40L25/CS40L25A/CS40L25B
 *
 * Copyright (C) 2018-2020 Cirrus Logic, Inc.
 */

#ifndef __CS40L2X_H__
#define __CS40L2X_H__

#include <linux/regmap.h>

#ifdef CONFIG_ANDROID_TIMED_OUTPUT
#include "../../../drivers/staging/android/timed_output.h"
#else
#include <linux/leds.h>
#endif

#include <linux/regulator/consumer.h>
#include <linux/hrtimer.h>
#include <linux/workqueue.h>
#include <linux/mutex.h>
#include <linux/completion.h>
#include <linux/firmware.h>
#include <linux/platform_data/cs40l2x.h>
#include <linux/input.h>

#include <linux/mfd/cs40l25-wavetable.h>

#define CS40L2X_FIRSTREG			0x00000000
#define CS40L2X_LASTREG				0x03804FE8

#define CS40L2X_DEVID				0x00000000
#define CS40L2X_REVID				0x00000004
#define CS40L2X_OTPID				0x00000010
#define CS40L2X_TEST_KEY_CTL			0x00000040
#define CS40L2X_OTP_MEM0			0x00000400
#define CS40L2X_OTP_MEM31			0x0000047C
#define CS40L2X_GLOBAL_ENABLES			0x00002014
#define CS40L2X_BLOCK_ENABLES			0x00002018
#define CS40L2X_BLOCK_ENABLES2			0x0000201C
#define CS40L2X_GLOBAL_OVERRIDES		0x00002020
#define CS40L2X_GLOBAL_SYNC			0x00002024
#define CS40L2X_ERROR_RELEASE			0x00002034
#define CS40L2X_LRCK_PAD_CONTROL		0x00002418
#define CS40L2X_SDIN_PAD_CONTROL		0x00002420
#define CS40L2X_GPIO_PAD_CONTROL		0x0000242C
#define CS40L2X_PWRMGT_CTL			0x00002900
#define CS40L2X_WAKESRC_CTL			0x00002904
#define CS40L2X_PWRMGT_STS			0x00002908
#define CS40L2X_REFCLK_INPUT			0x00002C04
#define CS40L2X_GLOBAL_SAMPLE_RATE		0x00002C0C
#define CS40L2X_FS_MON_0			0x00002D10
#define CS40L2X_VBST_CTL_1			0x00003800
#define CS40L2X_VBST_CTL_2			0x00003804
#define CS40L2X_BST_IPK_CTL			0x00003808
#define CS40L2X_SOFT_RAMP			0x0000380C
#define CS40L2X_BST_LOOP_COEFF			0x00003810
#define CS40L2X_LBST_SLOPE			0x00003814
#define CS40L2X_BST_SW_FREQ			0x00003818
#define CS40L2X_BST_DCM_CTL			0x0000381C
#define CS40L2X_DCM_FORCE			0x00003820
#define CS40L2X_VBST_OVP			0x00003830
#define CS40L2X_TEST_LBST			0x0000391C
#define CS40L2X_WARM_LIMIT_THRESHOLD		0x00004220
#define CS40L2X_CONFIGURATION			0x00004224
#define CS40L2X_ENABLES_AND_CODES_DIG		0x00004308
#define CS40L2X_ASP_ENABLES1			0x00004800
#define CS40L2X_ASP_CONTROL1			0x00004804
#define CS40L2X_ASP_CONTROL2			0x00004808
#define CS40L2X_ASP_CONTROL3			0x0000480C
#define CS40L2X_ASP_FRAME_CONTROL5		0x00004820
#define CS40L2X_ASP_DATA_CONTROL5		0x00004840
#define CS40L2X_DACPCM1_INPUT			0x00004C00
#define CS40L2X_DSP1RX1_INPUT			0x00004C40
#define CS40L2X_DSP1RX2_INPUT			0x00004C44
#define CS40L2X_DSP1RX3_INPUT			0x00004C48
#define CS40L2X_DSP1RX4_INPUT			0x00004C4C
#define CS40L2X_DSP1RX5_INPUT			0x00004C50
#define CS40L2X_DSP1RX6_INPUT			0x00004C54
#define CS40L2X_DSP1RX7_INPUT			0x00004C58
#define CS40L2X_DSP1RX8_INPUT			0x00004C5C
#define CS40L2X_NGATE1_INPUT			0x00004C60
#define CS40L2X_NGATE2_INPUT			0x00004C64
#define CS40L2X_AMP_CTRL			0x00006000
#define CS40L2X_VPBR_CONFIG			0x00006404
#define CS40L2X_VBBR_CONFIG			0x00006408
#define CS40L2X_VPBR_STATUS			0x0000640C
#define CS40L2X_VBBR_STATUS			0x00006410
#define CS40L2X_OTW_CONFIG			0x00006414
#define CS40L2X_AMP_ERROR_VOL_SEL		0x00006418
#define CS40L2X_VOL_STATUS_TO_DSP		0x00006450
#define CS40L2X_CLASSH_CONFIG			0x00006800
#define CS40L2X_WKFET_AMP_CONFIG		0x00006804
#define CS40L2X_NG_CONFIG			0x00006808
#define CS40L2X_AMP_GAIN			0x00006C04
#define CS40L2X_SPK_FORCE_TST_1			0x00007428
#define CS40L2X_IRQ1_CFG			0x00010000
#define CS40L2X_IRQ1_STATUS			0x00010004
#define CS40L2X_IRQ1_EINT_1			0x00010010
#define CS40L2X_IRQ1_EINT_2			0x00010014
#define CS40L2X_IRQ1_EINT_3			0x00010018
#define CS40L2X_IRQ1_EINT_4			0x0001001C
#define CS40L2X_IRQ1_STS_1			0x00010090
#define CS40L2X_IRQ1_STS_2			0x00010094
#define CS40L2X_IRQ1_STS_3			0x00010098
#define CS40L2X_IRQ1_STS_4			0x0001009C
#define CS40L2X_IRQ1_MASK_1			0x00010110
#define CS40L2X_IRQ1_MASK_2			0x00010114
#define CS40L2X_IRQ1_MASK_3			0x00010118
#define CS40L2X_IRQ1_MASK_4			0x0001011C
#define CS40L2X_IRQ1_EDGE_1			0x00010210
#define CS40L2X_IRQ1_EDGE_4			0x0001021C
#define CS40L2X_IRQ1_POL_1			0x00010290
#define CS40L2X_IRQ1_POL_4			0x0001029C
#define CS40L2X_IRQ1_DB_3			0x00010318
#define CS40L2X_IRQ2_CFG			0x00010800
#define CS40L2X_IRQ2_STATUS			0x00010804
#define CS40L2X_IRQ2_EINT_1			0x00010810
#define CS40L2X_IRQ2_EINT_2			0x00010814
#define CS40L2X_IRQ2_EINT_3			0x00010818
#define CS40L2X_IRQ2_EINT_4			0x0001081C
#define CS40L2X_IRQ2_STS_1			0x00010890
#define CS40L2X_IRQ2_STS_2			0x00010894
#define CS40L2X_IRQ2_STS_3			0x00010898
#define CS40L2X_IRQ2_STS_4			0x0001089C
#define CS40L2X_IRQ2_MASK_1			0x00010910
#define CS40L2X_IRQ2_MASK_2			0x00010914
#define CS40L2X_IRQ2_MASK_3			0x00010918
#define CS40L2X_IRQ2_MASK_4			0x0001091C
#define CS40L2X_IRQ2_EDGE_1			0x00010A10
#define CS40L2X_IRQ2_EDGE_4			0x00010A1C
#define CS40L2X_IRQ2_POL_1			0x00010A90
#define CS40L2X_IRQ2_POL_4			0x00010A9C
#define CS40L2X_IRQ2_DB_3			0x00010B18
#define CS40L2X_GPIO_STATUS1			0x00011000
#define CS40L2X_GPIO1_CTRL1			0x00011008
#define CS40L2X_GPIO2_CTRL1			0x0001100C
#define CS40L2X_GPIO3_CTRL1			0x00011010
#define CS40L2X_GPIO4_CTRL1			0x00011014
#define CS40L2X_DSP_MBOX_1			0x00013000
#define CS40L2X_DSP_MBOX_2			0x00013004
#define CS40L2X_DSP_MBOX_3			0x00013008
#define CS40L2X_DSP_MBOX_4			0x0001300C
#define CS40L2X_DSP_MBOX_5			0x00013010
#define CS40L2X_DSP_MBOX_6			0x00013014
#define CS40L2X_DSP_MBOX_7			0x00013018
#define CS40L2X_DSP_MBOX_8			0x0001301C
#define CS40L2X_DSP_VIRTUAL1_MBOX_1		0x00013020
#define CS40L2X_DSP_VIRTUAL1_MBOX_2		0x00013024
#define CS40L2X_DSP_VIRTUAL1_MBOX_3		0x00013028
#define CS40L2X_DSP_VIRTUAL1_MBOX_4		0x0001302C
#define CS40L2X_DSP_VIRTUAL1_MBOX_5		0x00013030
#define CS40L2X_DSP_VIRTUAL1_MBOX_6		0x00013034
#define CS40L2X_DSP_VIRTUAL1_MBOX_7		0x00013038
#define CS40L2X_DSP_VIRTUAL1_MBOX_8		0x0001303C
#define CS40L2X_DSP_VIRTUAL2_MBOX_1		0x00013040
#define CS40L2X_DSP_VIRTUAL2_MBOX_2		0x00013044
#define CS40L2X_DSP_VIRTUAL2_MBOX_3		0x00013048
#define CS40L2X_DSP_VIRTUAL2_MBOX_4		0x0001304C
#define CS40L2X_DSP_VIRTUAL2_MBOX_5		0x00013050
#define CS40L2X_DSP_VIRTUAL2_MBOX_6		0x00013054
#define CS40L2X_DSP_VIRTUAL2_MBOX_7		0x00013058
#define CS40L2X_DSP_VIRTUAL2_MBOX_8		0x0001305C
#define CS40L2X_CLOCK_DETECT_1			0x00014000
#define CS40L2X_DSP1_XMEM_PACK_0		0x02000000
#define CS40L2X_DSP1_XMEM_PACK_3068		0x02002FF0
#define CS40L2X_DSP1_AHBM_WINDOW_DEBUG_0	0x025E2040
#define CS40L2X_DSP1_AHBM_WINDOW_DEBUG_1	0x025E2044
#define CS40L2X_DSP1_XMEM_UNPACK24_0		0x02800000
#define CS40L2X_DSP1_XMEM_UNPACK24_4093		0x02803FF4
#define CS40L2X_DSP1_CTRL_BASE			0x02B80000
#define CS40L2X_DSP1_CORE_SOFT_RESET		0x02B80010
#define CS40L2X_DSP1_SAMPLE_RATE_RX1		0x02B80080
#define CS40L2X_DSP1_SAMPLE_RATE_RX2		0x02B80088
#define CS40L2X_DSP1_SAMPLE_RATE_RX3		0x02B80090
#define CS40L2X_DSP1_SAMPLE_RATE_RX4		0x02B80098
#define CS40L2X_DSP1_SAMPLE_RATE_RX5		0x02B800A0
#define CS40L2X_DSP1_SAMPLE_RATE_RX6		0x02B800A8
#define CS40L2X_DSP1_SAMPLE_RATE_RX7		0x02B800B0
#define CS40L2X_DSP1_SAMPLE_RATE_RX8		0x02B800B8
#define CS40L2X_DSP1_SAMPLE_RATE_TX1		0x02B80280
#define CS40L2X_DSP1_SAMPLE_RATE_TX2		0x02B80288
#define CS40L2X_DSP1_SAMPLE_RATE_TX3		0x02B80290
#define CS40L2X_DSP1_SAMPLE_RATE_TX4		0x02B80298
#define CS40L2X_DSP1_SAMPLE_RATE_TX5		0x02B802A0
#define CS40L2X_DSP1_SAMPLE_RATE_TX6		0x02B802A8
#define CS40L2X_DSP1_SAMPLE_RATE_TX7		0x02B802B0
#define CS40L2X_DSP1_SAMPLE_RATE_TX8		0x02B802B8
#define CS40L2X_DSP1_SCRATCH1			0x02B805C0
#define CS40L2X_DSP1_SCRATCH2			0x02B805C8
#define CS40L2X_DSP1_SCRATCH3			0x02B805D0
#define CS40L2X_DSP1_SCRATCH4			0x02B805D8
#define CS40L2X_DSP1_CCM_CORE_CONTROL		0x02BC1000
#define CS40L2X_DSP1_MPU_XM_ACCESS_0		0x02BC3000
#define CS40L2X_DSP1_MPU_YM_ACCESS_0		0x02BC3004
#define CS40L2X_DSP1_MPU_WINDOW_ACCESS_0	0x02BC3008
#define CS40L2X_DSP1_MPU_XREG_ACCESS_0		0x02BC300C
#define CS40L2X_DSP1_MPU_YREG_ACCESS_0		0x02BC3014
#define CS40L2X_DSP1_MPU_XM_ACCESS_1		0x02BC3018
#define CS40L2X_DSP1_MPU_YM_ACCESS_1		0x02BC301C
#define CS40L2X_DSP1_MPU_WINDOW_ACCESS_1	0x02BC3020
#define CS40L2X_DSP1_MPU_XREG_ACCESS_1		0x02BC3024
#define CS40L2X_DSP1_MPU_YREG_ACCESS_1		0x02BC302C
#define CS40L2X_DSP1_MPU_XM_ACCESS_2		0x02BC3030
#define CS40L2X_DSP1_MPU_YM_ACCESS_2		0x02BC3034
#define CS40L2X_DSP1_MPU_WINDOW_ACCESS_2	0x02BC3038
#define CS40L2X_DSP1_MPU_XREG_ACCESS_2		0x02BC303C
#define CS40L2X_DSP1_MPU_YREG_ACCESS_2		0x02BC3044
#define CS40L2X_DSP1_MPU_XM_ACCESS_3		0x02BC3048
#define CS40L2X_DSP1_MPU_YM_ACCESS_3		0x02BC304C
#define CS40L2X_DSP1_MPU_WINDOW_ACCESS_3	0x02BC3050
#define CS40L2X_DSP1_MPU_XREG_ACCESS_3		0x02BC3054
#define CS40L2X_DSP1_MPU_YREG_ACCESS_3		0x02BC305C
#define CS40L2X_DSP1_MPU_XM_VIO_ADDR		0x02BC3100
#define CS40L2X_DSP1_MPU_XM_VIO_STATUS		0x02BC3104
#define CS40L2X_DSP1_MPU_YM_VIO_ADDR		0x02BC3108
#define CS40L2X_DSP1_MPU_YM_VIO_STATUS		0x02BC310C
#define CS40L2X_DSP1_MPU_PM_VIO_ADDR		0x02BC3110
#define CS40L2X_DSP1_MPU_PM_VIO_STATUS		0x02BC3114
#define CS40L2X_DSP1_MPU_LOCK_CONFIG		0x02BC3140
#define CS40L2X_DSP1_YMEM_PACK_0		0x02C00000
#define CS40L2X_DSP1_YMEM_PACK_1532		0x02C017F0
#define CS40L2X_DSP1_YMEM_UNPACK24_0		0x03400000
#define CS40L2X_DSP1_YMEM_UNPACK24_2045		0x03401FF4
#define CS40L2X_DSP1_PMEM_0			0x03800000
#define CS40L2X_DSP1_PMEM_5114			0x03804FE8

/* trim fields unpacked from OTP memory */
#define CS40L2X_OTP_TRIM_1			0x0000208C
#define CS40L2X_OTP_TRIM_2			0x00002090
#define CS40L2X_OTP_TRIM_3			0x00003010
#define CS40L2X_OTP_TRIM_4			0x0000300C
#define CS40L2X_OTP_TRIM_5			0x0000394C
#define CS40L2X_OTP_TRIM_6			0x00003950
#define CS40L2X_OTP_TRIM_7			0x00003954
#define CS40L2X_OTP_TRIM_8			0x00003958
#define CS40L2X_OTP_TRIM_9			0x0000395C
#define CS40L2X_OTP_TRIM_10			0x0000416C
#define CS40L2X_OTP_TRIM_11			0x00004160
#define CS40L2X_OTP_TRIM_12			0x00004170
#define CS40L2X_OTP_TRIM_13			0x00004360
#define CS40L2X_OTP_TRIM_14			0x00004448
#define CS40L2X_OTP_TRIM_15			0x0000444C
#define CS40L2X_OTP_TRIM_16			0x00006E30
#define CS40L2X_OTP_TRIM_17			0x00006E34
#define CS40L2X_OTP_TRIM_18			0x00006E38
#define CS40L2X_OTP_TRIM_19			0x00006E3C
#define CS40L2X_OTP_TRIM_20			0x00006E40
#define CS40L2X_OTP_TRIM_21			0x00006E44
#define CS40L2X_OTP_TRIM_22			0x00006E48
#define CS40L2X_OTP_TRIM_23			0x00006E4C
#define CS40L2X_OTP_TRIM_24			0x00006E50
#define CS40L2X_OTP_TRIM_25			0x00006E54
#define CS40L2X_OTP_TRIM_26			0x00006E58
#define CS40L2X_OTP_TRIM_27			0x00006E5C
#define CS40L2X_OTP_TRIM_28			0x00006E60
#define CS40L2X_OTP_TRIM_29			0x00006E64
#define CS40L2X_OTP_TRIM_30			0x00007418
#define CS40L2X_OTP_TRIM_31			0x0000741C
#define CS40L2X_OTP_TRIM_32			0x00007434
#define CS40L2X_OTP_TRIM_33			0x00007068
#define CS40L2X_OTP_TRIM_34			0x0000410C
#define CS40L2X_OTP_TRIM_35			0x0000400C
#define CS40L2X_OTP_TRIM_36			0x00002030

/* basic mode (ROM) fields */
#define CS40L2X_BASIC_HALO_STATE		0x02800154
#define CS40L2X_BASIC_HALO_HEARTBEAT		0x02800158
#define CS40L2X_BASIC_STATEMACHINE		0X0280015C
#define CS40L2X_BASIC_F0_STORED			0X02800174
#define CS40L2X_BASIC_GPIO_TRIGGER_EDGE		0x02800178
#define CS40L2X_BASIC_BUZZ_FREQ			0x0280017C
#define CS40L2X_BASIC_BUZZ_LEVEL		0x02800180
#define CS40L2X_BASIC_BUZZ_DURATION		0x02800184
#define CS40L2X_BASIC_BUZZ_TRIGGER		0x02800188
#define CS40L2X_BASIC_AMP_STATUS		0x0280018C
#define CS40L2X_BASIC_SHUTDOWNREQUEST		0x02800190

/* basic mode (ROM) states */
#define CS40L2X_BASIC_IDLE			0
#define CS40L2X_BASIC_PLAY_TONE			1
#define CS40L2X_BASIC_CONTINUE_TONE		2
#define CS40L2X_BASIC_SHUTTINGDOWN		3
#define CS40L2X_BASIC_SHUTDOWN			4

/* basic mode (ROM) status flags */
#define CS40L2X_BASIC_NO_STATUS			0x00
#define CS40L2X_BASIC_BOOT_DONE			0x01
#define CS40L2X_BASIC_OTP_ERROR			0x02
#define CS40L2X_BASIC_AMP_ERROR			0x04
#define CS40L2X_BASIC_TEMP_RISE_WARN		0x08
#define CS40L2X_BASIC_TEMP_ERROR		0x10

#define CS40L2X_GLOBAL_EN_MASK			0x00000001
#define CS40L2X_GLOBAL_EN_SHIFT			0

#define CS40L2X_BST_EN_MASK			0x00000030
#define CS40L2X_BST_EN_SHIFT			4
#define CS40L2X_BST_DISABLED			0
#define CS40L2X_BST_BYPASS			1
#define CS40L2X_BST_ENABLED			2

#define CS40L2X_CLASSH_EN_MASK			BIT(4)
#define CS40L2X_CLASSH_EN_SHIFT			4

#define CS40L2X_VBBR_EN_MASK			0x00002000
#define CS40L2X_VBBR_EN_SHIFT			13

#define CS40L2X_VPBR_EN_MASK			0x00001000
#define CS40L2X_VPBR_EN_SHIFT			12

#define CS40L2X_DCM_DISABLE			0

#define CS40L2X_GP2_CTRL_MASK			0x07000000
#define CS40L2X_GP2_CTRL_SHIFT			24
#define CS40L2X_GP1_CTRL_MASK			0x00070000
#define CS40L2X_GP1_CTRL_SHIFT			16
#define CS40L2X_GPx_CTRL_GPIO			0x1
#define CS40L2X_GPx_CTRL_MCLK			0x3

#define CS40L2X_MEM_RDY_MASK			0x00000002
#define CS40L2X_MEM_RDY_SHIFT			1

#define CS40L2X_TRIG_HIBER_MASK			0x00000001
#define CS40L2X_TRIG_HIBER_SHIFT		0

#define CS40L2X_UPDT_WKCTL_MASK			0x00000100
#define CS40L2X_UPDT_WKCTL_SHIFT		8

#define CS40L2X_WKSRC_POL_MASK			0x0000000F
#define CS40L2X_WKSRC_POL_SHIFT			0
#define CS40L2X_WKSRC_POL_GPIO1			1
#define CS40L2X_WKSRC_POL_GPIO2			2
#define CS40L2X_WKSRC_POL_GPIO4			4
#define CS40L2X_WKSRC_POL_SDA			8

#define CS40L2X_WKSRC_EN_MASK			0x000000F0
#define CS40L2X_WKSRC_EN_SHIFT			4
#define CS40L2X_WKSRC_EN_GPIO1			1
#define CS40L2X_WKSRC_EN_GPIO2			2
#define CS40L2X_WKSRC_EN_GPIO4			4
#define CS40L2X_WKSRC_EN_SDA			8

#define CS40L2X_WR_PEND_STS_MASK		0x2
#define CS40L2X_WR_PEND_STS_SHIFT		1

#define CS40L2X_PLL_REFCLK_SEL_MASK		0x00000007
#define CS40L2X_PLL_REFCLK_SEL_SHIFT		0
#define CS40L2X_PLL_REFCLK_SEL_BCLK		0x0
#define CS40L2X_PLL_REFCLK_SEL_MCLK		0x5

#define CS40L2X_PLL_REFCLK_EN_MASK		0x00000010
#define CS40L2X_PLL_REFCLK_EN_SHIFT		4

#define CS40L2X_PLL_REFCLK_FREQ_MASK		0x000007E0
#define CS40L2X_PLL_REFCLK_FREQ_SHIFT		5
#define CS40L2X_PLL_REFCLK_FREQ_32K		32768
#define CS40L2X_NUM_REFCLKS			64

#define CS40L2X_PLL_OPEN_LOOP_MASK		BIT(11)
#define CS40L2X_PLL_OPEN_LOOP_SHIFT		11

#define CS40L2X_ASP_RX1_EN_MASK			0x00010000
#define CS40L2X_ASP_RX1_EN_SHIFT		16

#define CS40L2X_ASP_BCLK_FREQ_MASK		0x0000003F
#define CS40L2X_ASP_BCLK_FREQ_SHIFT		0

#define CS40L2X_ASP_RX_WIDTH_MASK		0xFF000000
#define CS40L2X_ASP_RX_WIDTH_SHIFT		24
#define CS40L2X_ASP_RX_WIDTH_MIN		12
#define CS40L2X_ASP_RX_WIDTH_MAX		128

#define CS40L2X_ASP_FMT_MASK			0x00000700
#define CS40L2X_ASP_FMT_SHIFT			8
#define CS40L2X_ASP_FMT_TDM1			0x0
#define CS40L2X_ASP_FMT_I2S			0x2
#define CS40L2X_ASP_FMT_TDM1R5			0x4

#define CS40L2X_ASP_BCLK_INV_MASK		0x00000040
#define CS40L2X_ASP_BCLK_INV_SHIFT		6

#define CS40L2X_ASP_FSYNC_INV_MASK		0x00000004
#define CS40L2X_ASP_FSYNC_INV_SHIFT		2

#define CS40L2X_ASP_RX1_SLOT_MASK		0x0000003F
#define CS40L2X_ASP_RX1_SLOT_SHIFT		0
#define CS40L2X_ASP_RX1_SLOT_MIN		0
#define CS40L2X_ASP_RX1_SLOT_MAX		63

#define CS40L2X_ASP_RX2_SLOT_MASK		GENMASK(13, 8)
#define CS40L2X_ASP_RX2_SLOT_SHIFT		8

#define CS40L2X_ASP_RX_WL_MASK			0x0000003F
#define CS40L2X_ASP_RX_WL_SHIFT			0
#define CS40L2X_ASP_RX_WL_MIN			12
#define CS40L2X_ASP_RX_WL_MAX			24

#define CS40L2X_DACPCM1_SRC_DSP1TX1		0x32
#define CS40L2X_DSP1_RXn_SRC_ASPRX1		0x08
#define CS40L2X_DSP1_RXn_SRC_ASPRX2		0x09
#define CS40L2X_DSP1_RXn_SRC_VMON		0x18
#define CS40L2X_DSP1_RXn_SRC_IMON		0x19
#define CS40L2X_DSP1_RXn_SRC_VPMON		0x28
#define CS40L2X_DSP1_RXn_SRC_VBSTMON		0x29

#define CS40L2X_DSP1_CCM_CORE_RESET_MASK	0x200
#define CS40L2X_DSP1_CCM_CORE_RESET_SHIFT	9

#define CS40L2X_DSP1_CCM_CORE_EN_MASK		0x1
#define CS40L2X_DSP1_CCM_CORE_EN_SHIFT		0

#define CS40L2X_BST_CTL_MASK			0x000000FF
#define CS40L2X_BST_CTL_SHIFT			0
#define CS40L2X_BST_VOLT_MIN			2550  /* millivolts */
#define CS40L2X_BST_VOLT_MAX			11000 /* millivolts */

#define CS40L2X_BST_CTL_LIM_EN_MASK		0x00000004
#define CS40L2X_BST_CTL_LIM_EN_SHIFT		2

#define CS40L2X_BST_CTL_SEL_MASK		0x00000003
#define CS40L2X_BST_CTL_SEL_SHIFT		0
#define CS40L2X_BST_CTL_SEL_CP_VAL		0
#define CS40L2X_BST_CTL_SEL_CLASSH		1

#define CS40L2X_BST_IPK_MASK			0x0000007F
#define CS40L2X_BST_IPK_SHIFT			0

#define CS40L2X_BST_K1_MASK			0x000000FF
#define CS40L2X_BST_K1_SHIFT			0
#define CS40L2X_BST_K2_MASK			0x0000FF00
#define CS40L2X_BST_K2_SHIFT			8

#define CS40L2X_BST_SLOPE_MASK			0x0000FF00
#define CS40L2X_BST_SLOPE_SHIFT			8

#define CS40L2X_BST_LBST_VAL_MASK		0x00000003
#define CS40L2X_BST_LBST_VAL_SHIFT		0

#define CS40L2X_BST_OVP_EN_MASK			0x00000100
#define CS40L2X_BST_OVP_EN_SHIFT		8

#define CS40L2X_BST_OVP_THLD_MASK		0x0000003F
#define CS40L2X_BST_OVP_THLD_SHIFT		0

#define CS40L2X_AMP_HPF_PCM_EN_MASK		0x00008000
#define CS40L2X_AMP_HPF_PCM_EN_SHIFT		15

#define CS40L2X_AMP_VOL_PCM_MASK		0x00003FF8
#define CS40L2X_AMP_VOL_PCM_SHIFT		3

#define CS40L2X_VxBR_MUTE_EN_MASK		0x01000000

#define CS40L2X_VxBR_REL_RATE_MASK		0x00E00000
#define CS40L2X_VxBR_REL_RATE_SHIFT		21
#define CS40L2X_VxBR_REL_RATE_MAX		7

#define CS40L2X_VxBR_WAIT_MASK			0x00180000
#define CS40L2X_VxBR_WAIT_SHIFT			19
#define CS40L2X_VxBR_WAIT_MAX			3

#define CS40L2X_VxBR_ATK_RATE_MASK		0x00070000
#define CS40L2X_VxBR_ATK_RATE_SHIFT		16
#define CS40L2X_VxBR_ATK_RATE_MAX		7

#define CS40L2X_VxBR_ATK_VOL_MASK		0x0000F000
#define CS40L2X_VxBR_ATK_VOL_SHIFT		12
#define CS40L2X_VxBR_ATK_VOL_MAX		7

#define CS40L2X_VxBR_MAX_ATT_MASK		0x00000F00
#define CS40L2X_VxBR_MAX_ATT_SHIFT		8
#define CS40L2X_VxBR_MAX_ATT_MAX		15

#define CS40L2X_VxBR_THLD1_SHIFT		0
#define CS40L2X_VPBR_THLD1_MASK			0x0000001F
#define CS40L2X_VPBR_THLD1_MAX			0x1F
#define CS40L2X_VBBR_THLD1_MASK			0x0000003F
#define CS40L2X_VBBR_THLD1_MAX			0x3F

#define CS40L2X_GAIN_CTRL_GPIO_MASK		0x00FFC000
#define CS40L2X_GAIN_CTRL_GPIO_SHIFT		14

#define CS40L2X_GAIN_CTRL_TRIG_MASK		0x00003FF0
#define CS40L2X_GAIN_CTRL_TRIG_SHIFT		4

#define CS40L2X_GPIO_GAIN_RISE_MASK		0x00FFC000
#define CS40L2X_GPIO_GAIN_RISE_SHIFT		14

#define CS40L2X_GPIO_GAIN_FALL_MASK		0x00003FF0
#define CS40L2X_GPIO_GAIN_FALL_SHIFT		4

#define CS40L2X_NUM_HW_ERRS			6
#define CS40L2X_HW_ERR_COUNT_MAX		10

#define CS40L2X_AMP_ERR				0x80000000
#define CS40L2X_TEMP_ERR			0x00020000
#define CS40L2X_TEMP_RISE_WARN			0x00008000
#define CS40L2X_BST_SHORT_ERR			0x00000100
#define CS40L2X_BST_UVP_ERR			0x00000080
#define CS40L2X_BST_OVP_ERR			0x00000040

#define CS40L2X_TEMP_ERR_RLS			0x00000040
#define CS40L2X_TEMP_RISE_WARN_RLS		0x00000020
#define CS40L2X_BST_UVP_ERR_RLS			0x00000010
#define CS40L2X_BST_OVP_ERR_RLS			0x00000008
#define CS40L2X_BST_SHORT_ERR_RLS		0x00000004
#define CS40L2X_AMP_ERR_RLS			0x00000002

#define CS40L2X_OTP_BOOT_ERR			0x80000000
#define CS40L2X_OTP_BOOT_DONE			0x00000002

#define CS40L2X_EXPL_MODE_EN			0x004DC080
#define CS40L2X_EXPL_MODE_DIS			0x014DC080

#define CS40L2X_FORCE_SPK_FREE			0x00000000
#define CS40L2X_FORCE_SPK_GND			0x00D02800

#define CS40L2X_DEVID_L20			0x035A40
#define CS40L2X_DEVID_L25			0x40A250
#define CS40L2X_DEVID_L25A			0x40A25A
#define CS40L2X_DEVID_L25B			0x40A25B

#define CS40L2X_REVID_A0			0xA0
#define CS40L2X_REVID_B0			0xB0
#define CS40L2X_REVID_B1			0xB1

#define CS40L2X_MPU_UNLOCK_CODE1		0x5555
#define CS40L2X_MPU_UNLOCK_CODE2		0xAAAA

#define CS40L2X_XM_UNPACKED_TYPE		0x0005
#define CS40L2X_YM_UNPACKED_TYPE		0x0006
#define CS40L2X_PM_PACKED_TYPE			0x0010
#define CS40L2X_XM_PACKED_TYPE			0x0011
#define CS40L2X_YM_PACKED_TYPE			0x0012
#define CS40L2X_ALGO_INFO_TYPE			0x00F2
#define CS40L2X_WMFW_INFO_TYPE			0x00FF
#define CS40L2X_WMDR_NAME_TYPE			0xFE00
#define CS40L2X_WMDR_INFO_TYPE			0xFF00

#define CS40L2X_FW_FILE_HEADER_SIZE		40
#define CS40L2X_FW_DBLK_OFFSET_SIZE		3
#define CS40L2X_FW_DBLK_TYPE_SIZE		1
#define CS40L2X_FW_DBLK_LENGTH_SIZE		4

#define CS40L2X_CLAB_CONFIG_FILE_NAME		"cs40l25a_clab.bin"
#define CS40L2X_PAR_CONFIG_FILE_NAME		"cs40l25a_par.bin"
#define CS40L2X_WT_FILE_DATE_MISSING		"N/A"
#define CS40L2X_WT_FILE_DATE_LEN_MAX		16
#define CS40L2X_WT_FILE_NAME_MISSING		"N/A"
#define CS40L2X_WT_FILE_NAME_DEFAULT		"cs40l20.bin"
#define CS40L2X_WT_FILE_NAME_LEN_MAX		32
#define CS40L2X_WT_FILE_HEADER_SIZE		16
#define CS40L2X_WT_DBLK_OFFSET_SIZE		2
#define CS40L2X_WT_DBLK_TYPE_SIZE		2
#define CS40L2X_WT_ALGO_ID_SIZE			4
#define CS40L2X_WT_ALGO_REV_SIZE		4
#define CS40L2X_WT_SAMPLE_RATE_SIZE		4
#define CS40L2X_WT_DBLK_LENGTH_SIZE		4
#define CS40L2X_WT_TYPE_10_COMP_FILE		10
#define CS40L2X_WT_TYPE_12_PWLE_FILE		12
#define CS40L2X_WT_NUM_GPIO_VSLOTS		2
#define CS40L2X_WT_NUM_COMP_VSLOTS		1
#define CS40L2X_WT_MAX_VIRT_WAVS		500
#define CS40L2X_WT_MAX_BIN_SIZE			9584

#define CS40L2X_WT_NUM_VIRT_SLOTS	(\
	CS40L2X_WT_NUM_COMP_VSLOTS +\
	CS40L2X_WT_NUM_GPIO_VSLOTS)

#define CS40L2X_MAX_WAVEFORMS			128
#define CS40L2X_OWT_CALC_SIZE			(CS40L2X_MAX_WAVEFORMS * 2)

#define CS40L2X_XM_FW_ID			(CS40L2X_DSP1_XMEM_UNPACK24_0 + 12)
#define CS40L2X_XM_NUM_ALGOS			(CS40L2X_DSP1_XMEM_UNPACK24_0 + 36)
#define CS40L2X_ALGO_ID_OFFSET			0
#define CS40L2X_ALGO_REV_OFFSET			4
#define CS40L2X_ALGO_XM_BASE_OFFSET		8
#define CS40L2X_ALGO_XM_SIZE_OFFSET		12
#define CS40L2X_ALGO_YM_BASE_OFFSET		16
#define CS40L2X_ALGO_YM_SIZE_OFFSET		20
#define CS40L2X_ALGO_ENTRY_SIZE			24
#define CS40L2X_ALGO_LIST_TERM			0xBEDEAD
#define CS40L2X_ALGO_REV_MASK			0xFF0000
#define CS40L2X_ALG0_PARAM_OFFSET		20

#define CS40L2X_NUM_ALGOS_MAX			16

#define CS40L2X_ALGO_ID_SIZE			4
#define CS40L2X_COEFF_COUNT_SIZE		4
#define CS40L2X_COEFF_OFFSET_SIZE		2
#define CS40L2X_COEFF_TYPE_SIZE			2
#define CS40L2X_COEFF_LENGTH_SIZE		4
#define CS40L2X_COEFF_NAME_LEN_MAX		32

#define CS40L2X_TIMEOUT_MS_MAX			0x02AAAA  /* ~174 sec */
#define CS40L2X_PR_TIMEOUT_MAX			0x7FFFFF
#define CS40L2X_EVENT_TIMEOUT_MAX		CS40L2X_PR_TIMEOUT_MAX
#define CS40L2X_FALSEI2CTIMEOUT_MIN		10
#define CS40L2X_FALSEI2CTIMEOUT_MAX		500

#define CS40L2X_STATUS_IDLE			0xFFFFFF
#define CS40L2X_TONE_DURATION_MS_NONE		0xFFFFFF

#define CS40L2X_MBOX_TRIGGERRESET		0xFFFFFFFF
#define CS40L2X_MBOX_TRIGGERINDEX		CS40L2X_DSP_VIRTUAL1_MBOX_1
#define CS40L2X_MBOX_TRIGGER_MS			CS40L2X_DSP_VIRTUAL1_MBOX_2
#define CS40L2X_MBOX_STIMULUS_MODE		CS40L2X_DSP_VIRTUAL1_MBOX_3
#define CS40L2X_MBOX_POWERCONTROL		CS40L2X_DSP_VIRTUAL1_MBOX_4
#define CS40L2X_MBOX_USER_CONTROL		CS40L2X_DSP_VIRTUAL1_MBOX_5

#define CS40L2X_INDEX_MASK			0x00007FFF
#define CS40L2X_INDEX_VIBE			0x00000000
#define CS40L2X_INDEX_CLICK_MIN			0x00000001
#define CS40L2X_INDEX_CLICK_MAX			0x00007FFF
#define CS40L2X_INDEX_CONT_MIN			0x00008000
#define CS40L2X_INDEX_CONT_MAX			0x0000FFF6
#define CS40L2X_INDEX_GP1F_OVWR			0x0000FFF7
#define CS40L2X_INDEX_GP1R_OVWR			0x0000FFF8
#define CS40L2X_INDEX_OVWR_SAVE			0x0000FFF9
#define CS40L2X_INDEX_PBQ_SAVE			0x0000FFFB
#define CS40L2X_INDEX_QEST			0x0000FFFC
#define CS40L2X_INDEX_PEAK			0x0000FFFD
#define CS40L2X_INDEX_PBQ			0x0000FFFE
#define CS40L2X_INDEX_DIAG			0x0000FFFF
#define CS40L2X_INDEX_IDLE			0xFFFFFFFF

#define CS40L2X_PBQ_SCALE_MAX			100
#define CS40L2X_PBQ_DELAY_MAX			10000
#define CS40L2X_PBQ_POLL_NS			5000000
#define CS40L2X_PBQ_STATE_IDLE			0x00
#define CS40L2X_PBQ_STATE_PLAYING		0x01
#define CS40L2X_PBQ_STATE_SILENT		0x02
#define CS40L2X_PBQ_FW_BYTES_MIN		192
#define CS40L2X_PBQ_DUR_MIN_REV			0x0A0101
#define CS40L2X_PWLE_FRQ_MIN_REV		0x0A0302
#define CS40L2X_A2H_REINIT_MIN_REV		0x0A0503
#define CS40L2X_OWT_MIN_REV			0x080908

#define CS40L2X_DIAG_STATE_INIT			0x00
#define CS40L2X_DIAG_STATE_RUN1			0x01
#define CS40L2X_DIAG_STATE_DONE1		0x02
#define CS40L2X_DIAG_STATE_RUN2			0x03
#define CS40L2X_DIAG_STATE_DONE2		0x04
#define CS40L2X_DIAG_STATE_DELAY_MS		500

#define CS40L2X_F0_TRACKING_OFF			0
#define CS40L2X_F0_TRACKING_DIAG		1
#define CS40L2X_F0_TRACKING_QEST		2
#define CS40L2X_F0_TRACKING_BOTH		3

#define CS40L2X_QEST_SRATE			48
#define CS40L2X_QEST_ERROR			0x800000

#define CS40L2X_DSP_TIMEOUT_COUNT		10 /* 1 count = 10 ms */
#define CS40L2X_ACK_TIMEOUT_COUNT		10 /* 1 count = 1 ms */
#define CS40L2X_OTP_TIMEOUT_COUNT		10 /* 1 count = 10 ms */
#define CS40L2X_BASIC_TIMEOUT_COUNT		200 /* 1 count = 5 ms */

#define CS40L2X_NUM_OTP_MAPS			3
#define CS40L2X_NUM_OTP_WORDS			32

#define CS40L2X_TEST_KEY_UNLOCK_CODE1		0x55
#define CS40L2X_TEST_KEY_UNLOCK_CODE2		0xAA
#define CS40L2X_TEST_KEY_RELOCK_CODE1		0xCC
#define CS40L2X_TEST_KEY_RELOCK_CODE2		0x33

#define CS40L2X_DIG_SCALE_MAX			816 /* -102 dB */
#define CS40L2X_DIG_SCALE_ZERO			0x800
#define CS40L2X_DIG_SCALE_MASK			0x7FF
#define CS40L2X_DIG_SCALE_RESET			0x80000000

#define CS40L2X_WSEQ_LENGTH_MAX			48
#define CS40L2X_WSEQ_STRIDE			8
#define CS40L2X_WSEQ_LIST_TERM			0x00FFFFFF
#define CS40L2X_WSEQ_REG_MASK1			0x0000FFFF
#define CS40L2X_WSEQ_REG_SHIFTUP		8
#define CS40L2X_WSEQ_VAL_SHIFTDN		24
#define CS40L2X_WSEQ_VAL_MASK1			0xFF000000
#define CS40L2X_WSEQ_VAL_MASK2			0x00FFFFFF

#define CS40L2X_POWERCONTROL_NONE		0
#define CS40L2X_POWERCONTROL_HIBERNATE		1
#define CS40L2X_POWERCONTROL_WAKEUP		2
#define CS40L2X_POWERCONTROL_FRC_STDBY		3

#define CS40L2X_POWERSTATE_BLANK		0
#define CS40L2X_POWERSTATE_ACTIVE		1
#define CS40L2X_POWERSTATE_STANDBY		2
#define CS40L2X_POWERSTATE_HIBERNATE		3
#define CS40L2X_POWERSTATE_FRC_STDBY		4

#define CS40L2X_WAKEUP_RETRIES			20
#define CS40L2X_STATUS_RETRIES			10

#define CS40L2X_EVENT_CTRL_GPIO1_FALL		0
#define CS40L2X_EVENT_CTRL_GPIO1_RISE		1
#define CS40L2X_EVENT_CTRL_GPIO2_FALL		2
#define CS40L2X_EVENT_CTRL_GPIO2_RISE		3
#define CS40L2X_EVENT_CTRL_GPIO3_FALL		4
#define CS40L2X_EVENT_CTRL_GPIO3_RISE		5
#define CS40L2X_EVENT_CTRL_GPIO4_FALL		6
#define CS40L2X_EVENT_CTRL_GPIO4_RISE		7
#define CS40L2X_EVENT_CTRL_TRIG_START		8
#define CS40L2X_EVENT_CTRL_GPIO_START		9
#define CS40L2X_EVENT_CTRL_TRIG_STOP		10
#define CS40L2X_EVENT_CTRL_GPIO_STOP		11
#define CS40L2X_EVENT_CTRL_READY		12
#define CS40L2X_EVENT_CTRL_HARDWARE		13
#define CS40L2X_EVENT_CTRL_TRIG_SUSP		14
#define CS40L2X_EVENT_CTRL_TRIG_RESM		15
#define CS40L2X_EVENT_CTRL_NONE			0xFFFFFF

#define CS40L2X_EVENT_DISABLED			0x000000
#define CS40L2X_EVENT_GPIO1_ENABLED		0x000001
#define CS40L2X_EVENT_GPIO2_ENABLED		0x000002
#define CS40L2X_EVENT_GPIO3_ENABLED		0x000004
#define CS40L2X_EVENT_GPIO4_ENABLED		0x000008
#define CS40L2X_EVENT_START_ENABLED		0x000010
#define CS40L2X_EVENT_END_ENABLED		0x000020
#define CS40L2X_EVENT_READY_ENABLED		0x000040
#define CS40L2X_EVENT_HARDWARE_ENABLED		0x800000

#define CS40L2X_USER_CTRL_SUCCESS		0x00000000
#define CS40L2X_USER_CTRL_DURATION		0x00000001
#define CS40L2X_USER_CTRL_PLAY			0x00000002
#define CS40L2X_USER_CTRL_STOP			0x00000003
#define CS40L2X_USER_CTRL_PLAY_AUTO		0x00000004
#define CS40L2X_USER_CTRL_Q_INDEX		0x00000005
#define CS40L2X_USER_CTRL_REINIT_A2H		0x00000007

#define CS40L2X_GPIO_BTNDETECT_GPIO1		1
#define CS40L2X_GPIO_BTNDETECT_GPIO2		2
#define CS40L2X_GPIO_BTNDETECT_GPIO3		4
#define CS40L2X_GPIO_BTNDETECT_GPIO4		8

#define CS40L2X_INDEXBUTTONPRESS1		0
#define CS40L2X_INDEXBUTTONPRESS2		4
#define CS40L2X_INDEXBUTTONPRESS3		8
#define CS40L2X_INDEXBUTTONPRESS4		12

#define CS40L2X_INDEXBUTTONRELEASE1		0
#define CS40L2X_INDEXBUTTONRELEASE2		4
#define CS40L2X_INDEXBUTTONRELEASE3		8
#define CS40L2X_INDEXBUTTONRELEASE4		12

#define CS40L2X_GPIO_RISE			1
#define CS40L2X_GPIO_FALL			0

#define CS40L2X_NUM_GPIO			4

#define CS40L2X_MAX_WLEN			4096

#define CS40L2X_DEVICE_NAME			"vibrator"

#define CS40L2X_NUM_FW_FAMS			8
#define CS40L2X_FW_ID_ORIG			0x1400A7
#define CS40L2X_FW_ID_B1ROM			0x1400BA
#define CS40L2X_FW_ID_REMAP			0x1400C3
#define CS40L2X_FW_ID_CAL			0x1400C6
#define CS40L2X_FW_ID_CLAB			0x1400CB
#define CS40L2X_FW_ID_PAR			0x1400CF
#define CS40L2X_FW_ID_A2H			0x1400D0
#define CS40L2X_FW_ID_DF0_CLAB			0x1400E0
#define CS40L2X_A2H_MAX_TUNING			5
#define CS40L2X_A2H_DELAY_MAX			500

#define CS40L2X_PDATA_PRESENT			0x80000000
#define CS40L2X_PDATA_MASK			~CS40L2X_PDATA_PRESENT

#define CS40L2X_GPIO1_MODE_DEF_ON		0
#define CS40L2X_GPIO1_MODE_DEF_OFF		1
#define CS40L2X_GPIO1_MODE_AUTO			2
#define CS40L2X_GPIO1_MODE_MAX			CS40L2X_GPIO1_MODE_AUTO

#define CS40L2X_GPIO1_ENABLED			1
#define CS40L2X_GPIO1_DISABLED			0

#define CS40L2X_COMP_EN_REDC_SHIFT		1
#define CS40L2X_COMP_EN_F0_SHIFT		0

#define CS40L2X_ASP_ENABLED			1
#define CS40L2X_ASP_DISABLED			0
#define CS40L2X_ASP_TIMEOUT_MAX			10000

#define CS40L2X_I2S_ENABLED			1
#define CS40L2X_I2S_DISABLED			0

#define CS40L2X_VIBE_STATE_STOPPED		0
#define CS40L2X_VIBE_STATE_RUNNING		1

#define CS40L2X_SAVE_UNSAFE			0
#define CS40L2X_SAVE_SAFE			1

#define CS40L2X_FW_BUSY				0
#define CS40L2X_FW_WAIT_COMPLETE		1

#define CS40L2X_EXC_ENABLED			1
#define CS40L2X_EXC_DISABLED			0

#define CS40L2X_PRE_ENABLED			1
#define CS40L2X_PRE_DISABLED			0

#define CS40L2X_ENDPLAYBACK_RETRIES		10
#define CS40L2X_ENDPLAYBACK_REQ			1
#define CS40L2X_ENDPLAYBACK_ACK			0

#define CS40L2X_VMON_POSFS			0x7FFFFF
#define CS40L2X_VMON_NEGFS			0x800000
#define CS40L2X_VMON_MASK			0xFFFFFF

#define CS40L2X_IMON_POSFS			CS40L2X_VMON_POSFS
#define CS40L2X_IMON_NEGFS			CS40L2X_VMON_NEGFS
#define CS40L2X_IMON_MASK			CS40L2X_VMON_MASK

#define CS40L2X_VPMONMAX_RESET			0
#define CS40L2X_VPMONMIN_RESET			0x0003FF

#define CS40L2X_PEAK_DELAY_MS			100

#define CS40L2X_F0_OFFSET_POS_MIN		0x000000
#define CS40L2X_F0_OFFSET_POS_MAX		0x190000 /* +100 Hz */
#define CS40L2X_F0_OFFSET_NEG_MIN		0xE70000 /* -100 Hz */
#define CS40L2X_F0_OFFSET_NEG_MAX		0xFFFFFF

#define CS40L2X_IRQMASKSEQ_STRIDE		8
#define CS40L2X_IRQMASKSEQ_MASK1		0x000000FF
#define CS40L2X_IRQMASKSEQ_MASK2		0xFFFFFF00
#define CS40L2X_IRQMASKSEQ_SHIFTUP		16
#define CS40L2X_IRQMASKSEQ_SHIFTDN		8

#define CS40L2X_ALGO_ID_VIBE			0x0000BD
#define CS40L2X_ALGO_ID_F0			0x0000E8
#define CS40L2X_ALGO_ID_EXC			0x000100
#define CS40L2X_ALGO_ID_PRE			0x000109
#define CS40L2X_ALGO_ID_A2H			0x000110
#define CS40L2X_ALGO_ID_DYN_F0			0x000111
#define CS40L2X_ALGO_ID_QEST			0x000112
#define CS40L2X_ALGO_ID_CLAB			0x000117
#define CS40L2X_ALGO_ID_PAR			0x000121

#define CS40L2X_DSP_CACHE_MAX			64

#define CS40L2X_CLAB_ENABLED			1
#define CS40L2X_CLAB_DISABLED			0
#define CS40L2X_CLAB_PEAK_MAX			0x400000

#define CS40L2X_PAR_ENABLED			1
#define CS40L2X_PAR_DISABLED			0
#define CS40L2X_GC_ENABLED			1
#define CS40L2X_GC_DISABLED			0

#define CS40L2X_IMON_OFFS_CALC_EN		1
#define CS40L2X_IMON_OFFS_CALC_DIS		0

#define CS40L2X_PLLSRC_SCLK			0
#define CS40L2X_PLLSRC_MCLK			5

#define CS40L2X_AUTOSUSPEND_DELAY_MS		3000

#define CS40l2X_F0_MAX_ENTRIES			20
#define CS40L2X_DYN_F0_INDEX_SHIFT		13
#define CS40L2X_DYN_F0_MASK			GENMASK(12, 0)
#define CS40L2X_DYN_F0_DEFAULT			0x7FE000
#define CS40L2X_DYN_F0_FILE_NAME		"cs40l25a_f0.bin"
#define CS40L2X_COND_CLSH_MIN_REV		0x090007

#define CS40L2X_BEMF_BUF_MAX			140

/* A2H */

#define CS40L2X_A2H_ENABLE			1
#define CS40L2X_A2H_DISABLE			0
#define CS40L2X_A2H_I2S_START			2
#define CS40L2X_A2H_I2S_END			3

#define CS40L2X_ASP_WIDTH_RX_MASK		GENMASK(31, 24)
#define CS40L2X_ASP_WIDTH_RX_SHIFT		24
#define CS40L2X_ASP_SP_RX_WL_MASK		GENMASK(5, 0)

#define CS40L2X_ASP_RX_ENABLE_MASK		GENMASK(17, 16)

#define CS40L2X_PWRCTL_FORCE_STBY		3
#define CS40L2X_PWRCTL_WAKE			2
#define CS40L2X_PWRCTL_NONE			0

#define CS40L2X_VOL_LVL_MAX_STEPS		10000
#define CS40L2X_VOL_LVL_MAX			0x7fffff

#define CS40L2X_SIZE_TWO_ARRAY			2

#define CS40L2X_PWLE_MIN_SEGS			2
#define CS40L2X_PWLE_MAX_SEGS			255
#define CS40L2X_PWLE_MAX_SEG_VALS		7
#define CS40L2X_PWLE_MAX_TOT_SV (\
	CS40L2X_PWLE_MAX_SEGS *\
	CS40L2X_PWLE_MAX_SEG_VALS)
#define CS40L2X_PWLE_TOTAL_VALS	(\
	CS40L2X_PWLE_MAX_TOT_SV +\
	CS40L2X_PWLE_MIN_SEGS)
#define CS40L2X_PWLE_MAX_SEG_BYTES		9
#define CS40L2X_PWLE_NON_SEG_BYTES		7
#define CS40L2X_PWLE_BYTES_MAX	((\
	CS40L2X_PWLE_MAX_SEGS *\
	CS40L2X_PWLE_MAX_SEG_BYTES) +\
	CS40L2X_PWLE_NON_SEG_BYTES)
#define CS40L2X_PWLE_MAX_SEG_STRING			67
#define CS40L2X_PWLE_MAX_NON_SEG_STRING		28
#define CS40L2X_PWLE_STRING_MAX ((\
	CS40L2X_PWLE_MAX_SEGS *\
	CS40L2X_PWLE_MAX_SEG_STRING) +\
	CS40L2X_PWLE_MAX_NON_SEG_STRING)
#define CS40L2X_PWLE_SEG_LEN_MAX		11
#define CS40L2X_PWLE_MAX_RP_VAL			255
#define CS40L2X_PWLE_MAX_WT_VAL			1023
#define CS40L2X_PWLE_MAX_TIME_VAL		16383
#define CS40L2X_PWLE_INDEF_TIME_VAL		65535
#define CS40L2X_PWLE_TIME_RES			25
#define CS40L2X_PWLE_FREQ_RES			125
#define CS40L2X_PWLE_MAX_LEV_VAL		98256
#define CS40L2X_PWLE_LEV_ADD_NEG		2048
#define CS40L2X_PWLE_LEV_DIV			48
#define CS40L2X_PWLE_MAX_FREQ_VAL		561
#define CS40L2X_PWLE_MIN_FREQ_VAL		50
#define CS40L2X_PWLE_MAX_VB_RES			9999999
#define CS40L2X_PWLE_MAX_VB_TARG		8388607
#define CS40L2X_PWLE_NUM_CONST_VALS		2
#define CS40L2X_PWLE_MAX_VB_RES_DIG		6
#define CS40L2X_PWLE_MAX_LV_RES_DIG		4
#define CS40L2X_PWLE_MAX_WVFRM_FEAT		12
#define CS40L2X_PWLE_WVFRM_FT_SHFT		20
#define CS40L2X_PWLE_SAMPLES_PER_MS		8
#define CS40L2X_PWLE_SEG_BYTES			6
#define CS40L2X_PWLE_WV_SMPL_BYTES		3
#define CS40L2X_PWLE_REPEAT_BYTES		1
#define CS40L2X_PWLE_WT_BYTES			2
#define CS40L2X_PWLE_NUM_SEG_BYTES		1
#define CS40L2X_PWLE_NUM_VBT_BYTES		3
#define CS40L2X_PWLE_END_PAD_BYTES		2
#define CS40L2X_ZERO_PAD_MASK			0xFFFFFF00
#define CS40L2X_MS_FOUR_BYTE_MASK		0xF0
#define CS40L2X_LS_FOUR_BYTE_MASK		0x0F
#define CS40L2X_PWLE_CHIRP_BIT			0x8
#define CS40L2X_PWLE_BRAKE_BIT			0x4
#define CS40L2X_PWLE_AMP_REG_BIT		0x2
#define CS40L2X_PWLE_FIRST_BYTES	(\
	CS40L2X_PWLE_WV_SMPL_BYTES +\
	CS40L2X_PWLE_REPEAT_BYTES +\
	CS40L2X_PWLE_WT_BYTES +\
	CS40L2X_PWLE_NUM_SEG_BYTES)
#define CS40L2X_PACKED_BYTES_MAX	(((\
	CS40L2X_PWLE_BYTES_MAX / 2) *\
	CS40L2X_WT_NUM_VIRT_SLOTS) + 3)
#define CS40L2X_SINGLE_PACKED_MAX	(\
	CS40L2X_PACKED_BYTES_MAX /\
	CS40L2X_WT_NUM_VIRT_SLOTS)
/* CS40L2X_PACKED_BYTES_MAX if changed, should stay above
 * the recommended min value of 576 and be evenly divisible
 * by CS40L2X_PBQ_FW_BYTES_MIN because the driver will attempt
 * to automatically reduce the size of the required space for
 * an open slot to use for open wavetable and chirp scalability
 * if there aren't CS40L2X_PACKED_BYTES_MAX bytes available.
 */

#define CS40L2X_TEMP_RESULT_UNFILT_MASK		0x1FF
#define CS40L2X_TEMP_RESULT_MIN			-64
#define CS40L2X_TEMP_RESULT_MAX			176

bool cs40l2x_readable_reg(struct device *dev, unsigned int reg);
bool cs40l2x_precious_reg(struct device *dev, unsigned int reg);

struct cs40l2x_trim {
	unsigned int reg;
	unsigned char shift;
	unsigned char size;
};

struct cs40l2x_otp_desc {
	unsigned int id;
	unsigned char row_start;
	unsigned char col_start;
	unsigned int num_trims;
	const struct cs40l2x_trim *trim_table;
};

struct cs40l2x_algo_info {
	unsigned int id;
	unsigned int rev;
	unsigned int xm_base;
	unsigned int xm_size;
	unsigned int ym_base;
	unsigned int ym_size;
};

struct cs40l2x_coeff_desc {
	unsigned int parent_id;
	unsigned int block_offset;
	unsigned int block_type;
	unsigned char name[CS40L2X_COEFF_NAME_LEN_MAX];
	unsigned int reg;
	struct list_head list;
};

struct cs40l2x_wseq_pair {
	unsigned int reg;
	unsigned int val;
};

struct cs40l2x_fw_desc {
	unsigned int id;
	unsigned int min_rev;
	unsigned int halo_state_started;
	unsigned int halo_state_run;
	unsigned int num_coeff_files;
	const char * const *coeff_files;
	const char *fw_file;
};

struct cs40l2x_hw_err_desc {
	unsigned int irq_mask;
	unsigned int rls_mask;
	bool bst_cycle;
	const char *err_name;
};

struct cs40l2x_f0_dynamic {
	unsigned int index;
	unsigned int f0;
	bool changed;
};

struct cs40l2x_ovwr_waveform {
	bool is_xm;
	unsigned int data_len;
	unsigned int wvfrm_type;
	unsigned int wvfrm_feature;
	char data[CS40L2X_SINGLE_PACKED_MAX];
};

struct cs40l2x_private {
	struct device *dev;
	struct regmap *regmap;
	struct regulator_bulk_data supplies[2];
	unsigned int num_supplies;
	unsigned int devid;
	unsigned int revid;
	struct work_struct vibe_start_work;
	struct work_struct vibe_pbq_work;
	struct work_struct vibe_stop_work;
	struct work_struct vibe_mode_work;
	struct workqueue_struct *vibe_workqueue;
	struct mutex lock;
	unsigned int cp_trigger_index;
	unsigned int cp_trailer_index;
	unsigned int num_waves;
	unsigned int num_virtual_waves;
	unsigned int loaded_virtual_index;
	unsigned int comp_bytes;
	unsigned int updated_block_size;
	unsigned int pwle_str_size;
	char *pbq_fw_raw_wt;
	char *pbq_updated_fw_raw_wt;
	bool open_wt_enable;
	bool virtual_stored;
	bool queue_stored;
	bool virtual_bin;
	bool xm_append;
	char wt_file[CS40L2X_WT_FILE_NAME_LEN_MAX];
	char wt_date[CS40L2X_WT_FILE_DATE_LEN_MAX];
	char pwle_str[CS40L2X_PWLE_STRING_MAX];
	bool vibe_init_success;
	bool vibe_state;
	bool safe_save_state;
	bool gpio_event;
	struct gpio_desc *reset_gpio;
	struct cs40l2x_platform_data pdata;
	unsigned int num_algos;
	struct cs40l2x_algo_info algo_info[CS40L2X_NUM_ALGOS_MAX + 1];
	struct list_head coeff_desc_head;
	unsigned int num_coeff_files;
	unsigned int diag_state;
	unsigned int diag_dig_scale;
	unsigned int f0_measured;
	unsigned int redc_measured;
	unsigned int q_measured;
	unsigned int bemf_measured;

	struct wt_wavetable wt_xm;
	struct wt_wavetable wt_ym;

	struct wt_type10_comp pbq_comp;
	unsigned int pbq_index;
	unsigned int pbq_state;
	int pbq_inner_mark;
	int pbq_inner_loop;
	int pbq_outer_loop;

	struct hrtimer pbq_timer;
	unsigned int pbq_cp_dig_scale;
	unsigned int num_virtual_pwle_waves;
	unsigned int last_type_entered;
	unsigned int display_pwle_segs;
	unsigned int virtual_gpio_index[CS40L2X_SIZE_TWO_ARRAY];
	unsigned int loaded_gpio_index[CS40L2X_SIZE_TWO_ARRAY];
	unsigned int virtual_slot_index;
	unsigned int virtual_gpio1_fall_slot;
	unsigned int virtual_gpio1_rise_slot;
	struct list_head virtual_waveform_head;
	struct cs40l2x_ovwr_waveform *ovwr_wav;
	struct cs40l2x_wseq_pair wseq_table[CS40L2X_WSEQ_LENGTH_MAX];
	unsigned int wseq_length;
	unsigned int event_control;
	unsigned int hw_err_mask;
	unsigned int hw_err_count[CS40L2X_NUM_HW_ERRS];
	unsigned int peak_gpio1_enable;
	unsigned int gpio_mask;
	int vpp_measured;
	int ipp_measured;
	bool a2h_enable;
	struct hrtimer asp_timer;
	const struct cs40l2x_fw_desc *fw_desc;
	unsigned int fw_id_remap;
	bool cal_disabled_owt;
	bool comp_enable;
	bool comp_enable_redc;
	bool comp_enable_f0;
	bool comp_dur_min_fw;
	bool ext_freq_min_fw;
	bool a2h_reinit_min_fw;
	bool amp_gnd_stby;
	bool dyn_f0_enable;
	bool cond_class_h_en;
	bool clab_bin_found;
	bool par_bin_found;
	struct cs40l2x_wseq_pair dsp_cache[CS40L2X_DSP_CACHE_MAX];
	unsigned int dsp_cache_depth;

	/* Access to DSP registers */
	unsigned int (*dsp_reg)(struct cs40l2x_private *cs40l2x,
			const char *coeff_name, const unsigned int block_type,
			const unsigned int algo_id);

	struct cs40l2x_f0_dynamic dynamic_f0[CS40l2X_F0_MAX_ENTRIES];
	int dynamic_f0_index;

#ifdef CONFIG_HAPTICS_CS40L2X_INPUT
	struct input_dev *input;
	struct ff_effect *effect;
	unsigned int trigger_indices[FF_MAX_EFFECTS];
#elif defined CONFIG_ANDROID_TIMED_OUTPUT
	struct timed_output_dev timed_dev;
	struct hrtimer vibe_timer;
	int vibe_timeout;
#else
	struct led_classdev led_dev;
#endif /* CONFIG_ANDROID_TIMED_OUTPUT */
	struct completion hap_done;
};

int cs40l2x_coeff_file_parse(struct cs40l2x_private *cs40l2x,
			const struct firmware *fw);
int cs40l2x_ack_write(struct cs40l2x_private *cs40l2x, unsigned int reg,
			unsigned int write_val, unsigned int reset_val);

struct cs40l2x_virtual_waveform {
	bool is_xm;
	unsigned int index;
	unsigned int data_len;
	unsigned int wvfrm_type;
	unsigned int wvfrm_feature;
	char data[CS40L2X_SINGLE_PACKED_MAX];
	struct list_head list;
};

extern const unsigned char cs40l2x_bst_k1_table[4][5];
extern const unsigned char cs40l2x_bst_k2_table[4][5];
extern const unsigned char cs40l2x_bst_slope_table[4];

extern const struct cs40l2x_otp_desc cs40l2x_otp_map[CS40L2X_NUM_OTP_MAPS];

extern const unsigned int cs40l2x_pbq_dig_scale[CS40L2X_PBQ_SCALE_MAX + 1];

extern const struct cs40l2x_fw_desc cs40l2x_fw_fam[CS40L2X_NUM_FW_FAMS];

extern const struct cs40l2x_hw_err_desc cs40l2x_hw_errs[CS40L2X_NUM_HW_ERRS];

#endif /*__CS40L2X_H__*/