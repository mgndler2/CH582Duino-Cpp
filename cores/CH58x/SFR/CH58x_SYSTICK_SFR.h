#pragma once

#ifndef __CH58xSYSTICKSFR__
#define __CH58xSYSTICKSFR__
#include "CH58x_SFR_TOP_LVL.h"

typedef union STK_CTRL {
	struct {
		uint32_t STE : 1;
		uint32_t STIE : 1;
		uint32_t STCLK : 1;
		uint32_t STRE : 1;
		uint32_t MODE : 1;
		uint32_t INIT : 1;
		uint32_t : 25;
		uint32_t SWIE : 1;
	};
	uint32_t pad;
}STK_CTRL_t;
typedef union STK_SR {
	struct {
		uint32_t CNTIF : 1;
		uint32_t : 31;
	};
	uint32_t pad;
}STK_SR_t;
typedef union STK_CNT {
	struct {
		uint32_t u16L : 16;
		uint32_t u16H : 16;
	};
	uint32_t pad;
}STK_CNT_t;
typedef union STK_CMPR {
	struct {
		uint16_t u16L;
		uint16_t u16H;
	};
	uint32_t pad;
}STK_CMPR_t;

typedef struct SYS_TICK {
	volatile STK_CTRL_t	STK_CTRL;
	volatile STK_SR_t	STK_SR;
	volatile STK_CNT_t	STK_CNTL;
	volatile STK_CNT_t	STK_CNTH;
	volatile STK_CMPR_t	STK_CMPLR;
	volatile STK_CMPR_t	STK_CMPHR;
}SYS_TICK_t;

#define SySTick		(*(volatile SYS_TICK_t*)	0xE000F000)

#define TUNE32K		(*(volatile TUNE_32K_t*)	0x4000102C)
#endif // !__CH58xSYSTICKSFR__
