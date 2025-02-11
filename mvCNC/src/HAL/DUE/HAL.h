/**
 * Modern Vintage CNC Firmware
 *
 * Copyright (c) 2020 mvCNCFirmware [https://github.com/Domush/Webber-Ranch-CNC-Firmware]
 * Copyright (c) 2016 Bob Cousins bobcousins42@googlemail.com
 * Copyright (c) 2015-2016 Nico Tonnhofer wurstnase.reprap@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * HAL for Arduino Due and compatible (SAM3X8E)
 */

#define CPU_32_BIT

#include "../shared/Marduino.h"
#include "../shared/eeprom_if.h"
#include "../shared/math_32bit.h"
#include "../shared/HAL_SPI.h"
#include "fastio.h"
#include "watchdog.h"

#include <stdint.h>

#include "../../core/serial_hook.h"

typedef ForwardSerial1Class< decltype(Serial) > DefaultSerial1;
typedef ForwardSerial1Class< decltype(Serial1) > DefaultSerial2;
typedef ForwardSerial1Class< decltype(Serial2) > DefaultSerial3;
typedef ForwardSerial1Class< decltype(Serial3) > DefaultSerial4;
extern DefaultSerial1 MSerial0;
extern DefaultSerial2 MSerial1;
extern DefaultSerial3 MSerial2;
extern DefaultSerial4 MSerial3;

#define _MSERIAL(X) MSerial##X
#define MSERIAL(X) _MSERIAL(X)

#if SERIAL_PORT == -1 || ENABLED(EMERGENCY_PARSER)
  #define MYSERIAL1 customizedSerial1
#elif WITHIN(SERIAL_PORT, 0, 3)
  #define MYSERIAL1 MSERIAL(SERIAL_PORT)
#else
  #error "The required SERIAL_PORT must be from 0 to 3, or -1 for USB Serial."
#endif

#ifdef SERIAL_PORT_2
  #if SERIAL_PORT_2 == -1 || ENABLED(EMERGENCY_PARSER)
    #define MYSERIAL2 customizedSerial2
  #elif WITHIN(SERIAL_PORT_2, 0, 3)
    #define MYSERIAL2 MSERIAL(SERIAL_PORT_2)
  #else
    #error "SERIAL_PORT_2 must be from 0 to 3, or -1 for USB Serial."
  #endif
#endif

#ifdef SERIAL_PORT_3
  #if SERIAL_PORT_3 == -1 || ENABLED(EMERGENCY_PARSER)
    #define MYSERIAL3 customizedSerial3
  #elif WITHIN(SERIAL_PORT_3, 0, 3)
    #define MYSERIAL3 MSERIAL(SERIAL_PORT_3)
  #else
    #error "SERIAL_PORT_3 must be from 0 to 3, or -1 for USB Serial."
  #endif
#endif

#ifdef MMU2_SERIAL_PORT
  #if WITHIN(MMU2_SERIAL_PORT, 0, 3)
    #define MMU2_SERIAL MSERIAL(MMU2_SERIAL_PORT)
  #else
    #error "MMU2_SERIAL_PORT must be from 0 to 3."
  #endif
#endif

#ifdef LCD_SERIAL_PORT
  #if WITHIN(LCD_SERIAL_PORT, 0, 3)
    #define LCD_SERIAL MSERIAL(LCD_SERIAL_PORT)
  #else
    #error "LCD_SERIAL_PORT must be from 0 to 3."
  #endif
#endif

#include "mvCNCSerial.h"
#include "mvCNCSerialUSB.h"

// On AVR this is in math.h?
#define square(x) ((x)*(x))

typedef int8_t pin_t;

#define SHARED_SERVOS HAS_SERVOS
#define HAL_SERVO_LIB Servo

//
// Interrupts
//
#define CRITICAL_SECTION_START()  uint32_t primask = __get_PRIMASK(); __disable_irq()
#define CRITICAL_SECTION_END()    if (!primask) __enable_irq()
#define ISRS_ENABLED() (!__get_PRIMASK())
#define ENABLE_ISRS()  __enable_irq()
#define DISABLE_ISRS() __disable_irq()

void cli();                     // Disable interrupts
void sei();                     // Enable interrupts

void HAL_clear_reset_source();  // clear reset reason
uint8_t HAL_get_reset_source(); // get reset reason

void HAL_reboot();

//
// ADC
//
extern uint16_t HAL_adc_result;     // result of last ADC conversion

#ifndef analogInputToDigitalPin
  #define analogInputToDigitalPin(p) ((p < 12U) ? (p) + 54U : -1)
#endif

#define HAL_ANALOG_SELECT(ch)

inline void HAL_adc_init() {}//todo

#define HAL_ADC_VREF         3.3
#define HAL_ADC_RESOLUTION  10
#define HAL_START_ADC(ch)   HAL_adc_start_conversion(ch)
#define HAL_READ_ADC()      HAL_adc_result
#define HAL_ADC_READY()     true

void HAL_adc_start_conversion(const uint8_t ch);
uint16_t HAL_adc_get_result();

//
// PWM
//
inline void set_pwm_duty(const pin_t pin, const uint16_t v, const uint16_t=255, const bool=false) { analogWrite(pin, v); }

//
// Pin Map
//
#define GET_PIN_MAP_PIN(index) index
#define GET_PIN_MAP_INDEX(pin) pin
#define PARSED_PIN_INDEX(code, dval) parser.intval(code, dval)

//
// Tone
//
void toneInit();
void tone(const pin_t _pin, const unsigned int frequency, const unsigned long duration=0);
void noTone(const pin_t _pin);

// Enable hooks into idle and setup for HAL
#define HAL_IDLETASK 1
void HAL_idletask();
void HAL_init();

//
// Utility functions
//
void _delay_ms(const int delay);

#pragma GCC diagnostic push
#if GCC_VERSION <= 50000
  #pragma GCC diagnostic ignored "-Wunused-function"
#endif

int freeMemory();

#pragma GCC diagnostic pop

#ifdef __cplusplus
  extern "C" {
#endif
char *dtostrf(double __val, signed char __width, unsigned char __prec, char *__s);
#ifdef __cplusplus
  }
#endif
