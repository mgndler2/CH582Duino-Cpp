#pragma once

#ifndef __CH58xADCSFR__
#define __CH58xADCSFR__

#include "CH58x_SFR_TOP_LVL.h"
//0x54
typedef union TKEY_COUNT {
	struct {
		uint8_t TKEY_CHARG_CNT : 5;
		uint8_t TKEY_DISCH_CNT : 3;
	};
	uint8_t byte;
}TKEY_COUNT_t;
//0x56
typedef union TKEY_CONVERT {
	struct {
		uint8_t TKEY_START : 1;
		uint8_t : 7;
	};
	uint8_t byte;
}TKEY_CONVERT_t;
//0x57
typedef union TKEY_CFG {
	struct {
		uint8_t TKEY_PWR_ON : 1;
		uint8_t TKEY_CURRENT : 1;
		uint8_t TKEY_DRV_EN : 1;
		uint8_t TKEY_PGA_ADJ : 1;
		uint8_t : 4;
	};
	uint8_t byte;
}TKEY_CFG_t;

typedef union TKEY_Module {
	struct {
		TKEY_COUNT		COUNT;		//0x54
		uint8_t : 8;				//0x55
		TKEY_CONVERT	CONVERT;	//0x56
		TKEY_CFG		CFG;		//0x57//
	};
}TKEY_Module_t;
//0x58
typedef union ADC_CHANNEL {
	struct {
		uint8_t ADC_CH_INX : 4;
		uint8_t : 4;
	};
	uint8_t byte;
}ADC_CHANNEL_t;
//0x59
typedef union ADC_CFG {
	struct {
		uint8_t ADC_POWER_ON : 1;
		uint8_t ADC_BUF_EN: 1;
		uint8_t ADC_DIFF_EN : 1;
		uint8_t ADC_OFS_TEST : 1;
		uint8_t ADC_PGA_GAIN : 2;
		uint8_t ADC_CLK_DIV : 2;
	};
	uint8_t byte;
}ADC_CFG_t;
//0x5A
typedef union ADC_CONVERT {
	struct {
		uint8_t ADC_START : 1;
		uint8_t : 6;
		uint8_t ADC_EOC_X : 1;
	};
	uint8_t byte;
}ADC_CONVERT_t;
//0x5B
typedef union TEM_SENSOR {
	struct {
		uint8_t : 7;
		uint8_t TEM_SEN_PWR_ON : 1;
	};
	uint8_t byte;
}TEM_SENSOR_t;
//0x5C
typedef union ADC_DATA {
	struct {
		uint16_t DATA : 12;
		uint16_t : 4;
	};
	uint16_t group;
}ADC_DATA_t;
//0x5E
typedef union ADC_INT_FLAG {
	struct {
		uint8_t : 7;
		uint8_t ADC_IF_EOC : 1;
	};
	uint8_t byte;
}ADC_INT_FLAG_t;
//0x60
typedef union ADC_DMA_CTRL {
	struct {
		
	};
	uint32_t bytes[4];
}ADC_DMA_CTRL_t;
//0x61
typedef union ADC_CTRL_DMA {
	struct {
		uint8_t ADC_DMA_ENABLE : 1;
		uint8_t : 1;
		uint8_t ADC_DMA_LOOP : 1;
		uint8_t ADC_IE_DMA_END : 1;
		uint8_t ADC_IE_EOC : 1;
		uint8_t : 1;
		uint8_t ADC_CONT_EN : 1;
		uint8_t ADC_AUTO_EN : 1;
	};
	uint8_t byte;
}ADC_CTRL_DMA_t;
//0x62
typedef union ADC_DMA_IF {
	struct {
		uint8_t : 2;
		uint8_t ADC_IF_DMA_END : 1;
		uint8_t ADC_IF_END_ADC : 1;
		uint8_t : 4;
	};
	uint8_t byte;
}ADC_DMA_IF_t;
//0x63
typedef union ADC_AUTO_CYCLE {
	struct {
		uint8_t AUTO_CYCLE;
	};

}ADC_AUTO_CYCLE_t;
//0x64
typedef union ADC_DMA_NOW {
	struct {

	};
	uint16_t addr;
}ADC_DMA_NOW_t;
//0x68
typedef union ADC_DMA_BEG {
	struct {

	};
	uint16_t addr;
}ADC_DMA_BEG_t;
//0x6C
typedef union ADC_DMA_END {
	struct {

	};
	uint16_t addr;
}ADC_DMA_END_t;

