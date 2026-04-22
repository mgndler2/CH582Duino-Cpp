#pragma once
#include "CH58x_GPIO_SFR.h"

// Pin definitions taken from:

// LEDs
#define PIN_LED        (8u)
#define LED_BUILTIN PIN_LED

// Serial
#define PIN_SERIAL1_TX (9u)
#define PIN_SERIAL1_RX (8u)
#define PIN_SERIAL1_pTX (29u)	//PB13
#define PIN_SERIAL1_pRX (28u)	//PB12

#define PIN_SERIAL0_TX (23u)	//PB7
#define PIN_SERIAL0_RX (20u)	//PB4
#define PIN_SERIAL0_pTX (14u)
#define PIN_SERIAL0_pRX (15u)
#define PIN_SERIAL0_DTR (21u)	//PB1, Only available on M-suffix
#define PIN_SERIAL0_DSR (17u)	//PB2, Only available on M-suffix
#define PIN_SERIAL0_pDTR (31u)	//PB15
#define PIN_SERIAL0_pDSR (30u)	//PB14

#define PIN_SERIAL2_TX (6u)		//PA6, Only available on M-suffix
#define PIN_SERIAL2_RX (7u)
#define PIN_SERIAL2_pTX (39u)	//PB23
#define PIN_SERIAL2_pRX (38u)	//PB22

#define PIN_SERIAL3_TX (5u)
#define PIN_SERIAL3_RX (4u)
#define PIN_SERIAL3_pTX (37u)	//PB21, Only available on M-suffix
#define PIN_SERIAL3_pRX (36u)	//PB20, Only available on M-suffix

//Only available on M-suffix

// SPI
#define PIN_SPI1_MISO  (2u)		//Only available on 583M
#define PIN_SPI1_MOSI  (1u)		//Only available on 583M
#define PIN_SPI1_SCK   (0u)		//Only available on 583M

#define PIN_SPI0_MISO  (15u)
#define PIN_SPI0_MOSI  (14u)
#define PIN_SPI0_SCK   (13u)
#define PIN_SPI0_SS    (12u)
#define PIN_SPI0_pMISO  (31u)
#define PIN_SPI0_pMOSI  (30u)
#define PIN_SPI0_pSCK   (29u)
#define PIN_SPI0_pSS    (28u)

// Wire
#define PIN_WIRE0_SDA  (4u)
#define PIN_WIRE0_SCL  (5u)

#define PIN_WIRE1_SDA  (26u)
#define PIN_WIRE1_SCL  (27u)

#define SERIAL_HOWMANY (1u)
#define SPI_HOWMANY    (1u)
#define WIRE_HOWMANY   (1u)

static const uint8_t PA0 = (0u);		//NO PIN OUT
static const uint8_t PA1 = (1u);		//NO PIN OUT
static const uint8_t PA2 = (2u);		//NO PIN OUT
static const uint8_t PA3 = (3u);		//NO PIN OUT
static const uint8_t PA4 = (4u);
static const uint8_t PA5 = (5u);
static const uint8_t PA6 = (6u);		//NO PIN OUT
static const uint8_t PA7 = (7u);
static const uint8_t PA8 = (8u);
static const uint8_t PA9 = (9u);
static const uint8_t PA10 = (10u);
static const uint8_t PA11 = (11u);
static const uint8_t PA12 = (12u);
static const uint8_t PA13 = (13u);
static const uint8_t PA14 = (14u);
static const uint8_t PA15 = (15u);
static const uint8_t PB0 = (16u);		//NO PIN OUT
static const uint8_t PB1 = (17u);		//NO PIN OUT
static const uint8_t PB2 = (18u);		//NO PIN OUT
static const uint8_t PB3 = (19u);		//NO PIN OUT
static const uint8_t PB4 = (20u);
static const uint8_t PB5 = (21u);		//NO PIN OUT
static const uint8_t PB6 = (22u);		//NO PIN OUT
static const uint8_t PB7 = (23u);
static const uint8_t PB8 = (24u);		//NO PIN OUT
static const uint8_t PB9 = (25u);		//NO PIN OUT
static const uint8_t PB10 = (26u);		//UDM, USB PORT DO NOT USE
static const uint8_t PB11 = (27u);		//UDP, USB PORT DO NOT USE
static const uint8_t PB12 = (28u);		
static const uint8_t PB13 = (29u);		
static const uint8_t PB14 = (30u);
static const uint8_t PB15 = (31u);
static const uint8_t PB16 = (32u);		//NO PIN OUT
static const uint8_t PB17 = (33u);		//NO PIN OUT
static const uint8_t PB18 = (34u);		//NO PIN OUT
static const uint8_t PB19 = (35u);		//NO PIN OUT
static const uint8_t PB20 = (36u);		//NO PIN OUT
static const uint8_t PB21 = (37u);		//NO PIN OUT
static const uint8_t PB22 = (38u);
static const uint8_t PB23 = (39u);

