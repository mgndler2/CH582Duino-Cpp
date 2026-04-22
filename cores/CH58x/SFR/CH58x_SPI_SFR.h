#ifndef __CH58xSPISFR__
#define __CH58xSPISFR__

#include "CH58x_SFR_TOP_LVL.h"
//0x00
typedef union SPI_CTRL_MOD {
	struct {
		uint8_t SPI_MODE_SLAVE : 1;
		uint8_t SPI_ALL_CLEAR : 1;
		uint8_t SPI_2WIRE_MOD : 1;
		uint8_t SPI_MST_SCK_MOD : 1;		
		uint8_t SPI_FIFO_DIR : 1;
		uint8_t SPI_SCK_OE : 1;
		uint8_t SPI_MOSI_OE : 1;
		uint8_t SPI_MISO_OE : 1;
	};
	struct {
		uint8_t : 3;
		uint8_t SPI_SLV_CMD_MOD : 1;
		uint8_t : 4;
	};
	uint8_t byte;
}SPI_CTRL_MOD_t;
//0x01
typedef union SPI_CTRL_CFG {
	struct {
		uint8_t SPI_DMA_ENABLE : 1;
		uint8_t : 1;
		uint8_t SPI_DMA_LOOP : 1;
		uint8_t : 1;
		uint8_t SPI_AUTO_IF : 1;
		uint8_t SPI_BIT_ORDER : 1;
		uint8_t SPI_MST_DLY_EN : 1;
		uint8_t : 1;
	};
	uint8_t byte;
}SPI_CTRL_CFG_t;
//0x02
typedef union SPI_INTER_EN {
	struct {
		uint8_t SPI_IE_CNT_END : 1;
		uint8_t SPI_IE_BYTE_END : 1;
		uint8_t SPI_IE_FIFO_HF : 1;
		uint8_t SPI_IE_DMA_END : 1;
		uint8_t SPI_IE_FIFO_OV : 1;
		uint8_t : 2;
		uint8_t SPI_IE_FST_BYTE : 1;
	};
	uint8_t byte;
}SPI_INTER_EN_t;
//0x03
typedef union SPI_CLOCK_DIV {
	struct {
		uint8_t DIV;
	};
	
}SPI_CLOCK_DIV_t;
//0x03
typedef union SPI_SLAVE_PRE {
	struct {
		uint8_t data;
	};

}SPI_SLAVE_PRE_t;
//0x04
typedef union SPI_BUFFER {
	struct {
		uint8_t data;
	};

}SPI_BUFFER_t;
//0x05
typedef union SPI_RUN_FLAG {
	struct {
		uint8_t : 4;
		uint8_t SPI_SLV_CMD_ACT : 1;
		uint8_t SPI_FIFO_READY : 1;
		uint8_t SPI_SLV_CS_LOAD : 1;
		uint8_t SPI_SLV_SELECT : 1;
	};
	uint8_t byte;
}SPI_RUN_FLAG_t;
//0x06
typedef union SPI_INT_FLAG {
	struct {
		uint8_t SPI_IF_CNT_END : 1;
		uint8_t SPI_IF_BYTE_END : 1;
		uint8_t SPI_IF_FIFO_HF : 1;
		uint8_t SPI_IF_DMA_END : 1;
		uint8_t SPI_IF_FIFO_OV : 1;
		uint8_t : 1;
		uint8_t SPI_FREE : 1;
		uint8_t SPI_IF_FST_BYTE : 1;
	};
	uint8_t byte;
}SPI_INT_FLAG_t;
//0x07
typedef union SPI_FIFO_COUNT {
	struct {
		uint8_t length;
	};

}SPI_FIFO_COUNT_t;
//0x0C
typedef union SPI_TOTAL_CNT {
	struct {
		
	};
	uint16_t length;
}SPI_TOTAL_CNT_t;
//0x10
typedef union SPI_FIFO {
	struct {
		uint8_t data;
	};

}SPI_FIFO_t;
//0x14
typedef union SPI_DMA_NOW {
	struct {
		
	};
	uint16_t addr;
}SPI_DMA_NOW_t;
//0x18
typedef union SPI_DMA_BEG {
	struct {

	};
	uint16_t addr;
}SPI_DMA_BEG_t;
//0x1C
typedef union SPI_DMA_END {
	struct {

	};
	uint16_t addr;
}SPI_DMA_END_t;

