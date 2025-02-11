/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * E4d@box pin assignments
 *
 * Small factor CNC control board based on the ESP32 microcontroller for Laser, CNC and CNCs.
 * More info at https://atbox.tech/ and the E4d@box Facebook page.
 */

#include "env_validate.h"

#if EXTRUDERS > 1 || E_STEPPERS > 1
  #error "E4d@box only supports one E Stepper. Comment out this line to continue."
#elif HAS_MULTI_HOTEND
  #error "E4d@box only supports one hotend / E-stepper. Comment out this line to continue."
#endif

#define BOARD_INFO_NAME       "E4d@box"
#define BOARD_WEBSITE_URL     "github.com/Exilaus/E4d@box"
#define DEFAULT_MACHINE_NAME  BOARD_INFO_NAME

//
// Disable I2S stepper stream
//
#undef I2S_STEPPER_STREAM

//
// Redefine I2S for ESP32
//
#undef I2S_WS
#define I2S_WS                                23
#undef I2S_BCK
#define I2S_BCK                               22
#undef I2S_DATA
#define I2S_DATA                              21

//
// Limit Switches
//
#define X_STOP_PIN                            34
#define Y_STOP_PIN                            35
#define Z_STOP_PIN                            16

//
// Steppers
//
#define X_STEP_PIN                            12
#define X_DIR_PIN                             13
#define X_ENABLE_PIN                          17
//#define X_CS_PIN                             0

#define Y_STEP_PIN                            32
#define Y_DIR_PIN                             33
#define Y_ENABLE_PIN                X_ENABLE_PIN
//#define Y_CS_PIN                            13

#define Z_STEP_PIN                            25
#define Z_DIR_PIN                             26
#define Z_ENABLE_PIN                X_ENABLE_PIN
//#define Z_CS_PIN                             5  // SS_PIN

#define E0_STEP_PIN                           27
#define E0_DIR_PIN                            14
#define E0_ENABLE_PIN               X_ENABLE_PIN
//#define E0_CS_PIN                           21

//
// Temperature Sensors
//
#define TEMP_0_PIN                            36  // Analog Input
#define TEMP_BED_PIN                          39  // Analog Input

//
// Heaters / Fans
//
#define HEATER_0_PIN                           2
#define FAN_PIN                                0
#define HEATER_BED_PIN                        15

//
// MicroSD card on SPI
//
#define SD_MOSI_PIN                           23
#define SD_MISO_PIN                           19
#define SD_SCK_PIN                            18
#define SDSS                                   5
#define USES_SHARED_SPI                           // SPI is shared by SD card with TMC SPI drivers
