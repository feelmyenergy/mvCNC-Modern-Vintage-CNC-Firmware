/**
 * Modern Vintage CNC Firmware
 * Copyright (c) 2020 mvCNCFirmware [https://github.com/Domush/Webber-Ranch-CNC-Firmware]
 *
 * Based on Marlin and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * SAMD51 HAL developed by Giuliano Zaro (AKA GMagician)
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

/**
 * Description: Tone function for Arduino Due and compatible (SAM3X8E)
 * Derived from https://forum.arduino.cc/index.php?topic=136500.msg2903012#msg2903012
 */

#ifdef ARDUINO_ARCH_SAM

#include "../../inc/mvCNCConfig.h"
#include "HAL.h"

static pin_t tone_pin;
volatile static int32_t toggles;

void tone(const pin_t _pin, const unsigned int frequency, const unsigned long duration) {
  tone_pin = _pin;
  toggles = 2 * frequency * duration / 1000;
  HAL_timer_start(MF_TIMER_TONE, 2 * frequency);
}

void noTone(const pin_t _pin) {
  HAL_timer_disable_interrupt(MF_TIMER_TONE);
  extDigitalWrite(_pin, LOW);
}

HAL_TONE_TIMER_ISR() {
  static uint8_t pin_state = 0;
  HAL_timer_isr_prologue(MF_TIMER_TONE);

  if (toggles) {
    toggles--;
    extDigitalWrite(tone_pin, (pin_state ^= 1));
  }
  else noTone(tone_pin);                         // turn off interrupt
}

#endif // ARDUINO_ARCH_SAM