static const uint8_t AIN0 = (4u);
static const uint8_t AIN1 = (5u);
static const uint8_t AIN2 = (12u);
static const uint8_t AIN3 = (13u);
static const uint8_t AIN4 = (14u);
static const uint8_t AIN5 = (15u);
static const uint8_t AIN6 = (3u);		//NO PIN OUT
static const uint8_t AIN7 = (2u);		//NO PIN OUT
static const uint8_t AIN8 = (1u);		//NO PIN OUT
static const uint8_t AIN9 = (0u);		//NO PIN OUT
static const uint8_t AIN10 = (6u);		//NO PIN OUT
static const uint8_t AIN11 = (7u);		//NO PIN OUT
static const uint8_t AIN12 = (8u);
static const uint8_t AIN13 = (9u);

const uint8_t pin_Channel_map[] = {
    0x09,0x08,0x07,0x06,0x00,
    0x01,0x0A,0x0B,0x0C,0x0D,
    0x0F,0x0F,0x02,0x03,0x04,
    0x05
};

typedef struct PinDesc{
    volatile uint8_t* data_reg;
} PinDesc_t;

typedef struct IntDesc {
    volatile uint16_t* data_reg;
} IntDesc_t;

static const IntDesc pinINT_EN_map[] = {
    [0] = {.data_reg = &(x32_INT_EN.PA_EN) },
    [1] = {.data_reg = &(x32_INT_EN.PB_EN) },
};

static const IntDesc_t pinINT_Mode_map[] = {
    [0] = {.data_reg = &(x32_INT_MODE.PA_MODE) },
    [1] = {.data_reg = &(x32_INT_MODE.PB_MODE) },
};

static const IntDesc_t pinINT_IF_map[] = {
    [0] = {.data_reg = &(x32_INT_IF.PA_IF) },
    [1] = {.data_reg = &(x32_INT_IF.PB_IF) },
};

static const PinDesc_t pinDir_map[] = {
    [0] = {.data_reg = &(x32_PA_DIR.PA_DIR_0) },
    [1] = {.data_reg = &(x32_PA_DIR.PA_DIR_1) },
    [2] = {.data_reg = &(x32_PB_DIR.PB_DIR_0) },
    [3] = {.data_reg = &(x32_PB_DIR.PB_DIR_1) },
    [4] = {.data_reg = &(x32_PB_DIR.PB_DIR_2) },
};

static const PinDesc_t pinIn_map[] = {
    [0] = {.data_reg = &(x32_PA_PIN.PA_PIN_0) },
    [1] = {.data_reg = &(x32_PA_PIN.PA_PIN_1) },
    [2] = {.data_reg = &(x32_PB_PIN.PB_PIN_0) },
    [3] = {.data_reg = &(x32_PB_PIN.PB_PIN_1) },
    [4] = {.data_reg = &(x32_PB_PIN.PB_PIN_2) },
};

static const PinDesc_t pinOut_map[] = {
    [0] = {.data_reg = &(x32_PA_OUT.PA_OUT_0) },
    [1] = {.data_reg = &(x32_PA_OUT.PA_OUT_1) },
    [2] = {.data_reg = &(x32_PB_OUT.PB_OUT_0) },
    [3] = {.data_reg = &(x32_PB_OUT.PB_OUT_1) },
    [4] = {.data_reg = &(x32_PB_OUT.PB_OUT_2) },
};

static const PinDesc_t pinClr_map[] = {
    [0] = {.data_reg = &(x32_PA_CLR.PA_CLR_0) },
    [1] = {.data_reg = &(x32_PA_CLR.PA_CLR_1) },
    [2] = {.data_reg = &(x32_PB_CLR.PB_CLR_0) },
    [3] = {.data_reg = &(x32_PB_CLR.PB_CLR_1) },
    [4] = {.data_reg = &(x32_PB_CLR.PB_CLR_2) },
};

static const PinDesc_t pinPU_map[] = {
    [0] = {.data_reg = &(x32_PA_PU.PA_PU_0) },
    [1] = {.data_reg = &(x32_PA_PU.PA_PU_1) },
    [2] = {.data_reg = &(x32_PB_PU.PB_PU_0) },
    [3] = {.data_reg = &(x32_PB_PU.PB_PU_1) },
    [4] = {.data_reg = &(x32_PB_PU.PB_PU_2) },
};

static const PinDesc_t pinPD_map[] = {
    {.data_reg = &(x32_PA_PD_DRV.PA_PD_DRV_0) },
    {.data_reg = &(x32_PA_PD_DRV.PA_PD_DRV_1) },
    {.data_reg = &(x32_PB_PD_DRV.PB_PD_DRV_0) },
    {.data_reg = &(x32_PB_PD_DRV.PB_PD_DRV_1) },
    {.data_reg = &(x32_PB_PD_DRV.PB_PD_DRV_2) },
};
