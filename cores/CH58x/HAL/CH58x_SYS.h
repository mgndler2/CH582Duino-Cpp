/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH57x_SYS.h
 * Author             : WCH
 * Version            : V1.2
 * Date               : 2021/11/17
 * Description
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#ifndef __CH58x_SYS_H__
#define __CH58x_SYS_H__
#include "CH58x_SYSCTRL_SFR.h"
#include "CH58x_CLK_SFR.h"
#include "core_riscv.h"
#include "ISP583.h"

#ifdef __cplusplus
extern "C" {
#endif
	namespace ns_SYS {
		typedef enum {
			CLK_SOURCE_HSE_1MHz = (0x80 | 0),
			CLK_SOURCE_HSE_2MHz = (0x80 | 16),
			CLK_SOURCE_HSE_4MHz = (0x80 | 8),
			CLK_SOURCE_HSE_8MHz = (0x80 | 4),
			CLK_SOURCE_HSE_16MHz = (0x80 | 2),

			CLK_SOURCE_PLL_15MHz = (0x40 | 0),
			CLK_SOURCE_PLL_20MHz = (0x40 | 24),
			CLK_SOURCE_PLL_19M2Hz = (0x40 | 25),
			CLK_SOURCE_PLL_24MHz = (0x40 | 20),
			CLK_SOURCE_PLL_30MHz = (0x40 | 16),
			CLK_SOURCE_PLL_32MHz = (0x40 | 15),
			CLK_SOURCE_PLL_40MHz = (0x40 | 12),
			CLK_SOURCE_PLL_48MHz = (0x40 | 10),
			CLK_SOURCE_PLL_60MHz = (0x40 | 8),
			CLK_SOURCE_PLL_80MHz = (0x40 | 6),

			CLK_SOURCE_LSI = (0xC0 | 0),
			CLK_SOURCE_LSE = (0xC0 | 1),
		}HCLK_CLKSOURCE;
		typedef enum {
			LSI_RC32K = 0,
			LSE_XT32K
		}LCLK_CLKSOURCE;
	}

	extern volatile uint32_t IRQ_STA;

	__Allways_INLINE static inline void sys_safe_access_enable(void)
	{
		//if (read_csr(0x800) & 0x08)
		//{
		//	IRQ_STA = read_csr(0x800);
		//	write_csr(0x800, (IRQ_STA & (~0x08)));
		//}
		_nop();_nop();
		x8_SAFE_ACCESS_SIG.byte = 0x57;
		x8_SAFE_ACCESS_SIG.byte = 0xA8;
		_nop();_nop();
	}

	__Allways_INLINE static inline void sys_safe_access_disable(void)
	{
		x8_SAFE_ACCESS_SIG.byte = 0;
		//write_csr(0x800, read_csr(0x800) | (IRQ_STA & 0x08));
		//IRQ_STA = 0;
	}

	/**
	 * @brief  rtc interrupt event define
	 */
	typedef enum
	{
		RST_STATUS_SW = 0, // 软件复位
		RST_STATUS_RPOR,   // 上电复位
		RST_STATUS_WTR,    // 看门狗超时复位
		RST_STATUS_MR,     // 外部手动复位
		RST_STATUS_LRM0,   // 唤醒复位-软复位引起
		RST_STATUS_GPWSM,  // 下电模式唤醒复位
		RST_STATUS_LRM1,   //	唤醒复位-看门狗引起
		RST_STATUS_LRM2,   //	唤醒复位-手动复位引起

	} SYS_ResetStaTypeDef;

	/**
	 * @brief  rtc interrupt event define
	 */
	typedef enum
	{
		INFO_ROM_READ = 0, // FlashROM 代码和数据区 是否可读
		INFO_RESET_EN = 2, // RST#外部手动复位输入功能是否开启
		INFO_BOOT_EN,      // 系统引导程序 BootLoader 是否开启
		INFO_DEBUG_EN,     // 系统仿真调试接口是否开启
		INFO_LOADER,       // 当前系统是否处于Bootloader 区
		STA_SAFEACC_ACT,   // 当前系统是否处于安全访问状态，否则RWA属性区域不可访问

	} SYS_InfoStaTypeDef;

#define SYS_GetChipID()      R8_CHIP_ID
#define SYS_GetAccessID()    R8_SAFE_ACCESS_ID
	uint8_t SYS_GetInfoSta(SYS_InfoStaTypeDef i);
#define SYS_GetLastResetSta()    (R8_RESET_STATUS & RB_RESET_FLAG)
	void SYS_ResetExecute(void);
#define SYS_ResetKeepBuf(d)    (R8_GLOB_RESET_KEEP = d)
	void SYS_DisableAllIrq(uint32_t* pirqv);
	void SYS_RecoverIrq(uint32_t irq_status);
	uint32_t SYS_GetSysTickCnt(void);
#define WWDG_SetCounter(c)    (R8_WDOG_COUNT = c)
	void WWDG_ITCfg(FunctionalState s);
	void WWDG_ResetCfg(FunctionalState s);
#define WWDG_GetFlowFlag()    (R8_RST_WDOG_CTRL & RB_WDOG_INT_FLAG)
	void WWDG_ClearFlag(void);

#ifdef __cplusplus
}
#endif

class CLK_Source {
public:
	CLK_Source(){}
	void SetSysClock(ns_SYS::HCLK_CLKSOURCE source);
	uint32_t GetSysClock();
private:
	uint32_t _f_cpu = 6400000UL;
};
extern CLK_Source CPU_CLK;



extern volatile uint32_t IRQ_STA;
#endif // !__CH58x_SYS_H__