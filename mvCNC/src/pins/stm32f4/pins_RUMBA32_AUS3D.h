/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * Pin assignments for the RUMBA32
 *
 * https://aus3d.com.au/rumba32
 * https://github.com/Aus3D/RUMBA32
 */

#define BOARD_INFO_NAME "RUMBA32"

#if NO_EEPROM_SELECTED
  #if MB(RUMBA32_V1_0)
    #define FLASH_EEPROM_EMULATION
    #define mvCNC_EEPROM_SIZE            0x1000  // 4KB
  #elif MB(RUMBA32_V1_1)
    #define I2C_EEPROM
    #define mvCNC_EEPROM_SIZE            0x2000  // 8KB (24LC64T-I/OT)
  #endif
#endif

#if ENABLED(FLASH_EEPROM_EMULATION)
  // Decrease delays and flash wear by spreading writes across the
  // 128 kB sector allocated for EEPROM emulation.
  #define FLASH_EEPROM_LEVELING
#endif

#include "pins_RUMBA32_common.h"

#if MB(RUMBA32_V1_1)

  #define SERVO0_PIN                        PA15

  #if HAS_TMC_UART
    //
    // TMC2208/TMC2209 stepper drivers - Software Serial is used according to below pins
    //
    #define X_SERIAL_TX_PIN                 PA14
    #define X_SERIAL_RX_PIN                 PC14

    #define Y_SERIAL_TX_PIN                 PA13
    #define Y_SERIAL_RX_PIN                 PE4

    #define Z_SERIAL_TX_PIN                 PB10
    #define Z_SERIAL_RX_PIN                 PE0

    #define E0_SERIAL_TX_PIN                PD11
    #define E0_SERIAL_RX_PIN                PC13

    #define E1_SERIAL_TX_PIN                PB3
    #define E1_SERIAL_RX_PIN                PD5

    #define E2_SERIAL_TX_PIN                PB4
    #define E2_SERIAL_RX_PIN                PD1
  #endif
#endif
