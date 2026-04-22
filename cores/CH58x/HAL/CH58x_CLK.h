/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH57x_clk.h
 * Author             : WCH
 * Version            : V1.2
 * Date               : 2021/11/17
 * Description
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#ifndef __CH58x_CLK_H__
#define __CH58x_CLK_H__
#include "CH58x_SYSCTRL_SFR.h"
#include "CH58x_CLK_SFR.h"

#ifdef __cplusplus
extern "C" {
#endif
    typedef enum
    {
        Clk32K_LSI = 0,
        Clk32K_LSE,

    } LClk32KTypeDef;

    typedef enum
    {
        HSE_RCur_75 = 0,
        HSE_RCur_100,
        HSE_RCur_125,
        HSE_RCur_150

    } HSECurrentTypeDef;

    typedef enum
    {
        HSECap_10p = 0,
        HSECap_12p,
        HSECap_14p,
        HSECap_16p,
        HSECap_18p,
        HSECap_20p,
        HSECap_22p,
        HSECap_24p

    } HSECapTypeDef;

    typedef enum
    {
        LSE_RCur_70 = 0,
        LSE_RCur_100,
        LSE_RCur_140,
        LSE_RCur_200

    } LSECurrentTypeDef;

    typedef enum
    {
        LSECap_2p = 0,
        LSECap_13p,
        LSECap_14p,
        LSECap_15p,
        LSECap_16p,
        LSECap_17p,
        LSECap_18p,
        LSECap_19p,
        LSECap_20p,
        LSECap_21p,
        LSECap_22p,
        LSECap_23p,
        LSECap_24p,
        LSECap_25p,
        LSECap_26p,
        LSECap_27p

    } LSECapTypeDef;

#define MAX_DAY                   0x00004000
#define MAX_2_SEC                 0x0000A8C0

#define BEGYEAR                   2020
#define IsLeapYear(yr)            (!((yr) % 400) || (((yr) % 100) && !((yr) % 4)))
#define YearLength(yr)            (IsLeapYear(yr) ? 366 : 365)
#define monthLength(lpyr, mon)    (((mon) == 1) ? (28 + (lpyr)) : (((mon) > 6) ? (((mon) & 1) ? 31 : 30) : (((mon) & 1) ? 30 : 31)))

    typedef enum
    {
        Period_0_125_S = 0, // 0.125s 周期
        Period_0_25_S,      // 0.25s 周期
        Period_0_5_S,       // 0.5s 周期
        Period_1_S,         // 1s 周期
        Period_2_S,         // 2s 周期
        Period_4_S,         // 4s 周期
        Period_8_S,         // 8s 周期
        Period_16_S,        // 16s 周期
    } RTC_TMRCycTypeDef;

    typedef enum
    {
        RTC_TRIG_EVENT = 0, // RTC 触发事件
        RTC_TMR_EVENT,      // RTC 周期定时事件

    } RTC_EVENTTypeDef;

    typedef enum
    {
        RTC_TRIG_MODE = 0, // RTC 触发模式
        RTC_TMR_MODE,      // RTC 周期定时模式

    } RTC_MODETypeDef;

    typedef enum
    {
        /* 校准精度越高，耗时越长 */
        Level_32 = 3, // 用时 1.2ms 1000ppm (32M 主频)  1100ppm (60M 主频)
        Level_64,     // 用时 2.2ms 800ppm  (32M 主频)  1000ppm (60M 主频)
        Level_128,    // 用时 4.2ms 600ppm  (32M 主频)  800ppm  (60M 主频)

    } Cali_LevelTypeDef;

void LClk32K_Select(LClk32KTypeDef hc);
void HSECFG_Current(HSECurrentTypeDef c);
void HSECFG_Capacitance(HSECapTypeDef c);
void LSECFG_Current(LSECurrentTypeDef c);
void LSECFG_Capacitance(LSECapTypeDef c);

void Calibration_LSI(Cali_LevelTypeDef cali_Lv); 
void RTC_InitTime(uint16_t y, uint16_t mon, uint16_t d, uint16_t h, uint16_t m, uint16_t s);
void RTC_GetTime(uint16_t* py, uint16_t* pmon, uint16_t* pd, uint16_t* ph, uint16_t* pm, uint16_t* ps);
void RTC_SetCycle32k(uint32_t cyc);
uint32_t RTC_GetCycle32k(void);
void RTC_TRIGFunCfg(uint32_t cyc);
void RTC_TMRFunCfg(RTC_TMRCycTypeDef t);
void RTC_ModeFunDisable(RTC_MODETypeDef m);
uint8_t RTC_GetITFlag(RTC_EVENTTypeDef f);
void RTC_ClearITFlag(RTC_EVENTTypeDef f);
#ifdef __cplusplus
}
#endif



#endif // !__CH58x_CLK_H__
