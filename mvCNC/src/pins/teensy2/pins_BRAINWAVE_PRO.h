/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * Brainwave Pro pin assignments (AT90USB1286)
 *
 * Requires hardware bundle for Arduino:
 * https://github.com/unrepentantgeek/brainwave-arduino
 */

/**
 *  Rev B  16 JAN 2017
 *
 *  Added pointers to currently available Arduino IDE extensions that will
 *  allow this board to use the latest mvCNC software
 *
 *
 *  Rev C  2 JUN 2017
 *
 *  Converted to Arduino pin numbering
 */

/**
 *  There are two Arduino IDE extensions that are compatible with this board
 *  and with the mainstream mvCNC software.
 *
 *  Teensyduino - https://www.pjrc.com/teensy/teensyduino.html
 *    Select Teensy++ 2.0 in Arduino IDE from the 'Tools > Board' menu
 *
 *    Installation instructions are at the above URL.  Don't bother loading the
 *    libraries - they are not used with the mvCNC software.
 *
 *  Printrboard - https://github.com/scwimbush/Printrboard-HID-Arduino-IDE-Support
 *
 *    Installation:
 *
 *       1. Go to the above URL, click on the "Clone or Download" button and then
 *          click on "Download ZIP" button.
 *       2. Unzip the file, find the "printrboard" directory and then copy it to the
 *          hardware directory in Arduino.  The Arduino hardware directory will probably
 *          be located in a path similar to this: C:\Program Files (x86)\Arduino\hardware.
 *       3. Restart Arduino.
 *       4. Select "Printrboard" from the 'Tools > Board' menu.
 *
 *  Teensyduino is the most popular option. Printrboard is used if your board doesn't have
 *  the Teensyduino bootloader on it.
 */

/**
 *  To burn the bootloader that comes with Printrboard:
 *
 *   1. Connect your programmer to the board.
 *   2. In the Arduino IDE select "Printrboard" and then select the programmer.
 *   3. In the Arduino IDE click on "burn bootloader". Don't worry about the "verify failed at 1F000" error message.
 *   4. The programmer is no longer needed. Remove it.
 */

#include "env_validate.h"

#define BOARD_INFO_NAME "Brainwave Pro"

//
// Limit Switches
//
#define X_STOP_PIN                            45  // F7
#define Y_STOP_PIN                            12  // C2
#define Z_STOP_PIN                            36  // E4

//
// Z Probe (when not Z_MIN_PIN)
//
#ifndef Z_MIN_PROBE_PIN
  #define Z_MIN_PROBE_PIN                     11  // C1
#endif

//
// Steppers
//
#define X_STEP_PIN                             9  // E1
#define X_DIR_PIN                              8  // E0
#define X_ENABLE_PIN                          23  // B3

#define Y_STEP_PIN                             7  // D7
#define Y_DIR_PIN                              6  // D6
#define Y_ENABLE_PIN                          20  // B0

#define Z_STEP_PIN                             5  // D5
#define Z_DIR_PIN                              4  // D4
#define Z_ENABLE_PIN                          37  // E5

#define E0_STEP_PIN                           47  // E3
#define E0_DIR_PIN                            46  // E2
#define E0_ENABLE_PIN                         25  // B5

//
// Temperature Sensors
//
#define TEMP_0_PIN                             2  // F2  Analog Input
#define TEMP_1_PIN                             1  // F1  Analog Input
#define TEMP_BED_PIN                           0  // F0  Analog Input

//
// Heaters / Fans
//
#define HEATER_0_PIN                          27  // B7
#define HEATER_BED_PIN                        26  // B6  Bed
#ifndef FAN_PIN
  #define FAN_PIN                             16  // C6  Fan, PWM3A
#endif

//
// Misc. Functions
//
#define SDSS                                  20  // B0
#define SD_DETECT_PIN                         24  // B4
#define LED_PIN                               13  // C3
