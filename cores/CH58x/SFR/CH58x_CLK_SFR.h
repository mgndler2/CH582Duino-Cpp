#pragma once

#ifndef __CH58xCLKSFR__
#define __CH58xCLKSFR__
#include "CH58x_SFR_TOP_LVL.h"

typedef union CLK_SYS_CFG {
	 struct {
		  uint8_t CLK_PLL_DIV : 5;
		  uint8_t : 1;
		  uint8_t CLK_SYS_MOD : 2;
		  uint8_t : 8;
	 };
	 struct {
		  uint8_t CLK_SOURCE : 8;
		  uint8_t : 8;
	 };
}CLK_SYS_CFG_t;
typedef union HFCK_PWR_CTRL {
	 struct {
		  uint8_t : 2;
		  uint8_t CLK_XT32M_PON : 1;
		  uint8_t CLK_XT32M_KEEP : 1;
		  uint8_t CLK_PLL_PON : 1;
		  uint8_t : 3;
	 };
	 uint8_t byte;
}HFCK_PWR_CTRL_t;
typedef union INT32K_TUNE {
	 struct {
		  uint16_t TUNE : 13;
		  uint16_t : 3;
	 };
	 uint8_t bytes[2];
}INT32K_TUNE_t;
typedef union XT32K_TUNE {
	 struct {
		  uint8_t XT32K_I_TUNE : 2;
		  uint8_t : 2;
		  uint8_t XT32K_C_LOAD : 4;
	 };
	 uint8_t byte;
}XT32K_TUNE_t;
typedef union CK32K_CONFIG {
	 struct {
		  uint8_t CLK_XT32K_PON : 1;
		  uint8_t CLK_INT32K_PON : 1;
		  uint8_t CLK_OSC32K_XT : 1;
		  uint8_t CLK_OSC32K_FILT : 1;
		  uint8_t : 3;
		  uint8_t CLK_PIN: 1;
	 };
	 uint8_t byte;
}CK32K_CONFIG_t;
typedef union XT32M_TUNE {
	 struct {
		  uint8_t XT32M_I_BIAS : 2;
		  uint8_t : 2;
		  uint8_t XT32M_C_LOAD : 3;
		  uint8_t : 1;
	 };
	 uint8_t byte;
}XT32M_TUNE_t;
typedef union OSC_CAL_CNT {
	 struct {
		  uint16_t CAL_CNT : 14;
		  uint16_t OSC_CAL_OV_CLR : 1;
		  uint16_t OSC_CAL_IF : 1;
	 };
}OSC_CAL_CNT_t;
typedef union OSC_CAL_OV_CNT {
	 uint8_t COUNT;
}OSC_CAL_OV_CNT_t;
typedef union OSC_CAL_CTRL {
	 struct {
		  uint8_t OSC_CNT_TOTAL : 3;
		  uint8_t OSC_CNT_HALT : 1;
		  uint8_t OSC_CAL_IE : 1;
		  uint8_t OSC_CNT_EN : 1;
		  uint8_t OSC_CNT_END : 1;
		  uint8_t : 1;
	 };
	 uint8_t byte;
}OSC_CAL_CTRL_t;
typedef union PLL_CONFIG {
	 struct {
		  uint8_t PLL_CFG_DAT : 7;
		  uint8_t FLASH_IO_MOD : 1;
	 };
	 uint8_t byte;
}PLL_CONFIG_t;
typedef union RTC_FLAG_CTRL {
	 struct {
		  uint8_t : 4;
		  uint8_t RTC_TMR_CLR : 1;
		  uint8_t RTC_TRIG_CLR : 1;
		  uint8_t RTC_TMR_FLAG : 1;
		  uint8_t RTC_TRIG_FLAG : 1;
	 };
	 uint8_t byte;
}RTC_FLAG_CTRL_t;
typedef union RTC_MODE_CTRL {
	 struct {
		  uint8_t RTC_TMR_MODE : 3;
		  uint8_t RTC_IGNORE_B0 : 1;
		  uint8_t RTC_TMR_EN : 1;
		  uint8_t RTC_TRIG_EN : 1;
		  uint8_t RTC_LOAD_LO : 1;
		  uint8_t RTC_LOAD_HI : 1;
	 };
	 uint8_t byte;
}RTC_MODE_CTRL_t;
typedef union RTC_TRIG {
	 uint32_t VAL;
}RTC_TRIG_t;
typedef union RTC_CNT_32K {
	 uint16_t COUNT;
}RTC_CNT_32K_t;
typedef union RTC_CNT_2S {
	 uint16_t COUNT;
}RTC_CNT_2S_t;
typedef union RTC_CNT_DAY {
	 struct {
		  uint16_t CNT_DAY : 14;
		  uint16_t : 2;
		  uint16_t : 16;
	 };
	 uint32_t pad;
}RTC_CNT_DAY_t;

