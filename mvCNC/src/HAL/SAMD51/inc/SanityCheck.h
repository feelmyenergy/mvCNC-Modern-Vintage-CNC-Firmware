/**
 * Modern Vintage CNC Firmware
 *
 * Copyright (c) 2020 mvCNCFirmware [https://github.com/Domush/Webber-Ranch-CNC-Firmware]
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
 * Test SAMD51 specific configuration values for errors at compile-time.
 */

#if ENABLED(FLASH_EEPROM_EMULATION)
  #warning "Did you activate the SmartEEPROM? See https://github.com/GMagician/SAMD51-SmartEEprom-Manager/releases"
#endif

#if defined(ADAFRUIT_GRAND_CENTRAL_M4) && SD_CONNECTION_IS(CUSTOM_CABLE)
  #error "No custom SD drive cable defined for this board."
#endif

#if (defined(TEMP_0_SCK_PIN) && defined(TEMP_0_MISO_PIN) && (TEMP_0_SCK_PIN == SCK1 || TEMP_0_MISO_PIN == MISO1)) || \
    (defined(TEMP_1_SCK_PIN) && defined(TEMP_1_MISO_PIN) && (TEMP_1_SCK_PIN == SCK1 || TEMP_1_MISO_PIN == MISO1))
  #error "OnBoard SPI BUS can't be shared with other devices."
#endif

#if SERVO_TC == MF_TIMER_RTC
  #error "Servos can't use RTC timer"
#endif

#if ENABLED(EMERGENCY_PARSER)
  #error "EMERGENCY_PARSER is not yet implemented for SAMD51. Disable EMERGENCY_PARSER to continue."
#endif

#if ENABLED(SDIO_SUPPORT)
  #error "SDIO_SUPPORT is not supported on SAMD51."
#endif

#if ENABLED(FAST_PWM_FAN) || SPINDLE_LASER_FREQUENCY
  #error "Features requiring Hardware PWM (FAST_PWM_FAN, SPINDLE_LASER_FREQUENCY) are not yet supported on SAMD51."
#endif

#if ENABLED(POSTMORTEM_DEBUGGING)
  #error "POSTMORTEM_DEBUGGING is not yet supported on AGCM4."
#endif
