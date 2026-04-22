#pragma once

#ifndef __CH58xUARTSFR__
#define __CH58xUARTSFR__

#include "CH58x_SFR_TOP_LVL.h" 
typedef union UART_MCR {
	 struct {
		  uint8_t MCR_DTR : 1;
		  uint8_t MCR_RTS : 1;
		  uint8_t : 1;
		  uint8_t MCR_INT_OE : 1;
		  uint8_t MCR_LOOP : 1;
		  uint8_t MCR_AU_FLOW_EN : 1;
		  uint8_t MCR_TNOW : 1;
		  uint8_t MCR_HALF : 1;
	 };
	 struct {
		  uint8_t : 2;
		  uint8_t MCR_OUT : 2;
		  uint8_t : 4;
	 };
	 uint8_t byte;
}UART_MCR_t;			//0x00
typedef union UART_IER {
	 struct {
		  uint8_t IER_RECV_RDY : 1;
		  uint8_t IER_THR_EMPTY : 1;
		  uint8_t IER_LINE_STAT : 1;
		  uint8_t IER_MODEM_CHG : 1;
		  uint8_t IER_DTR_EN : 1;
		  uint8_t IER_RTS_EN : 1;
		  uint8_t IER_TXD_EN : 1;
		  uint8_t IER_RESET : 1;
	 };
	 uint8_t byte;
}UART_IER_t;			//0x01
typedef union UART_FCR {
	 struct {
		  uint8_t FCR_FIFO_EN : 1;
		  uint8_t FCR_RX_FIFO_CLR : 1;
		  uint8_t FCR_TX_FIFO_CLR : 1;
		  uint8_t : 3;
		  uint8_t FCR_FIFO_TRIG : 2;
	 };
	 uint8_t byte;
}UART_FCR_t;			//0x02
typedef union UART_LCR {
	 struct {
		  uint8_t LCR_WORD_SZ : 2;
		  uint8_t LCR_STOP_BIT : 1;
		  uint8_t LCR_PAR_EN : 1;
		  uint8_t LCR_PAR_MOD : 2;
		  uint8_t LCR_BREAK_EN : 1;
		  uint8_t LCR_DLAB : 1;
	 };
	 uint8_t byte;
}UART_LCR_t;			//0x03
typedef union UART_IIR {
	 struct {
		  uint8_t IIR_NO_INT : 1;
		  uint8_t IIR_ID : 3;
		  uint8_t : 2;
		  uint8_t IIR_FIFO_ID : 2;
	 };
	 struct {
		  uint8_t IIR_INT_MASK : 4;
		  uint8_t : 4;
	 };
	 uint8_t byte;
}UART_IIR_t;			//0x04
typedef union UART_LSR {
	 struct {
		  uint8_t LSR_DATA_RDY : 1;
		  uint8_t LSR_OVER_ERR : 1;
		  uint8_t LSR_PAR_ERR : 1;
		  uint8_t LSR_FRAME_ERR : 1;
		  uint8_t LSR_BREAK_ERR : 1;
		  uint8_t LSR_TX_FIFO_EMP : 1;
		  uint8_t LSR_TX_ALL_EMP : 1;
		  uint8_t LSR_ERR_RX_FIFO : 1;
	 };
	 uint8_t byte;
}UART_LSR_t;			//0x05
typedef union UART_MSR {
	 struct {
		  uint8_t MSR_CTS_CHG : 1;
		  uint8_t MSR_DSR_CHG : 1;
		  uint8_t MSR_RI_CHG : 1;
		  uint8_t MSR_DCD_CHG : 1;
		  uint8_t MSR_CTS : 1;
		  uint8_t MSR_DSR : 1;
		  uint8_t MSR_RI : 1;
		  uint8_t MSR_DCD : 1;
	 };
	 uint8_t byte;
}UART_MSR_t;			//0x06
typedef union UART_RBR {
	 uint8_t RBR;
}UART_RBR_t;			//0x08
typedef union UART_THR {
	 uint8_t THR;
}UART_THR_t;			//0x08
typedef union UART_RFC {
	 uint8_t RFC;
}UART_RFC_t;			//0x0A
typedef union UART_TFC {
	 uint8_t TFC;
}UART_TFC_t;			//0x0B
typedef union UART_DL {
	 uint16_t DL;
}UART_DL_t;				//0x0C
typedef union UART_DIV {
	 uint8_t DIV;
}UART_DIV_t;			//0x0E
typedef union UART_ADR {
	 uint8_t ADR;
}UART_ADR_t;			//0x0F