typedef union SPI_Module {
	struct {
		SPI_CTRL_MOD_t		SPI_MOD;		//0x00
		SPI_CTRL_CFG_t		SPI_CFG;		//0x01
		SPI_INTER_EN_t		INTER_EN;		//0x02
		union {								//0x03//
			SPI_CLOCK_DIV_t		CLOCK_DIV;
			SPI_SLAVE_PRE_t		SLAVE_PRE;
		};
		SPI_BUFFER_t		SPI_BUFFER;		//0x04
		SPI_RUN_FLAG_t		SPI_RUN_FLAG;	//0x05
		SPI_INT_FLAG_t		SPI_INT_FLAG;	//0x06
		SPI_FIFO_COUNT_t	FIFO_COUNT;		//0x07//
		uint32_t : 32;						//0x08-0B//
		SPI_TOTAL_CNT_t		SPI_TOTAL_CNT;	//0x0C-0D
		uint16_t : 16;						//0x0E-0F//
		SPI_FIFO_t			FIFO;			//0x10
		uint16_t : 16;						//0x11-12
		SPI_FIFO_COUNT_t	FIFO_COUNT1;	//0x13//
		SPI_DMA_NOW_t		SPI_DMA_NOW;	//0x14-15
		uint16_t : 16;						//0x16-17//
		SPI_DMA_BEG_t		SPI_DMA_BEG;	//0x18-19
		uint16_t : 16;						//0x1A-1B//
		SPI_DMA_END_t		SPI_DMA_END;	//0x1C-1D
		uint16_t : 16;						//0x1E-1F//
	};
}SPI_Module_t;
//
// SPI0
//
#define SPI0				(*(volatile SPI_Module_t*)			0x40004000)
#define x8_SPI0_CTRL_MOD		(*(volatile SPI_CTRL_MOD_t*)		0x40004000)
#define x8_SPI0_CTRL_CFG		(*(volatile SPI_CTRL_CFG_t*)		0x40004001)
#define x8_SPI0_INTER_EN		(*(volatile SPI_INTER_EN_t*)		0x40004002)
#define x8_SPI0_CLOCK_DIV		(*(volatile SPI_CLOCK_DIV_t*)		0x40004003)
#define x8_SPI0_SLAVE_PRE		(*(volatile SPI_SLAVE_PRE_t*)		0x40004003)
#define x8_SPI0_BUFFER			(*(volatile SPI_BUFFER_t*)			0x40004004)
#define x8_SPI0_RUN_FLAG		(*(volatile SPI_RUN_FLAG_t*)		0x40004005)
#define x8_SPI0_INT_FLAG		(*(volatile SPI_INT_FLAG_t*)		0x40004006)
#define x8_SPI0_FIFO_COUNT		(*(volatile SPI_FIFO_COUNT_t*)		0x40004007)
/*-----0x40004008-0B is RSVD-----*/
#define x16_SPI0_TOTAL_CNT		(*(volatile SPI_TOTAL_CNT_t*)		0x4000400C)
/*-----0x4000400E-0F is RSVD-----*/
#define x8_SPI0_FIFO			(*(volatile SPI_FIFO_t*)			0x40004010)
/*-----0x40004011-12 is RSVD-----*/
#define x8_SPI0_FIFO_COUNT1		(*(volatile SPI_FIFO_COUNT_t*)		0x40004013)
#define x16_SPI0_DMA_NOW		(*(volatile SPI_DMA_NOW_t*)			0x40004014)
/*-----0x40004016-17 is RSVD-----*/
#define x16_SPI0_DMA_BEG		(*(volatile SPI_DMA_BEG_t*)			0x40004018)
/*-----0x4000401A-1B is RSVD-----*/
#define x16_SPI0_DMA_END		(*(volatile SPI_DMA_END_t*)			0x4000401C)
/*-----0x4000401E-1F is RSVD-----*/
//
// SPI1
//
#define SPI1				(*(volatile SPI_Module_t*)			0x40004400)
#define x8_SPI1_CTRL_MOD		(*(volatile SPI_CTRL_MOD_t*)		0x40004400)
#define x8_SPI1_CTRL_CFG		(*(volatile SPI_CTRL_CFG_t*)		0x40004401)
#define x8_SPI1_INTER_EN		(*(volatile SPI_INTER_EN_t*)		0x40004402)
#define x8_SPI1_CLOCK_DIV		(*(volatile SPI_CLOCK_DIV_t*)		0x40004403)
#define x8_SPI1_SLAVE_PRE		(*(volatile SPI_SLAVE_PRE_t*)		0x40004403)
#define x8_SPI1_BUFFER			(*(volatile SPI_BUFFER_t*)			0x40004404)
#define x8_SPI1_RUN_FLAG		(*(volatile SPI_RUN_FLAG_t*)		0x40004405)
#define x8_SPI1_INT_FLAG		(*(volatile SPI_INT_FLAG_t*)		0x40004406)
#define x8_SPI1_FIFO_COUNT		(*(volatile SPI_FIFO_COUNT_t*)		0x40004407)
/*-----0x40004008-0B is RSVD-----*/
#define x16_SPI1_TOTAL_CNT		(*(volatile SPI_TOTAL_CNT_t*)		0x4000440C)
/*-----0x4000400E-0F is RSVD-----*/
#define x8_SPI1_FIFO			(*(volatile SPI_FIFO_t*)			0x40004410)
/*-----0x40004011-12 is RSVD-----*/
#define x8_SPI1_FIFO_COUNT1		(*(volatile SPI_FIFO_COUNT_t*)		0x40004413)
/*-----0x40004014-1F is RSVD-----*/

#endif // !__CH58xSPISFR__
