/*
  wiring_digital.cpp - digital input and output functions
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2018-2019 Arduino SA

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/

#include "Arduino.h"
#include "pins_arduino.h"
#include "CH58x_PWM.h"

void pinMode(pin_size_t pin, PinMode mode, bool highPower)
{
    uint8_t Group = pin / 8, Bit = pin % 8;
    switch (mode) {
    case INPUT:
        *pinPD_map[Group].data_reg &= ~(1u << Bit);
        *pinPU_map[Group].data_reg &= ~(1u << Bit);
        *pinDir_map[Group].data_reg &= ~(1u << Bit);
        break;
    case OUTPUT:
        if (highPower) {
            *pinPD_map[Group].data_reg |= (1u << Bit);
        }
        else {
            *pinPD_map[Group].data_reg &= ~(1u << Bit);
        }
        *pinDir_map[Group].data_reg |= (1u << Bit);
        break;
    case INPUT_PULLUP:
        *pinPD_map[Group].data_reg &= ~(1u << Bit);
        *pinPU_map[Group].data_reg |= (1u << Bit);
        *pinDir_map[Group].data_reg &= ~(1u << Bit);
        break;
    case INPUT_PULLDOWN:
        *pinPD_map[Group].data_reg |= (1u << Bit);
        *pinPU_map[Group].data_reg &= ~(1u << Bit);
        *pinDir_map[Group].data_reg &= ~(1u << Bit);
        break;
    default:
        *pinPD_map[Group].data_reg &= ~(1u << Bit);
        *pinPU_map[Group].data_reg &= ~(1u << Bit);
        *pinDir_map[Group].data_reg &= ~(1u << Bit);
        break;
    }
}


void digitalWrite(pin_size_t pin, PinStatus val)
{
    uint8_t Group = pin / 8, Bit = pin % 8;
    if (val == HIGH) {
        *pinOut_map[Group].data_reg |= (1u << Bit);
    }
    else if(val == LOW){
        *pinClr_map[Group].data_reg |= (1u << Bit);
    }

    int8_t channel = 0xFF;
    switch (pin) {
    case PA6:
        if (x16_PIN_ALTERNATE.PIN_PWMX == 1)
            channel = 4;
        break;
    case PA12:
        if (x16_PIN_ALTERNATE.PIN_PWMX == 0)
            channel = 4;
        break;
    case PA7:
        if (x16_PIN_ALTERNATE.PIN_PWMX == 1)
            channel = 5;
        break;
    case PA13:
        if (x16_PIN_ALTERNATE.PIN_PWMX == 0)
            channel = 5;
        break;
    case PB0:
        channel = 6;
        break;
    case PB1:
        if (x16_PIN_ALTERNATE.PIN_PWMX == 1)
            channel = 7;
        break;
    case PB4:
        if (x16_PIN_ALTERNATE.PIN_PWMX == 0)
            channel = 7;
        break;
    case PB2:
        if (x16_PIN_ALTERNATE.PIN_PWMX == 1)
            channel = 8;
        break;
    case PB6:
        if (x16_PIN_ALTERNATE.PIN_PWMX == 0)
            channel = 8;
        break;
    case PB3:
        if (x16_PIN_ALTERNATE.PIN_PWMX == 1)
            channel = 9;
        break;
    case PB7:
        if (x16_PIN_ALTERNATE.PIN_PWMX == 0)
            channel = 9;
        break;
    case PB14:
        channel = 10;
        break;
    case PB23:
        channel = 11;
        break;
    }
    if (channel > 0) {
        SqureWave.disablePWM(channel);
    }
}

PinStatus digitalRead(pin_size_t pin)
{
    uint8_t Group = pin / 8, Bit = pin % 8;
    uint8_t result = *pinIn_map[Group].data_reg & (1u << Bit);
    return (PinStatus)(result > 0);
}