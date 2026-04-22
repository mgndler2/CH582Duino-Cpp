#pragma once

#ifndef __CH58xPWMSFR__
#define __CH58xPWMSFR__
#include "CH58x_SFR_TOP_LVL.h"

typedef union PWM_OUT_EN
{
	struct {
		uint8_t PWM04 : 1;
		uint8_t PWM05 : 1;
		uint8_t PWM06 : 1;
		uint8_t PWM07 : 1;
		uint8_t PWM08 : 1;
		uint8_t PWM09 : 1;
		uint8_t PWM10 : 1;
		uint8_t PWM11 : 1;
	};
	uint8_t byte;
}PWM_OUT_EN_t;

typedef union PWM_POLAR
{
	struct {
		uint8_t PWM04 : 1;
		uint8_t PWM05 : 1;
		uint8_t PWM06 : 1;
		uint8_t PWM07 : 1;
		uint8_t PWM08 : 1;
		uint8_t PWM09 : 1;
		uint8_t PWM10 : 1;
		uint8_t PWM11 : 1;
	};
	uint8_t byte;
}PWM_POLAR_t;

typedef union PWM_CONFIG
{
	struct {
		uint8_t CYCLE_SEL : 1;
		uint8_t STAG_ST : 1;
		uint8_t CYC_MOD : 2;
		uint8_t STAG04_05 : 1;
		uint8_t STAG06_07 : 1;
		uint8_t STAG08_09 : 1;
		uint8_t STAG10_11 : 1;
	};
	uint8_t byte;
}PWM_CONFIG_t;

typedef union PWM_CLOCK_DIV {
	uint8_t DIV;
}PWM_CLOCK_DIV_t;

typedef union PWM_DATA {
	struct {
		uint8_t PWM04;
		uint8_t PWM05;
		uint8_t PWM06;
		uint8_t PWM07;
		uint8_t PWM08;
		uint8_t PWM09;
		uint8_t PWM10;
		uint8_t PWM11;
	};
	uint8_t bytes[8];
}PWM_DATA_t;

typedef union PWM_INT_CTRL {
	struct {
		uint8_t IE_CYC : 1;
		uint8_t CYC_PRE : 1;
		uint8_t : 5;
		uint8_t IF_CYC : 1;
	};
}PWM_INT_CTRL_t;

typedef struct PWM_Module {
	PWM_OUT_EN_t	OUT_EN;
	PWM_POLAR_t		POLAR;
	PWM_CONFIG_t	CONFIG;
	PWM_CLOCK_DIV_t	DIV;
	PWM_DATA_t		DATA;
	PWM_INT_CTRL_t	INT_CTRL;
}PWM_Module_t;

#define PWM					(*(volatile PWM_Module_t*)		0x40005000)
#define x8_PWM_OUT_EN		(*(volatile PWM_OUT_EN_t*)		0x40005000)
#define x8_PWM_POLAR		(*(volatile PWM_POLAR_t*)		0x40005001)
#define x8_PWM_CONFIG		(*(volatile PWM_CONFIG_t*)		0x40005002)
#define x8_PWM_CLOCK_DIV	(*(volatile PWM_CLOCK_DIV_t*)	0x40005003)
#define x8_PWM4_DATA		(*(volatile uint8_t*)			0x40005004)
#define x8_PWM5_DATA		(*(volatile uint8_t*)			0x40005005)
#define x8_PWM6_DATA		(*(volatile uint8_t*)			0x40005006)
#define x8_PWM7_DATA		(*(volatile uint8_t*)			0x40005007)
#define x8_PWM8_DATA		(*(volatile uint8_t*)			0x40005008)
#define x8_PWM9_DATA		(*(volatile uint8_t*)			0x40005009)
#define x8_PWM10_DATA		(*(volatile uint8_t*)			0x4000500A)
#define x8_PWM11_DATA		(*(volatile uint8_t*)			0x4000500B)
#define x8_PWM_INT_CTRL		(*(volatile PWM_INT_CTRL_t*)	0x4000500C)

#endif // !__CH58xPWMSFR__