typedef struct SYS_CLK {
	CLK_SYS_CFG_t		CLK_SYS_CFG;	//0x08-09
	HFCK_PWR_CTRL_t		HFCK_PWR_CTRL;	//0x0A
	uint8_t : 8;						//0x0B//
}SYS_CLK_t;
typedef struct TUNE_32K {
	INT32K_TUNE_t		INT32K_TUNE;	//0x2C-2D
	XT32K_TUNE_t		XT32K_TUNE;		//0x2E
	CK32K_CONFIG_t		CK32K_CONFIG;	//0x2F//
}TUNE_32K_t;
typedef struct MISC_CTRL {
	uint16_t : 16;						//0x48-49
	uint8_t : 8;						//0x4A
	PLL_CONFIG_t		PLL_CONFIG;		//0x4B//
}MISC_CTRL_t;
typedef struct TUNE_32M {
	uint16_t : 16;						//0x4C-4D
	XT32M_TUNE_t		XT32M_TUNE;		//0x4E
	uint8_t : 8;						//0x4F//
}TUNE_32M_t;
typedef struct OSC_CAL {
	OSC_CAL_CNT_t		OSC_CAL_CNT;	//0x50-51
	OSC_CAL_OV_CNT_t	OSC_CAL_OV_CNT;	//0x52
	OSC_CAL_CTRL_t		OSC_CAL_CTRL;	//0x53//
}OSC_CAL_t;
typedef struct RTC_CFG {
	RTC_FLAG_CTRL_t		RTC_FLAG_CTRL;	//0x30
	RTC_MODE_CTRL_t		RTC_MODE_CTRL;	//0x31
	uint16_t : 16;						//0x32-33//
	RTC_TRIG_t			RTC_TRIG;		//0x34-37//
	RTC_CNT_32K_t		RTC_CNT_32K;	//0x38-39
	RTC_CNT_2S_t		RTC_CNT_2S;		//0x3A-3B//
	RTC_CNT_DAY_t		RTC_CNT_DAY;	//0x3C-3F
}RTC_CFG_t;
//
// SySClock
//
#define SySClock	(*(volatile SYS_CLK_t*)	0x40001008)
#define x16_CLK_SYS_CFG		(*(volatile CLK_SYS_CFG_t*)		0x40001008)
#define x8_HFCK_PWR_CTRL	(*(volatile HFCK_PWR_CTRL_t*)	0x4000100A)
/*-----0x4000100B is RSVD-----*/
//
// TUNE32K
//
#define TUNE32K		(*(volatile TUNE_32K_t*)	0x4000102C)
#define x16_INT32K_TUNE		(*(volatile INT32K_TUNE_t*)	0x4000102C)
#define x8_XT32K_TUNE		(*(volatile XT32K_TUNE_t*)		0x4000102E)
#define x8_CK32K_CONFIG		(*(volatile CK32K_CONFIG_t*)	0x4000102F)
//
// RTCCFG
//
#define RTCCFG		(*(volatile RTC_CFG*)		0x40001030)
#define x8_RTC_FLAG_CTRL	(*(volatile RTC_FLAG_CTRL_t*)	0x40001030)
#define x8_RTC_MODE_CTRL	(*(volatile RTC_MODE_CTRL_t*)	0x40001031)
/*-----0x40001032-33 is RSVD-----*/
#define x32_RTC_TRIG		(*(volatile RTC_TRIG_t*)		0x40001034)
#define x16_RTC_CNT_32K		(*(volatile RTC_CNT_32K_t*)		0x40001038)
#define x16_RTC_CNT_2S		(*(volatile RTC_CNT_2S_t*)		0x4000103A)
#define x32_RTC_CNT_DAY		(*(volatile RTC_CNT_DAY_t*)		0x4000103C)
//
// MISCCtrl
//
#define MISCCtrl	(*(volatile MISC_CTRL_t*)	0x40001048)
/*-----0x40001048-4A is RSVD-----*/
#define x8_PLL_CONFIG		(*(volatile PLL_CONFIG_t*)		0x4000104B)
//
// TUNE32M
//
#define TUNE32M		(*(volatile TUNE_32M_t*)	0x4000104C)
/*-----0x4000104C-4D is RSVD-----*/
#define x8_XT32M_TUNE		(*(volatile XT32M_TUNE_t*)		0x4000104E)
/*-----0x4000104F is RSVD-----*/
//
// OSCCali
//
#define OSCCali		(*(volatile OSC_CAL_t*)		0x40001050)
#define x16_OSC_CAL_CNT		(*(volatile OSC_CAL_CNT_t*)		0x40001050)
#define x8_OSC_CAL_OV_CNT	(*(volatile OSC_CAL_OV_CNT_t*)	0x40001052)
#define x8_OSC_CAL_CTRL		(*(volatile OSC_CAL_CTRL_t*)	0x40001053)

#endif // !__CH58xCLKSFR__