typedef struct UART_Module {
	UART_MCR_t	MCR;		//0x00
	UART_IER_t	IER;		//0x01
	UART_FCR_t	FCR;		//0x02
	UART_LCR_t	LCR;		//0x03//
	UART_IIR_t	IIR;		//0x04
	UART_LSR_t	LSR;		//0x05
	UART_MSR_t	MSR;		//0x06
	uint8_t : 8;			//0x07//
	union {					//0x08
		UART_RBR_t	RBR;
		UART_THR_t	THR;
	};
	uint8_t : 8;			//0x09
	UART_RFC_t	RFC;		//0x0A
	UART_TFC_t	TFC;		//0x0B//
	UART_DL_t	DL;			//0x0C-0D
	UART_DIV_t	DIV;		//0x0E
	UART_ADR_t	ADR;		//0x0F//
}UART_Module_t;
//
// UART0
//
#define UART0		  	(*(volatile UART_Module_t*)	  	0x40003000)
#define x8_UART0_MCR	(*(volatile UART_MCR_t*)	0x40003000)
#define x8_UART0_IER	(*(volatile UART_IER_t*)	0x40003001)
#define x8_UART0_FCR	(*(volatile UART_FCR_t*)	0x40003002)
#define x8_UART0_LCR	(*(volatile UART_LCR_t*)	0x40003003)
#define x8_UART0_IIR	(*(volatile UART_IIR_t*)	0x40003004)
#define x8_UART0_LSR	(*(volatile UART_LSR_t*)	0x40003005)
#define x8_UART0_MSR	(*(volatile UART_MSR_t*)	0x40003006)
/*-----0x40003007 is RSVD-----*/
#define x8_UART0_RBR	(*(volatile UART_RBR_t*)	0x40003008)
#define x8_UART0_THR	(*(volatile UART_THR_t*)	0x40003008)
/*-----0x40003009 is RSVD-----*/
#define x8_UART0_RFC	(*(volatile UART_RFC_t*)	0x4000300A)
#define x8_UART0_TFC	(*(volatile UART_TFC_t*)	0x4000300B)
#define x16_UART0_DL	(*(volatile UART_DL_t*)		0x4000300C)
#define x8_UART0_DIV	(*(volatile UART_DIV_t*)	0x4000300E)
#define x8_UART0_ADR	(*(volatile UART_ADR_t*)	0x4000300F)
//
// UART1
//
#define UART1			(*(volatile UART_Module_t*)	  	0x40003400)
#define x8_UART1_MCR	(*(volatile UART_MCR_t*)	0x40003400)
#define x8_UART1_IER	(*(volatile UART_IER_t*)	0x40003401)
#define x8_UART1_FCR	(*(volatile UART_FCR_t*)	0x40003402)
#define x8_UART1_LCR	(*(volatile UART_LCR_t*)	0x40003403)
#define x8_UART1_IIR	(*(volatile UART_IIR_t*)	0x40003404)
#define x8_UART1_LSR	(*(volatile UART_LSR_t*)	0x40003405)
#define x8_UART1_MSR	(*(volatile UART_MSR_t*)	0x40003406)
/*-----0x40003407 is RSVD-----*/
#define x8_UART1_RBR	(*(volatile UART_RBR_t*)	0x40003408)
#define x8_UART1_THR	(*(volatile UART_THR_t*)	0x40003408)
/*-----0x40003409 is RSVD-----*/
#define x8_UART1_RFC	(*(volatile UART_RFC_t*)	0x4000340A)
#define x8_UART1_TFC	(*(volatile UART_TFC_t*)	0x4000340B)
#define x16_UART1_DL	(*(volatile UART_DL_t*)		0x4000340C)
#define x8_UART1_DIV	(*(volatile UART_DIV_t*)	0x4000340E)
/*-----0x4000340F is RSVD-----*/
//
// UART2
//
#define UART2		  	(*(volatile UART_Module_t*)		0x40003800)
#define x8_UART2_MCR	(*(volatile UART_MCR_t*)	0x40003800)
#define x8_UART2_IER	(*(volatile UART_IER_t*)	0x40003801)
#define x8_UART2_FCR	(*(volatile UART_FCR_t*)	0x40003802)
#define x8_UART2_LCR	(*(volatile UART_LCR_t*)	0x40003803)
#define x8_UART2_IIR	(*(volatile UART_IIR_t*)	0x40003804)
#define x8_UART2_LSR	(*(volatile UART_LSR_t*)	0x40003805)
#define x8_UART2_MSR	(*(volatile UART_MSR_t*)	0x40003806)
/*-----0x40003807 is RSVD-----*/
#define x8_UART2_RBR	(*(volatile UART_RBR_t*)	0x40003808)
#define x8_UART2_THR	(*(volatile UART_THR_t*)	0x40003808)
/*-----0x40003809 is RSVD-----*/
#define x8_UART2_RFC	(*(volatile UART_RFC_t*)	0x4000380A)
#define x8_UART2_TFC	(*(volatile UART_TFC_t*)	0x4000380B)
#define x16_UART2_DL	(*(volatile UART_DL_t*)		0x4000380C)
#define x8_UART2_DIV	(*(volatile UART_DIV_t*)	0x4000380E)
/*-----0x4000380F is RSVD-----*/
//
// UART3
//
#define UART3		  	(*(volatile UART_t*)		0x40003C00)
#define x8_UART3_MCR	(*(volatile UART_MCR_t*)	0x40003C00)
#define x8_UART3_IER	(*(volatile UART_IER_t*)	0x40003C01)
#define x8_UART3_FCR	(*(volatile UART_FCR_t*)	0x40003C02)
#define x8_UART3_LCR	(*(volatile UART_LCR_t*)	0x40003C03)
#define x8_UART3_IIR	(*(volatile UART_IIR_t*)	0x40003C04)
#define x8_UART3_LSR	(*(volatile UART_LSR_t*)	0x40003C05)
#define x8_UART3_MSR	(*(volatile UART_MSR_t*)	0x40003C06)
/*-----0x40003C07 is RSVD-----*/
#define x8_UART3_RBR	(*(volatile UART_RBR_t*)	0x40003C08)
#define x8_UART3_THR	(*(volatile UART_THR_t*)	0x40003C08)
/*-----0x40003C09 is RSVD-----*/
#define x8_UART3_RFC	(*(volatile UART_RFC_t*)	0x40003C0A)
#define x8_UART3_TFC	(*(volatile UART_TFC_t*)	0x40003C0B)
#define x16_UART3_DL	(*(volatile UART_DL_t*)		0x40003C0C)
#define x8_UART3_DIV	(*(volatile UART_DIV_t*)	0x40003C0E)
/*-----0x40003C0F is RSVD-----*/

#endif // !__CH58xUARTSFR__