/*
  wiring_analog.cpp - analog input and output functions
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
#include "CH58x_ADC.h"
#include "CH58x_GPIO_SFR.h"

static int write_resolution = 8;
static int read_resolution = 10;


void analogWrite(pin_size_t pin, int val)
{
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
        SqureWave.enablePWM(channel);
        SqureWave.setVal(channel, val);
    }
}

void analogWriteResolution(int bits)
{
    write_resolution = SqureWave.setResolution(bits);
}

int analogRead(pin_size_t pin, uint8_t gain, uint8_t div)
{
    if (pin > 15) return 0;
    Analog.setADC_CH(pin_Channel_map[pin]);
    if (Analog.getCLK_DIV() != div || Analog.getPGA_GAIN() != gain)
    {
        Analog.setCLK_DIV((ns_ADC::CLK_DIV)div, false);
        Analog.setPGA_GAIN((ns_ADC::PGA_GAIN)gain);
    }
    return Analog.doConversion();
}

void analogReadResolution(int bits)
{
  read_resolution = bits;
}

int getAnalogReadResolution()
{
  return read_resolution;
}