#pragma once

#ifndef __CH58xTMRSFR__
#define __CH58xTMRSFR__
#include "CH58x_SFR_TOP_LVL.h" 

typedef union TMR_CTRL_MOD {
	struct {
		uint8_t TMR_MODE_IN : 1;
		uint8_t TMR_ALL_CLEAR : 1;
		uint8_t TMR_COUNT_EN : 1;
		uint8_t TMR_OUT_EN : 1;
		uint8_t TMR_OUT_POLAR : 1;
		uint8_t : 1;
		uint8_t TMR_PWM_REPEAT : 2;
	}PWM;
	struct {
		uint8_t TMR_MODE_IN : 1;
		uint8_t TMR_ALL_CLEAR : 1;
		uint8_t TMR_COUNT_EN : 1;
		uint8_t TMR_OUT_EN : 1;
		uint8_t TMR_CAP_COUNT : 1;
		uint8_t : 1;
		uint8_t TMR_CAP_EDGE : 2;
	}CNT;
	uint8_t byte;
}TMR_CTRL_MOD_t;
typedef union TMR_INTER_EN {
	struct {
		uint8_t TMR_IE_CYC_END : 1;
		uint8_t TMR_IE_DATA_ACT : 1;
		uint8_t TMR_IE_FIFO_HF : 1;
		uint8_t TMR_IE_DMA_END : 1;
		uint8_t TMR_IE_FIFO_OV : 1;
		uint8_t : 3;
	};
	uint8_t byte;
}TMR_INTER_EN_t;
typedef union TMR_INT_FLAG {
	struct {
		uint8_t TMR_IF_CYC_END : 1;
		uint8_t TMR_IF_DATA_ACT : 1;
		uint8_t TMR_IF_FIFO_HF : 1;
		uint8_t TMR_IF_DMA_END : 1;
		uint8_t TMR_IF_FIFO_OV : 1;
		uint8_t : 3;
	};
	uint8_t byte;
}TMR_INT_FLAG_t;
typedef union TMR_FIFO_COUNT {
	struct {
		uint8_t COUNT;
	};
	uint8_t byte;
}TMR_FIFO_COUNT_t;
typedef union TMR_COUNT {
	struct {
		
	};
	uint32_t COUNT;
}TMR_COUNT_t;
typedef union TMR_CNT {
	struct {
		uint32_t DATA_L : 16;
		uint32_t DATA_H : 10;
		uint32_t : 6;
	};
	uint32_t DATA;
}TMR_CNT_t;
typedef union TMR_FIFO {
	struct {
		uint32_t DATA;
	};
}TMR_FIFO_t;
typedef union TMR_CTRL_DMA {
	struct {
		uint8_t TMR_DMA_ENABLE : 1;
		uint8_t : 1;
		uint8_t TMR_DMA_LOOP : 1;
		uint8_t : 5;
	};
	uint8_t byte;
}TMR_CTRL_DMA_t;
typedef union TMR_DMA_ADDR {
	struct {
		uint16_t DMA_ADDRL : 8;
		uint16_t DMA_ADDRH : 8;
	};
	uint16_t ADDR;
}TMR_DMA_ADDR_t;

typedef struct TMR_0_3_REG {
	TMR_CTRL_MOD_t		CTRL_MOD;	//0x00
	uint8_t : 8;					//0x01
	TMR_INTER_EN_t		INTER_EN;	//0x02
	uint8_t : 8;					//0x03//
	uint16_t : 16;					//0x04-05
	TMR_INT_FLAG_t		INT_FLAG;	//0x06
	TMR_FIFO_COUNT_t	FIFO_COUNT;	//0x07//
	TMR_COUNT_t			COUNT;		//0x08-0B//
	TMR_CNT_t			CNT_END;	//0x0C-0F
	TMR_FIFO_t			FIFO;		//0x10-13//
}TMR_0_3_REG_t;

