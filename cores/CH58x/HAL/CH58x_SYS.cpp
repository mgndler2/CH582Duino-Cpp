/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH58x_SYS.c
 * Author             : WCH
 * Version            : V1.2
 * Date               : 2021/11/17
 * Description
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/
#pragma G++ optimize ("O0")
#include "CH58x_SYS.h"
#include "CH58x_CLK.h"
#include "Arduino.h"
CLK_Source CPU_CLK;

volatile uint32_t IRQ_STA = 0;


void CLK_Source::SetSysClock(ns_SYS::HCLK_CLKSOURCE source) {
	uint8_t C32K = TUNE32K.CK32K_CONFIG.byte;
	sys_safe_access_enable();
	MISCCtrl.PLL_CONFIG.byte &= ~(1 << 5);
	TUNE32K.CK32K_CONFIG.CLK_INT32K_PON = 1;
	TUNE32K.CK32K_CONFIG.CLK_OSC32K_XT = 0;
	sys_safe_access_disable();
	_nop(); _nop();

	sys_safe_access_enable();
	SySClock.CLK_SYS_CFG.CLK_SYS_MOD = 0b11;
	_nop(); _nop(); _nop(); _nop();
	sys_safe_access_disable();
	for (int i = 0; i < 120; i++)
	{
		//_nop();_nop();
	}

	if ((source & 0xC0) != 0xC0) {
		if (SySClock.HFCK_PWR_CTRL.CLK_XT32M_PON == 0) {
			sys_safe_access_enable();
			//TUNE32M.XT32M_TUNE.XT32M_C_LOAD = 7;
			//TUNE32M.XT32M_TUNE.XT32M_I_BIAS = 3;
			SySClock.HFCK_PWR_CTRL.CLK_XT32M_PON = 1;
			sys_safe_access_disable();
			for (int i = 0; i < 1200; i++)
			{
				_nop();_nop();
			}
		}
		if ((source & 0x40) == 0x40 && SySClock.HFCK_PWR_CTRL.CLK_PLL_PON == 0) {
			sys_safe_access_enable();
			SySClock.HFCK_PWR_CTRL.CLK_PLL_PON = 1;
			sys_safe_access_disable();
			for (int i = 0; i < 2000; i++)
			{
				_nop();_nop();
			}

		}

		sys_safe_access_enable();
		x32_FLASH_CONTROL.FLASH_CFG = 0x57;
		SySClock.CLK_SYS_CFG.CLK_SOURCE = source;//		
		_nop();_nop();_nop();_nop();
		sys_safe_access_disable();
		uint8_t CLK_Mode = SySClock.CLK_SYS_CFG.CLK_SYS_MOD;

		sys_safe_access_enable();
		if (CLK_Mode == 0b01) {//PLL
			if (source == ns_SYS::CLK_SOURCE_PLL_80MHz) {
				x32_FLASH_CONTROL.FLASH_CFG = 0X01;
			}
			else {
				x32_FLASH_CONTROL.FLASH_CFG = 0X02;
			}
		}
		else if (CLK_Mode == 0b00 || CLK_Mode == 0b10) {//HSE
			x32_FLASH_CONTROL.FLASH_CFG = 0x57;
			
		}
		sys_safe_access_disable();

	}
	else {

	}

	sys_safe_access_enable();
	//ISCCtrl.PLL_CONFIG.FLASH_IO_MOD = 1;
	//x8_PLL_CONFIG.byte |= (1 << 7);
	x8_PLL_CONFIG.byte = 0b11001010;
	sys_safe_access_disable();
	_f_cpu = GetSysClock();
}

uint32_t CLK_Source::GetSysClock() {
	uint8_t CLK_Mode = SySClock.CLK_SYS_CFG.CLK_SYS_MOD;
	uint8_t CLK_Div = SySClock.CLK_SYS_CFG.CLK_PLL_DIV;
	if (CLK_Mode == 0b00 || CLK_Mode == 0b10) {
		if (CLK_Div != 0) {
			return (32000000 / CLK_Div);
		}
		return 1000000;
	}
	else if (CLK_Mode == 0b01) {
		if (CLK_Div != 0) {
			return (480000000 / CLK_Div);
		}
		return 15000000;
	}
	else {
		return 32000;
	}
}

/*********************************************************************
 * @fn      SYS_GetInfoSta
 *
 * @brief   获取当前系统信息状态
 *
 * @param   i       - refer to SYS_InfoStaTypeDef
 *
 * @return  是否开启
 */

