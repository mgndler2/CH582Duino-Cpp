#pragma once

#ifndef __CH58xUSBSFR__
#define __CH58xUSBSFR__
#define MAX_PACKET_SIZE		64
#include "CH58x_SFR_TOP_LVL.h" 
//0x00
typedef union USB_CTRL {
	struct {
		uint8_t UC_DMA_EN : 1;		// DMA enable and DMA interrupt enable for USB
		uint8_t UC_CLR_ALL : 1;		// force clear FIFO and count of USB
		uint8_t UC_RESET_SIE : 1;	// force reset USB SIE, need software clear
		uint8_t UC_INT_BUSY : 1;	// enable automatic responding busy for device mode or automatic pause for host mode during interrupt flag UIF_TRANSFER valid
		uint8_t UC_SYS_CTRL : 2;	// bit mask of USB system control
		uint8_t UC_LOW_SPEED : 1;	// enable USB low speed: 0=12Mbps, 1=1.5Mbps
		uint8_t UC_HOST_MODE : 1;	// enable USB host mode: 0=device mode, 1=host mode
	};
	struct {
		uint8_t : 5;
		uint8_t UC_DEV_PU_EN : 1;	// USB device enable and internal pullup resistance enable
		uint8_t : 2;
	};
	uint8_t byte;
}USB_CTRL_t;
//0x01
typedef union UDEV_CTRL {
	struct {
		uint8_t UD_PORT_EN : 1;
		uint8_t UD_GP_BIT : 1;
		uint8_t UD_LOW_SPEED : 1;
		uint8_t : 1;
		uint8_t UD_DM_PIN : 1;
		uint8_t UD_DP_PIN : 1;
		uint8_t : 1;
		uint8_t UD_PD_DIS : 1;
	};
	uint8_t byte;
}UDEV_CTRL_t;
//0x01
typedef union UHOST_CTRL {
	struct {
		uint8_t UH_PORT_EN : 1;
		uint8_t UH_BUS_RESET : 1;
		uint8_t UH_LOW_SPEED : 1;
		uint8_t : 1;
		uint8_t UH_DM_PIN : 1;
		uint8_t UH_DP_PIN : 1;
		uint8_t : 1;
		uint8_t UH_PD_DIS : 1;
	};
	uint8_t byte;
}UHOST_CTRL_t;
//0x02
typedef union USB_INT_EN {
	struct {		//DEVICE
		uint8_t UIE_BUS_RST : 1;
		uint8_t UIE_TRANSFER : 1;
		uint8_t UIE_SUSPEND : 1;
		uint8_t : 1;
		uint8_t UIE_FIFO_OV : 1;
		uint8_t : 1;
		uint8_t UIE_DEV_NAK : 1;
		uint8_t UIE_DEV_SOF : 1;
	}DEVICE;
	struct {		//HOST
		uint8_t UIE_DETECT : 1;
		uint8_t UIE_TRANSFER : 1;
		uint8_t UIE_SUSPEND : 1;
		uint8_t UIE_HST_SOF : 1;
		uint8_t UIE_FIFO_OV : 1;
		uint8_t : 3;
	}HOST;
	uint8_t byte;
}USB_INT_EN_t;
//0x03
typedef union USB_DEV_AD {
	struct {
		uint8_t USB_ADDR : 7;
		uint8_t UDA_GP_BIT : 1;
	};
	uint8_t byte;
}USB_DEV_AD_t;
//0x05
typedef union USB_MIS_ST {
	struct {
		uint8_t : 2;
		uint8_t UMS_SUSPEND : 1;
		uint8_t UMS_BUS_RESET : 1;
		uint8_t UMS_R_FIFO_RDY : 1;
		uint8_t UMS_SIE_FREE : 1;
		uint8_t : 2;
	}DEVICE;
	struct {
		uint8_t UMS_DEV_ATTACH : 1;
		uint8_t UMS_DM_LEVEL : 1;
		uint8_t UMS_SUSPEND : 1;
		uint8_t UMS_BUS_RESET : 1;
		uint8_t UMS_R_FIFO_RDY : 1;
		uint8_t UMS_SIE_FREE : 1;
		uint8_t UMS_SOF_ACT : 1;
		uint8_t UMS_SOF_PRES : 1;
	}HOST;
	uint8_t byte;
}USB_MIS_ST_t;
//0x06
typedef union USB_INT_FG {
	struct {
		uint8_t UIF_BUS_RST : 1;
		uint8_t UIF_TRANSFER : 1;
		uint8_t UIF_SUSPEND : 1;
		uint8_t : 1;
		uint8_t UIF_FIFO_OV : 1;
		uint8_t U_SIE_FREE : 1;
		uint8_t U_TOG_OK : 1;
		uint8_t U_IS_NAK : 1;
	}DEVICE;
	struct {
		uint8_t UIF_DETECT : 1;
		uint8_t UIF_TRANSFER : 1;
		uint8_t UIF_SUSPEND : 1;
		uint8_t UIF_HST_SOF : 1;
		uint8_t UIF_FIFO_OV : 1;
		uint8_t U_SIE_FREE : 1;
		uint8_t U_TOG_OK : 1;
		uint8_t : 1;
	}HOST;
	uint8_t byte;
}USB_INT_FG_t;
//0x07
typedef union USB_INT_ST {
	struct {
		uint8_t UIS_ENDP : 4;
		uint8_t UIS_TOKEN : 2;
		uint8_t UIS_TOG_OK : 1;
		uint8_t UIS_SETUP_ACT : 1;
	}DEVICE;
	struct {
		uint8_t UIS_H_RES : 4;
		uint8_t : 2;
		uint8_t UIS_TOG_OK : 1;
		uint8_t : 1;
	}HOST;
	uint8_t byte;
}USB_INT_ST_t;
//0x08
typedef union USB_RX_LEN {
	struct {
		uint8_t length;
	};
}USB_RX_LEN_t;
//0x0C
typedef union UEP4_1_MOD {
	union {
		struct {
			uint8_t : 4;
			uint8_t BUF_MOD : 1;
			uint8_t : 1;
			uint8_t TX_EN : 1;
			uint8_t RX_EN : 1;
		};
		struct {
			uint8_t : 6;
			uint8_t RX_TX : 2;
		};
	}UEP1;
	union {
		struct {
			uint8_t : 2;
			uint8_t TX_EN : 1;
			uint8_t RX_EN : 1;
			uint8_t : 4;
		};
		struct {
			uint8_t : 2;
			uint8_t RX_TX : 2;
			uint8_t : 4;
		};
	}UEP4;
	uint8_t byte;
}UEP4_1_MOD_t;
//0x0D
typedef union UEP2_3_MOD {
	union {
		struct {
			uint8_t BUF_MOD : 1;
			uint8_t : 1;
			uint8_t TX_EN : 1;
			uint8_t RX_EN : 1;
			uint8_t : 4;
		};
		struct {
			uint8_t : 2;
			uint8_t RX_TX : 2;
			uint8_t : 4;
		};
	}UEP2;
	union {
		struct {
			uint8_t : 4;
			uint8_t BUF_MOD : 1;
			uint8_t : 1;
			uint8_t TX_EN : 1;
			uint8_t RX_EN : 1;
		};
		struct {
			uint8_t : 6;
			uint8_t RX_TX : 2;
		};
	}UEP3;
	uint8_t byte;
}UEP2_3_MOD_t;
//0x0D
typedef union UH_EP_MOD {
	struct {
		uint8_t UH_EP_RBUF_MOD : 1;
		uint8_t : 2;
		uint8_t UH_EP_RX_EN : 1;
		uint8_t UH_EP_TBUF_MOD : 1;
		uint8_t : 1;
		uint8_t UH_EP_TX_EN : 1;
		uint8_t : 1;
	};
	uint8_t byte;
}UH_EP_MOD_t;
//0x0E
typedef union UEP567_MOD {
	union {
		struct {
			uint8_t TX_EN : 1;
			uint8_t RX_EN : 1;
			uint8_t : 6;
		};
		struct {
			uint8_t RX_TX : 2;
			uint8_t : 6;
		};
	}UEP5;
	union {
		struct {
			uint8_t : 2;
			uint8_t TX_EN : 1;
			uint8_t RX_EN : 1;
			uint8_t : 4;
		};
		struct {
			uint8_t : 2;
			uint8_t RX_TX : 2;
			uint8_t : 4;
		};
	}UEP6;
	union {
		struct {
			uint8_t : 4;
			uint8_t TX_EN : 1;
			uint8_t RX_EN : 1;
			uint8_t : 2;
		};
		struct {
			uint8_t : 4;
			uint8_t RX_TX : 2;
			uint8_t : 2;
		};
	}UEP7;
	uint8_t byte;
}UEP567_MOD_t;
//0x10,0x14,0x18,0x1C,0x54,0x58,0x5C
typedef union UEPn_DMA {
	struct {
		uint16_t addrL : 8;
		uint16_t addrH : 8;
	};
	uint16_t DMA_addr;
}UEPn_DMA_t;
//0x18,0x1C
typedef union UH_XX_DMA {
	struct {

	};
	uint16_t DMA_addr;
}UH_XX_DMA_t;
//0x20,0x24,0x28,0x2c,0x30,0x64,0x68,0x6C
typedef union UEPn_T_LEN {
	struct {
		uint8_t length;
	};

}UEPn_T_LEN_t;
//0x22,0x26,0x2A,0x2E,0x32,0x66,0x6A,0x6E
typedef union UEPn_CTRL {
	struct {
		uint8_t UEP_T_RES : 2;
		uint8_t UEP_R_RES : 2;
		uint8_t UEP_AUTO_TOG : 1;
		uint8_t : 1;
		uint8_t UEP_T_TOG : 1;
		uint8_t UEP_R_TOG : 1;
	};
	uint8_t byte;
}UEPn_CTRL_t;
//0x26
typedef union UH_SETUP {
	struct {
		uint8_t : 5;
		uint8_t UH_SOF_EN : 1;
		uint8_t UH_PRE_PID_EN : 1;
	};
	uint8_t byte;
}UH_SETUP_t;
//0x28
typedef union UH_EP_PID {
	struct {
		uint8_t UH_ENDP : 4;
		uint8_t UH_TOKEN : 4;
	};
	uint8_t byte;
}UH_EP_PID_t;
//0x2A
typedef union UH_RX_CTRL {
	struct {

		uint8_t : 2;
		uint8_t UH_R_RES : 1;
		uint8_t : 1;
		uint8_t UH_R_AUTO_TOG : 1;
		uint8_t : 2;
		uint8_t UH_R_TOG : 1;
	};
	uint8_t byte;
}UH_RX_CTRL_t;
//0x2C
typedef union UH_TX_LEN {
	struct {
		uint8_t length;
	};

}UH_TX_LEN_t;
//0x2E
typedef union UH_TX_CTRL {
	struct {
		uint8_t UH_T_RES : 1;
		uint8_t : 3;
		uint8_t UH_T_AUTO_TOG : 1;
		uint8_t : 1;
		uint8_t UH_T_TOG : 1;
		uint8_t : 1;
	};
	uint8_t byte;
}UH_TX_CTRL_t;