typedef struct TMR_Module {
	TMR_CTRL_MOD_t		CTRL_MOD;	//0x00
	TMR_CTRL_DMA_t		CTRL_DMA;	//0x01
	TMR_INTER_EN_t		INTER_EN;	//0x02
	uint8_t : 8;					//0x03//
	uint16_t : 16;					//0x04-05
	TMR_INT_FLAG_t		INT_FLAG;	//0x06
	TMR_FIFO_COUNT_t	FIFO_COUNT;	//0x07//
	TMR_COUNT_t			COUNT;		//0x08-0B//
	TMR_CNT_t			CNT_END;	//0x0C-0F//
	TMR_FIFO_t			FIFO;		//0x10-13//
	TMR_DMA_ADDR_t		DMA_NOW;	//0x14-17//
	TMR_DMA_ADDR_t		DMA_BEG;	//0x18-1A//
	TMR_DMA_ADDR_t		DMA_END;	//0x1C-1F//
}TMR_Module_t;
//
// TMR0
//
#define TMR0			(*(volatile TMR_Module_t*)	  		0x40002000)
#define x8_TMR0_CTRL_MOD	 (*(volatile TMR_CTRL_MOD_t*)		0x40002000)
/*-----0x40002001 is RSVD-----*/
#define x8_TMR0_INTER_EN	 (*(volatile TMR_INTER_EN_t*)		0x40002002)
/*-----0x40002003-05 is RSVD-----*/
#define x8_TMR0_INT_FLAG	 (*(volatile TMR_INT_FLAG_t*)		0x40002006)
#define x8_TMR0_FIFO_COUNT	 (*(volatile TMR_FIFO_COUNT_t*)		0x40002007)
#define x32_TMR0_COUNT		 (*(volatile TMR_COUNT_t*)			0x40002008)
#define x32_TMR0_CNT_END	 (*(volatile TMR_CNT_t*)			0x4000200C)
#define x32_TMR0_FIFO		 (*(volatile TMR_FIFO_t*)			0x40002010)
//
// TMR1
//
#define TMR1			(*(volatile TMR_Module_t*)			0x40002400)
#define x8_TMR1_CTRL_MOD	 (*(volatile TMR_CTRL_MOD_t*)		0x40002400)
#define x8_TMR1_CTRL_DMA	 (*(volatile TMR_CTRL_DMA_t*)		0x40002401)
#define x8_TMR1_INTER_EN	 (*(volatile TMR_INTER_EN_t*)		0x40002402)
/*-----0x40002403-05 is RSVD-----*/
#define x8_TMR1_INT_FLAG	 (*(volatile TMR_INT_FLAG_t*)		0x40002406)
#define x8_TMR1_FIFO_COUNT	 (*(volatile TMR_FIFO_COUNT_t*)	0x40002407)
#define x32_TMR1_COUNT		 (*(volatile TMR_COUNT_t*)			0x40002408)
#define x32_TMR1_CNT_END	 (*(volatile TMR_CNT_t*)			0x4000240C)
#define x32_TMR1_FIFO		 (*(volatile TMR_FIFO_t*)			0x40002410)
#define x16_TMR1_DMA_NOW	 (*(volatile TMR_DMA_ADDR_t*)		0x40002414)
/*-----0x40002416-17 is RSVD-----*/
#define x16_TMR1_DMA_BEG	 (*(volatile TMR_DMA_ADDR_t*)		0x40002418)
/*-----0x4000241A-1B is RSVD-----*/
#define x16_TMR1_DMA_END	 (*(volatile TMR_DMA_ADDR_t*)		0x4000241C)
//
// TMR2
//
#define TMR2			(*(volatile TMR_Module_t*)			0x40002800)
#define x8_TMR2_CTRL_MOD	 (*(volatile TMR_CTRL_MOD_t*)		0x40002800)
#define x8_TMR2_CTRL_DMA	 (*(volatile TMR_CTRL_DMA_t*)		0x40002801)
#define x8_TMR2_INTER_EN	 (*(volatile TMR_INTER_EN_t*)		0x40002802)
/*-----0x40002803-05 is RSVD-----*/
#define x8_TMR2_INT_FLAG	 (*(volatile TMR_INT_FLAG_t*)		0x40002806)
#define x8_TMR2_FIFO_COUNT	 (*(volatile TMR_FIFO_COUNT_t*)	0x40002807)
#define x32_TMR2_COUNT		 (*(volatile TMR_COUNT_t*)			0x40002808)
#define x32_TMR2_CNT_END	 (*(volatile TMR_CNT_t*)			0x4000280C)
#define x32_TMR2_FIFO		 (*(volatile TMR_FIFO_t*)			0x40002810)
#define x16_TMR2_DMA_NOW	 (*(volatile TMR_DMA_ADDR_t*)		0x40002814)
/*-----0x40002816-17 is RSVD-----*/
#define x16_TMR2_DMA_BEG	 (*(volatile TMR_DMA_ADDR_t*)		0x40002818)
/*-----0x4000281A-1B is RSVD-----*/
#define x16_TMR2_DMA_END	 (*(volatile TMR_DMA_ADDR_t*)		0x4000281C)
//
// TMR3
//
#define TMR3			(*(volatile TMR_Module_t*)			0x40002C00)
#define x8_TMR3_CTRL_MOD	 (*(volatile TMR_CTRL_MOD_t*)		0x40002C00)
/*-----0x40002C01 is RSVD-----*/
#define x8_TMR3_INTER_EN	 (*(volatile TMR_INTER_EN_t*)		0x40002C02)
/*-----0x40002C03-05 is RSVD-----*/
#define x8_TMR3_INT_FLAG	 (*(volatile TMR_INT_FLAG_t*)		0x40002C06)
#define x8_TMR3_FIFO_COUNT	 (*(volatile TMR_FIFO_COUNT_t*)		0x40002C07)
#define x32_TMR3_COUNT		 (*(volatile TMR_COUNT_t*)			0x40002C08)
#define x32_TMR3_CNT_END	 (*(volatile TMR_CNT_t*)			0x40002C0C)
#define x32_TMR3_FIFO		 (*(volatile TMR_FIFO_t*)			0x40002C10)
#endif // !__CH58xTMRSFR__