uint8_t SYS_GetInfoSta(SYS_InfoStaTypeDef i)
{
	if (i == STA_SAFEACC_ACT)
	{
		return (R8_SAFE_ACCESS_SIG & RB_SAFE_ACC_ACT);
	}
	else
	{
		return (R8_GLOB_CFG_INFO & (1 << i));
	}
}

/*********************************************************************
 * @fn      SYS_ResetExecute
 *
 * @brief   执行系统软件复位
 *
 * @param   none
 *
 * @return  none
 */
__HIGH_CODE
void SYS_ResetExecute(void)
{
	FLASH_ROM_SW_RESET();
	sys_safe_access_enable();
	R8_RST_WDOG_CTRL |= RB_SOFTWARE_RESET;
	sys_safe_access_disable();
}

/*********************************************************************
 * @fn      SYS_DisableAllIrq
 *
 * @brief   关闭所有中断，并保留当前中断值
 *
 * @param   pirqv   - 当前保留中断值
 *
 * @return  none
 */
void SYS_DisableAllIrq(uint32_t* pirqv)
{
	*pirqv = (PFIC->ISR[0] >> 8) | (PFIC->ISR[1] << 24);
	PFIC->IRER[0] = 0xffffffff;
	PFIC->IRER[1] = 0xffffffff;
	asm volatile("fence.i");
}

/*********************************************************************
 * @fn      SYS_RecoverIrq
 *
 * @brief   恢复之前关闭的中断值
 *
 * @param   irq_status  - 当前保留中断值
 *
 * @return  none
 */
void SYS_RecoverIrq(uint32_t irq_status)
{
	PFIC->IENR[0] = (irq_status << 8);
	PFIC->IENR[1] = (irq_status >> 24);
}

/*********************************************************************
 * @fn      SYS_GetSysTickCnt
 *
 * @brief   获取当前系统(SYSTICK)计数值
 *
 * @param   none
 *
 * @return  当前计数值
 */
uint32_t SYS_GetSysTickCnt(void)
{
	uint32_t val;

	val = SysTick->CNT;
	return (val);
}

/*********************************************************************
 * @fn      WWDG_ITCfg
 *
 * @brief   看门狗定时器溢出中断使能
 *
 * @param   s       - 溢出是否中断
 *
 * @return  none
 */
void WWDG_ITCfg(FunctionalState s)
{
	uint8_t ctrl = R8_RST_WDOG_CTRL;

	if (s == DISABLE)
	{
		ctrl &= ~RB_WDOG_INT_EN;
	}
	else
	{
		ctrl |= RB_WDOG_INT_EN;
	}

	sys_safe_access_enable();
	R8_RST_WDOG_CTRL = ctrl;
	sys_safe_access_disable();
}

/*********************************************************************
 * @fn      WWDG_ResetCfg
 *
 * @brief   看门狗定时器复位功能
 *
 * @param   s       - 溢出是否复位
 *
 * @return  none
 */
void WWDG_ResetCfg(FunctionalState s)
{
	uint8_t ctrl = R8_RST_WDOG_CTRL;

	if (s == DISABLE)
	{
		ctrl &= ~RB_WDOG_RST_EN;
	}
	else
	{
		ctrl |= RB_WDOG_RST_EN;
	}

	sys_safe_access_enable();
	R8_RST_WDOG_CTRL = ctrl;
	sys_safe_access_disable();
}

/*********************************************************************
 * @fn      WWDG_ClearFlag
 *
 * @brief   清除看门狗中断标志，重新加载计数值也可清除
 *
 * @param   none
 *
 * @return  none
 */
void WWDG_ClearFlag(void)
{
	sys_safe_access_enable();
	R8_RST_WDOG_CTRL |= RB_WDOG_INT_FLAG;
	sys_safe_access_disable();
}

/*********************************************************************
 * @fn      HardFault_Handler
 *
 * @brief   硬件错误中断，进入后执行复位，复位类型为上电复位
 *
 * @param   none
 *
 * @return  none
 */
__INTERRUPT
__HIGH_CODE
__attribute__((weak))
void HardFault_Handler(void)
{
	FLASH_ROM_SW_RESET();
	sys_safe_access_enable();
	R16_INT32K_TUNE = 0xFFFF;
	sys_safe_access_disable();
	sys_safe_access_enable();
	R8_RST_WDOG_CTRL |= RB_SOFTWARE_RESET;
	sys_safe_access_disable();
	while (1);
}