typedef struct USB_Module {
	USB_CTRL_t		USB_CTRL;	//0x00
	union {						//0x01
		UDEV_CTRL_t		UDEV_CTRL;
		UHOST_CTRL_t	UHOST_CTRL;
	};
	USB_INT_EN_t	INT_EN;	//0x02
	USB_DEV_AD_t	DEV_AD;	//0x03//
	uint8_t : 8;				//0x04
	USB_MIS_ST_t	MIS_ST;	//0x05
	USB_INT_FG_t	INT_FG;	//0x06
	USB_INT_ST_t	INT_ST;	//0x07//
	USB_RX_LEN_t	RX_LEN;	//0x08
	uint8_t : 8;				//0x09
	uint16_t : 16;				//0x0A-0B//
	UEP4_1_MOD_t	UEP4_1_MOD;	//0x0C
	union {						//0x0D
		UEP2_3_MOD_t	UEP2_3_MOD;
		UH_EP_MOD_t		UH_EP_MOD;
	};
	UEP567_MOD_t	UEP567_MOD;	//0x0E
	uint8_t : 8;				//0x0F//
	UEPn_DMA_t		UEP0_DMA;	//0x10-11
	uint16_t : 16;				//0x12-13//
	UEPn_DMA_t		UEP1_DMA;	//0x14-15
	uint16_t : 16;				//0x16-17//
	union {						//0x18-19
		UEPn_DMA_t		UEP2_DMA;
		UH_XX_DMA_t		RX_DMA;
	};
	uint16_t : 16;				//0x1A-1B
	union {						//0x1C-1D
		UEPn_DMA_t		UEP3_DMA;
		UH_XX_DMA_t		TX_DMA;
	};
	uint16_t : 16;				//0x1E-1F//
	UEPn_T_LEN_t	UEP0_T_LEN;	//0x20
	uint8_t : 8;				//0x21
	UEPn_CTRL_t		UEP0_CTRL;	//0x22
	uint8_t : 8;				//0x23//
	UEPn_T_LEN_t	UEP1_T_LEN;	//0x24
	uint8_t : 8;
	UEPn_CTRL_t		UEP1_CTRL;	//0x26
	uint8_t : 8;				//0x27//
	UEPn_T_LEN_t	UEP2_T_LEN;	//0x28
	uint8_t : 8;				//0x29
	UEPn_CTRL_t		UEP2_CTRL;	//0x2A
	uint8_t : 8;				//0x2B//
	UEPn_T_LEN_t	UEP3_T_LEN;	//0x2C
	uint8_t : 8;				//0x2D
	UEPn_CTRL_t		UEP3_CTRL;	//0x2E
	uint8_t : 8;				//0x2F//
	UEPn_T_LEN_t	UEP4_T_LEN;	//0x30
	uint8_t : 8;				//0x31
	UEPn_CTRL_t		UEP4_CTRL;	//0x32
	uint8_t : 8;				//0x33//
	uint32_t : 32;				//0x34-37//
	uint32_t : 32;				//0x38-3B//
	uint32_t : 32;				//0x3C-3F//
	uint32_t : 32;				//0x40-43//
	uint32_t : 32;				//0x44-47//
	uint32_t : 32;				//0x48-4B//
	uint32_t : 32;				//0x4C-4F//
	uint32_t : 32;				//0x50-53//
	UEPn_DMA_t		UEP5_DMA;	//0x54-55
	uint16_t : 16;				//0x56-57//
	UEPn_DMA_t		UEP6_DMA;	//0x58-59
	uint16_t : 16;				//0x5A-5B//
	UEPn_DMA_t		UEP7_DMA;	//0x5C-5D
	uint16_t : 16;				//0x5E-5F//
	uint32_t : 32;				//0x60-63//
	UEPn_T_LEN_t	UEP5_T_LEN;	//0x64
	uint8_t : 8;				//0x65
	UEPn_CTRL_t		UEP5_CTRL;	//0x66
	uint8_t : 8;				//0x67//
	UEPn_T_LEN_t	UEP6_T_LEN;	//0x68
	uint8_t : 8;				//0x69
	UEPn_CTRL_t		UEP6_CTRL;	//0x6A
	uint8_t : 8;				//0x6B//
	UEPn_T_LEN_t	UEP7_T_LEN;	//0x6C
	uint8_t : 8;				//0x6D
	UEPn_CTRL_t		UEP7_CTRL;	//0x6E
	uint8_t : 8;				//0x6F//
}USB_Module_t;
//
// USB
//
#define USB			(*(volatile USB_Module_t*)	 0x40008000)
#define x8_USB_CTRL		(*(volatile USB_CTRL_t*)		0x40008000)	// USB base control
#define x8_UDEV_CTRL	(*(volatile UDEV_CTRL_t*)		0x40008001)	// USB device physical prot control
#define x8_UHOST_CTRL	(*(volatile UHOST_CTRL_t*)		0x40008001)	// USB host physical prot control
#define x8_USB_INT_EN	(*(volatile USB_INT_EN_t*)		0x40008002)	// USB interrupt enable
#define x8_USB_DEV_AD	(*(volatile USB_DEV_AD_t*)		0x40008003)	// USB device address
/*-----0x40008004 is RSVD-----*/
#define x8_USB_MIS_ST	(*(volatile USB_MIS_ST_t*)		0x40008005)	// USB miscellaneous status
#define x8_USB_INT_FG	(*(volatile USB_INT_FG_t*)		0x40008006)	// USB interrupt flag
#define x8_USB_INT_ST	(*(volatile USB_INT_ST_t*)		0x40008007)	// USB interrupt status
#define x8_USB_RX_LEN	(*(volatile USB_RX_LEN_t*)		0x40008008)	// USB receiving length
/*-----0x40008009-B is RSVD-----*/
#define x8_UEP4_1_MOD	(*(volatile UEP4_1_MOD_t*)		0x4000800C)	// endpoint 4/1 mode
#define x8_UEP2_3_MOD	(*(volatile UEP2_3_MOD_t*)		0x4000800D)	// endpoint 2/3 mode
#define x8_UH_EP_MOD	(*(volatile UH_EP_MOD_t*)		0x4000800D)	// host endpoint mode
#define x8_UEP567_MOD	(*(volatile UEP567_MOD_t*)		0x4000800E)	// endpoint 5/6/7 mode
/*-----0x4000800F is RSVD-----*/
#define x16_UEP0_DMA	(*(volatile UEPn_DMA_t*)		0x40008010)	// endpoint 0 DMA buffer address
#define x16_UEP1_DMA	(*(volatile UEPn_DMA_t*)		0x40008014)	// endpoint 1 DMA buffer address
#define x16_UEP2_DMA	(*(volatile UEPn_DMA_t*)		0x40008018)	// endpoint 2 DMA buffer address
#define x16_UH_RX_DMA	(*(volatile UH_XX_DMA_t*)		0x40008018)	// host rx endpoint buffer address
#define x16_UEP3_DMA	(*(volatile UEPn_DMA_t*)		0x4000801C)	// endpoint 3 DMA buffer address
#define x16_UH_TX_DMA	(*(volatile UH_XX_DMA_t*)		0x4000801C)	// host tx endpoint buffer address
#define x8_UEP0_T_LEN	(*(volatile UEPn_T_LEN_t*)		0x40008020)	// endpoint 0 transmittal length
#define x8_UEP0_CTRL	(*(volatile UEPn_CTRL_t*)		0x40008022)	// endpoint 0 control
#define x8_UEP1_T_LEN	(*(volatile UEPn_T_LEN_t*)		0x40008024)	// endpoint 1 transmittal length
#define x8_UEP1_CTRL	(*(volatile UEPn_CTRL_t*)		0x40008026)	// endpoint 1 control
#define x8_UEP2_T_LEN	(*(volatile UEPn_T_LEN_t*)		0x40008028)	// endpoint 2 transmittal length
#define x8_UEP2_CTRL	(*(volatile UEPn_CTRL_t*)		0x4000802A)	// endpoint 2 control
#define x8_UEP3_T_LEN	(*(volatile UEPn_T_LEN_t*)		0x4000802C)	// endpoint 3 transmittal length
#define x8_UEP3_CTRL	(*(volatile UEPn_CTRL_t*)		0x4000802E)	// endpoint 3 control
#define x8_UEP4_T_LEN	(*(volatile UEPn_T_LEN_t*)		0x40008030)	// endpoint 4 transmittal length
#define x8_UEP4_CTRL	(*(volatile UEPn_CTRL_t*)		0x40008032)	// endpoint 4 control
#define x16_UEP5_DMA	(*(volatile UEPn_DMA_t*)		0x40008054)	// endpoint 5 DMA buffer address
#define x16_UEP6_DMA	(*(volatile UEPn_DMA_t*)		0x40008058)	// endpoint 6 DMA buffer address
#define x16_UEP7_DMA	(*(volatile UEPn_DMA_t*)		0x4000805C)	// endpoint 7 DMA buffer address
#define x8_UEP5_T_LEN	(*(volatile UEPn_T_LEN_t*)		0x40008064)	// endpoint 5 transmittal length
#define x8_UEP5_CTRL	(*(volatile UEPn_CTRL_t*)		0x40008066)	// endpoint 5 control
#define x8_UEP6_T_LEN	(*(volatile UEPn_T_LEN_t*)		0x40008068)	// endpoint 6 transmittal length
#define x8_UEP6_CTRL	(*(volatile UEPn_CTRL_t*)		0x4000806A)	// endpoint 6 control
#define x8_UEP7_T_LEN	(*(volatile UEPn_T_LEN_t*)		0x4000806C)	// endpoint 7 transmittal length
#define x8_UEP7_CTRL	(*(volatile UEPn_CTRL_t*)		0x4000806E)	// endpoint 7 control
//
// USB2
//
#define USB2		(*(volatile USB_Module_t*)	 0x40008400)
#define x8_USB2_CTRL	(*(volatile USB_CTRL_t*)		0x40008400)	// USB base control
#define x8_U2DEV_CTRL	(*(volatile UDEV_CTRL_t*)		0x40008401)	// USB device physical prot control
#define x8_U2HOST_CTRL	(*(volatile UHOST_CTRL_t*)		0x40008401)	// USB host physical prot control
#define x8_USB2_INT_EN	(*(volatile USB_INT_EN_t*)		0x40008402)	// USB interrupt enable
#define x8_USB2_DEV_AD	(*(volatile USB_DEV_AD_t*)		0x40008403)	// USB device address
/*-----0x40008404 is RSVD-----*/
#define x8_USB2_MIS_ST	(*(volatile USB_MIS_ST_t*)		0x40008405)	// USB miscellaneous status
#define x8_USB2_INT_FG	(*(volatile USB_INT_FG_t*)		0x40008406)	// USB interrupt flag
#define x8_USB2_INT_ST	(*(volatile USB_INT_ST_t*)		0x40008407)	// USB interrupt status
#define x8_USB2_RX_LEN	(*(volatile USB_RX_LEN_t*)		0x40008408)	// USB receiving length
/*-----0x40008409-B is RSVD-----*/
#define x8_U2EP4_1_MOD	(*(volatile UEP4_1_MOD_t*)		0x4000840C)	// endpoint 4/1 mode
#define x8_U2EP2_3_MOD	(*(volatile UEP2_3_MOD_t*)		0x4000840D)	// endpoint 2/3 mode
#define x8_U2H_EP_MOD	(*(volatile UH_EP_MOD_t*)		0x4000840D)	// host endpoint mode
#define x8_U2EP567_MOD	(*(volatile UEP567_MOD_t*)		0x4000840E)	// endpoint 5/6/7 mode
/*-----0x4000840F is RSVD-----*/
#define x16_U2EP0_DMA	(*(volatile UEPn_DMA_t*)		0x40008410)	// endpoint 0 DMA buffer address
#define x16_U2EP1_DMA	(*(volatile UEPn_DMA_t*)		0x40008414)	// endpoint 1 DMA buffer address
#define x16_U2EP2_DMA	(*(volatile UEPn_DMA_t*)		0x40008418)	// endpoint 2 DMA buffer address
#define x16_U2H_RX_DMA	(*(volatile UH_XX_DMA_t*)		0x40008418)	// host rx endpoint buffer address
#define x16_U2EP3_DMA	(*(volatile UEPn_DMA_t*)		0x4000841C)	// endpoint 3 DMA buffer address
#define x16_U2H_TX_DMA	(*(volatile UH_XX_DMA_t*)		0x4000841C)	// host tx endpoint buffer address
#define x8_U2EP0_T_LEN	(*(volatile UEPn_T_LEN_t*)		0x40008420)	// endpoint 0 transmittal length
#define x8_U2EP0_CTRL	(*(volatile UEPn_CTRL_t*)		0x40008422)	// endpoint 0 control
#define x8_U2EP1_T_LEN	(*(volatile UEPn_T_LEN_t*)		0x40008424)	// endpoint 1 transmittal length
#define x8_U2EP1_CTRL	(*(volatile UEPn_CTRL_t*)		0x40008426)	// endpoint 1 control
#define x8_U2EP2_T_LEN	(*(volatile UEPn_T_LEN_t*)		0x40008428)	// endpoint 2 transmittal length
#define x8_U2EP2_CTRL	(*(volatile UEPn_CTRL_t*)		0x4000842A)	// endpoint 2 control
#define x8_U2EP3_T_LEN	(*(volatile UEPn_T_LEN_t*)		0x4000842C)	// endpoint 3 transmittal length
#define x8_U2EP3_CTRL	(*(volatile UEPn_CTRL_t*)		0x4000842E)	// endpoint 3 control
#define x8_U2EP4_T_LEN	(*(volatile UEPn_T_LEN_t*)		0x40008430)	// endpoint 4 transmittal length
#define x8_U2EP4_CTRL	(*(volatile UEPn_CTRL_t*)		0x40008432)	// endpoint 4 control
#define x16_U2EP5_DMA	(*(volatile UEPn_DMA_t*)		0x40008454)	// endpoint 5 DMA buffer address
#define x16_U2EP6_DMA	(*(volatile UEPn_DMA_t*)		0x40008458)	// endpoint 6 DMA buffer address
#define x16_U2EP7_DMA	(*(volatile UEPn_DMA_t*)		0x4000845C)	// endpoint 7 DMA buffer address
#define x8_U2EP5_T_LEN	(*(volatile UEPn_T_LEN_t*)		0x40008464)	// endpoint 5 transmittal length
#define x8_U2EP5_CTRL	(*(volatile UEPn_CTRL_t*)		0x40008466)	// endpoint 5 control
#define x8_U2EP6_T_LEN	(*(volatile UEPn_T_LEN_t*)		0x40008468)	// endpoint 6 transmittal length
#define x8_U2EP6_CTRL	(*(volatile UEPn_CTRL_t*)		0x4000846A)	// endpoint 6 control
#define x8_U2EP7_T_LEN	(*(volatile UEPn_T_LEN_t*)		0x4000846C)	// endpoint 7 transmittal length
#define x8_U2EP7_CTRL	(*(volatile UEPn_CTRL_t*)		0x4000846E)	// endpoint 7 control

#endif // !__CH58xUSBSFR__

