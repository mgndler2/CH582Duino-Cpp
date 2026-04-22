#pragma once

#ifndef __CH58xSYSCTRLSFR__
#define __CH58xSYSCTRLSFR__
#include "CH58x_SFR_TOP_LVL.h"

typedef union SAFE_ACCESS_SIG {
	 struct {
		  uint8_t SAFE_ACC_MODE : 2;
		  uint8_t : 1;
		  uint8_t SAFE_ACC_ACT : 1;
		  uint8_t SAFE_ACC_TIMER : 3;
		  uint8_t : 1;
	 };
	 struct {
		  uint8_t SAFE_ACCESS;
	 };
	 uint8_t byte;
}SAFE_ACCESS_SIG_t;
typedef union CHIP_ID {
	 struct {
		  uint8_t ID;
	 };	 
}CHIP_ID_t;
typedef union SAFE_ACCESS_ID {
	 struct {
		  uint8_t ID;
	 };
}SAFE_ACCESS_ID_t;
typedef union WDOG_COUNT {
	 struct {
		  uint8_t COUNT;
	 };
}WDOG_COUNT_t;
typedef union RESET_STATUS {
	 struct {
		  uint8_t RESET_FLAG : 3;
		  uint8_t : 5;
	 };
	 uint8_t byte;
}RESET_STATUS_t;
typedef union GLOB_ROM_CFG {
	 struct {
		  uint8_t : 4;
		  uint8_t ROM_CODE_OFS : 1;
		  uint8_t ROM_CTRL_EN : 1;
		  uint8_t ROM_DATA_WE : 1;
		  uint8_t ROM_CODE_WE : 1;
	 };
	 uint8_t byte;
}GLOB_ROM_CFG_t;
typedef union GLOB_CFG_INFO {
	 struct {
		  uint8_t CFG_ROM_READ : 1;
		  uint8_t : 1;
		  uint8_t CFG_RESET_EN : 1;
		  uint8_t CFG_BOOT_EN : 1;
		  uint8_t CFG_DEBUG_EN : 1;
		  uint8_t BOOT_LOADER : 1;
		  uint8_t : 2;
	 };
	 uint8_t byte;
}GLOB_CFG_INFO_t;
typedef union RST_WDOG_CTRL {
	 struct {
		  uint8_t SOFTWARE_RESET : 1;		  
		  uint8_t WDOG_RST_EN : 1;
		  uint8_t WDOG_INT_EN : 1;
		  uint8_t : 1;
		  uint8_t WDOG_INT_FLAG : 1;
		  uint8_t : 3;
	 };
	 uint8_t byte;
}RST_WDOG_CTRL_t;
typedef union GLOB_RESET_KEEP {
	 struct {
		  uint8_t DATA;
	 };
}GLOB_RESET_KEEP_t;

typedef union FLASH_DATA {
	uint32_t pad;
}FLASH_DATA_t;

typedef union FLASH_CONTROL {
	struct {
		uint8_t FLASH_DATA;
		uint8_t : 8;
		uint8_t FLASH_CTRL;
		uint8_t FLASH_CFG;
	};
	uint32_t pad;
}FLASH_CONTROL_t;


typedef struct SYS_CTRL {
	SAFE_ACCESS_SIG_t	SAFE_ACCESS_SIG;	//0x40
	CHIP_ID_t			CHIP_ID;			//0x41
	SAFE_ACCESS_ID_t	SAFE_ACCESS_ID;		//0x42
	WDOG_COUNT_t		WDOG_COUNT;			//0x43//
	union {									//0x44
		RESET_STATUS_t		RESET_STATUS;
		GLOB_ROM_CFG_t		GLOB_ROM_CFG;
	};
	GLOB_CFG_INFO_t		GLOB_CFG_INFO;		//0x45
	RST_WDOG_CTRL_t		RST_WDOG_CTRL;		//0x46
	GLOB_RESET_KEEP_t	GLOB_RESET_KEEP;	//0x47//
}SYS_CTRL_t;
#define SySCtrl			(*(volatile SYS_CTRL_t*)		0x40001040)
#define x8_SAFE_ACCESS_SIG		(*(volatile SAFE_ACCESS_SIG_t*)		0x40001040)
#define x8_CHIP_ID				(*(volatile CHIP_ID_t*)				0x40001041)
#define x8_SAFE_ACCESS_ID		(*(volatile SAFE_ACCESS_ID_t*)		0x40001042)
#define x8_WDOG_COUNT			(*(volatile WDOG_COUNT_t*)			0x40001043)
#define x8_GLOB_ROM_CFG			(*(volatile GLOB_ROM_CFG_t*)		0x40001044)
#define x8_GLOB_CFG_INFO		(*(volatile GLOB_CFG_INFO_t*)		0x40001045)
#define x8_RST_WDOG_CTRL		(*(volatile RST_WDOG_CTRL_t*)		0x40001046)
#define x8_GLOB_RESET_KEEP		(*(volatile GLOB_RESET_KEEP_t*)		0x40001047)

#define x32_FLASH_DATA			(*(volatile FLASH_DATA_t*)			0x40001800)
#define x32_FLASH_CONTROL		(*(volatile FLASH_CONTROL_t*)		0x40001804)

#endif // !__CH58xSYSCTRLSFR__