typedef union ADC_Module {
	struct {
		ADC_CHANNEL_t		ADC_CHANNEL;	//0x58
		ADC_CFG_t			ADC_CFG;		//0x59
		ADC_CONVERT_t		ADC_CONVERT;	//0x5A
		TEM_SENSOR_t		TEM_SENSOR;		//0x5B//
		ADC_DATA_t			ADC_DATA;		//0x5C-5D
		ADC_INT_FLAG_t		ADC_INT_FLAG;	//0x5E
		uint8_t : 8;						//0x5F//
		uint8_t : 8;						//0x60
		ADC_CTRL_DMA_t		ADC_CTRL_DMA;	//0x61
		ADC_DMA_IF_t		ADC_DMA_IF;		//0x62
		ADC_AUTO_CYCLE_t	ADC_AUTO_CYCLE; //0x63//
		ADC_DMA_NOW_t		ADC_DMA_NOW;	//0x64-65
		uint16_t : 16;						//0x66-67//
		ADC_DMA_BEG_t		ADC_DMA_BEG;	//0x68-69
		uint16_t : 16;						//0x6A-6B//
		ADC_DMA_END_t		ADC_DMA_END;	//0x6C-6D
		uint16_t : 16;						//0x6E-6F//
	};
	struct {
		uint32_t : 32;						//0x58-5B//
		uint32_t : 32;						//0x5C-5F//
		ADC_DMA_CTRL_t		ADC_DMA_CTRL;	//0x60-63//
		uint32_t : 32;						//0x64-67//
		uint32_t : 32;						//0x68-6B//
		uint32_t : 32;						//0x6C-6F//
	};
}ADC_Module_t;
//
// TKEY
//
#define Touch_Key			(*(volatile TKEY_Module_t*)		0x40001054)
#define x8_TKEY_COUNT		(*(volatile ADC_CHANNEL_t*)		0x40001054)
/*-----0x40001055 is RSVD-----*/
#define x8_TKEY_CONVERT		(*(volatile ADC_CFG_t*)			0x40001056)
#define x8_TKEY_CFG			(*(volatile ADC_CHANNEL_t*)		0x40001057)
//
// ADC
//
#define ADC					(*(volatile ADC_Module_t*)		0x40001058)
#define x8_ADC_CHANNEL		(*(volatile ADC_CHANNEL_t*)		0x40001058)
#define x8_ADC_CFG			(*(volatile ADC_CFG_t*)			0x40001059)
#define x8_ADC_CONVERT		(*(volatile ADC_CONVERT_t*)		0x4000105A)
#define x8_TEM_SENSOR		(*(volatile TEM_SENSOR_t*)		0x4000105B)
#define x16_ADC_DATA		(*(volatile ADC_DATA_t*)		0x4000105C)
#define x8_ADC_INT_FLAG		(*(volatile ADC_INT_FLAG_t*)	0x4000105E)
/*-----0x4000105F is RSVD-----*/
#define x32_ADC_DMA_CTRL	(*(volatile ADC_DMA_CTRL_t*)	0x40001060)
#define x8_ADC_CTRL_DMA		(*(volatile ADC_CTRL_DMA_t*)	0x40001061)
#define x8_ADC_DMA_IF		(*(volatile ADC_DMA_IF_t*)		0x40001062)
#define x8_ADC_AUTO_CYCLE	(*(volatile ADC_AUTO_CYCLE_t*)	0x40001063)
#define x16_ADC_DMA_NOW		(*(volatile ADC_DMA_NOW_t*)		0x40001064)
/*-----0x40001066-67 is RSVD-----*/
#define x16_ADC_DMA_BEG		(*(volatile ADC_DMA_BEG_t*)		0x40001068)
/*-----0x4000106A-6B is RSVD-----*/
#define x16_ADC_DMA_END		(*(volatile ADC_DMA_END_t*)		0x4000106C)
/*-----0x4000106E-6F is RSVD-----*/


#endif // !__CH58xADCSFR__
