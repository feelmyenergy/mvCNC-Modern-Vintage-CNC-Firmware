/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * Mightyboard Rev.E pin assignments
 * also works for Rev D boards. It's all rev E despite what the silk screen says
 */

/**
 * Rev B  2 JAN 2017
 *
 *  Added pin definitions for:
 *    M3, M4 & M5 spindle control commands
 *    case light
 *
 *  Corrected pin assignment for EX2_HEAT_PIN pin. Changed it from 9 to 11.  The port
 *  number (B5) agrees with the schematic but B5 is assigned to logical pin 11.
 */

#define ALLOW_MEGA1280
#include "env_validate.h"

#define BOARD_INFO_NAME      "Mightyboard"
#define DEFAULT_MACHINE_NAME "MB Replicator"

//
// Servos
//
#define SERVO0_PIN                            36  // C1 (1280-EX1)
#define SERVO1_PIN                            37  // C0 (1280-EX2)
#define SERVO2_PIN                            40  // G1 (1280-EX3)
#define SERVO3_PIN                            41  // G0 (1280-EX4)

//
// Limit Switches
//
#define X_MIN_PIN                             49  // L0
#define X_MAX_PIN                             48  // L1
#define Y_MIN_PIN                             47  // L2
#define Y_MAX_PIN                             46  // L3
#define Z_MIN_PIN                             43  // L6
#define Z_MAX_PIN                             42  // L7

//
// Z Probe (when not Z_MIN_PIN)
//
#ifndef Z_MIN_PROBE_PIN
  #define Z_MIN_PROBE_PIN                     42
#endif

//
// Filament Runout Sensor
//
#ifndef FIL_RUNOUT_PIN
  #define FIL_RUNOUT_PIN                      49
#endif
#ifndef FIL_RUNOUT2_PIN
  #define FIL_RUNOUT2_PIN                     47
#endif

//
// Steppers
//
#define X_STEP_PIN                            55  // F1
#define X_DIR_PIN                             54  // F0
#define X_ENABLE_PIN                          56  // F2

#define Y_STEP_PIN                            59  // F5
#define Y_DIR_PIN                             58  // F4
#define Y_ENABLE_PIN                          60  // F6

#define Z_STEP_PIN                            63  // K1
#define Z_DIR_PIN                             62  // K0
#define Z_ENABLE_PIN                          64  // K2

#define E0_STEP_PIN                           25  // A3
#define E0_DIR_PIN                            24  // A2
#define E0_ENABLE_PIN                         26  // A4

#define E1_STEP_PIN                           29  // A7
#define E1_DIR_PIN                            28  // A6
#define E1_ENABLE_PIN                         39  // G2

//
// I2C Digipots - MCP4018
// Address 5E (2F << 1)
// Set from 0 - 127 with stop bit.
// (Ex. 3F << 1 | 1)
//
#define DIGIPOTS_I2C_SCL                      76  // J5
#define DIGIPOTS_I2C_SDA_X                    57  // F3
#define DIGIPOTS_I2C_SDA_Y                    61  // F7
#define DIGIPOTS_I2C_SDA_Z                    65  // K3
#define DIGIPOTS_I2C_SDA_E0                   27  // A5
#define DIGIPOTS_I2C_SDA_E1                   77  // J6

#ifndef DIGIPOT_I2C_ADDRESS_A
  #define DIGIPOT_I2C_ADDRESS_A             0x2F  // unshifted slave address (5E <- 2F << 1)
#endif
#define DIGIPOT_ENABLE_I2C_PULLUPS                // MightyBoard doesn't have hardware I2C pin pull-ups.

//
// Temperature Sensors
//
// K7 - 69 / ADC15 - 15
#define TEMP_BED_PIN                          15

// SPI for MAX Thermocouple
// Uses a separate SPI bus
//
//  3 E5 DO (SO)
//  5 E3 CS1
//  2 E4 CS2
// 78 E2 SCK
//
#define TEMP_0_CS_PIN                          5  // E3
#define TEMP_0_SCK_PIN                        78  // E2
#define TEMP_0_MISO_PIN                        3  // E5
//#define TEMP_0_MOSI_PIN                    ...  // For MAX31865

#define TEMP_1_CS_PIN                          2  // E4
#define TEMP_1_SCK_PIN            TEMP_0_SCK_PIN
#define TEMP_1_MISO_PIN          TEMP_0_MISO_PIN
//#define TEMP_1_MOSI_PIN        TEMP_0_MOSI_PIN

//
// Augmentation for auto-assigning plugs
//
// Two thermocouple connectors allows for either
// 2 extruders or 1 extruder and a heated bed.
// With no heated bed, an additional 24V fan is possible.
//

#define MOSFET_A_PIN                           6  // H3 EX1_HEAT_PIN
#define MOSFET_B_PIN                          11  // B5 EX2_HEAT_PIN
#define MOSFET_C_PIN                          45  // L4 HBP_PIN
#define MOSFET_D_PIN                          44  // L5 EXTRA_FET_PIN

//
// Heaters / Fans (24V)
//
#define HEATER_0_PIN                MOSFET_A_PIN

#if FET_ORDER_EFB                                 // Hotend, Fan, Bed
  #define HEATER_BED_PIN            MOSFET_C_PIN
#elif FET_ORDER_EEF                               // Hotend, Hotend, Fan
  #define HEATER_1_PIN              MOSFET_B_PIN
#elif FET_ORDER_EEB                               // Hotend, Hotend, Bed
  #define HEATER_1_PIN              MOSFET_B_PIN
  #define HEATER_BED_PIN            MOSFET_C_PIN
#elif FET_ORDER_EFF                               // Hotend, Fan, Fan
  #define FAN1_PIN                  MOSFET_C_PIN
#endif

#ifndef FAN_PIN
  #if EITHER(FET_ORDER_EFB, FET_ORDER_EFF)        // Hotend, Fan, Bed or Hotend, Fan, Fan
    #define FAN_PIN                 MOSFET_B_PIN
  #elif EITHER(FET_ORDER_EEF, FET_ORDER_SF)       // Hotend, Hotend, Fan or Spindle, Fan
    #define FAN_PIN                 MOSFET_C_PIN
  #else
    #define FAN_PIN                 MOSFET_D_PIN
  #endif
#endif

#ifndef FAN1_PIN
  #define FAN1_PIN                             7  // H4 EX1_FAN_PIN
#endif

#ifndef CONTROLLER_FAN_PIN
  #define CONTROLLER_FAN_PIN                  12  // B6 EX2_FAN_PIN
#endif

//
// Misc. Functions
//
#define LED_PIN                               13  // B7
#define CUTOFF_RESET_PIN                      16  // H1
#define CUTOFF_TEST_PIN                       17  // H0
#define CUTOFF_SR_CHECK_PIN                   70  // G4 (TOSC1)

//
// LCD / Controller
//
#if HAS_WIRED_LCD

  #if IS_RRD_FG_SC

    #define LCD_PINS_RS                       33  // C4: LCD-STROBE
    #define LCD_PINS_ENABLE                   72  // J2: LEFT
    #define LCD_PINS_D4                       35  // C2: LCD-CLK
    #define LCD_PINS_D5                       32  // C5: RLED
    #define LCD_PINS_D6                       34  // C3: LCD-DATA
    #define LCD_PINS_D7                       31  // C6: GLED

    #define BTN_EN2                           75  // J4, UP
    #define BTN_EN1                           73  // J3, DOWN
    //STOP button connected as KILL_PIN
    #define KILL_PIN                          14  // J1, RIGHT
    //KILL - not connected

    #define BEEPER_PIN                         8  // H5, SD_WP

    //on board leds
    #define STAT_LED_RED_LED          SERVO0_PIN  // C1 (1280-EX1, DEBUG2)
    #define STAT_LED_BLUE_PIN         SERVO1_PIN  // C0 (1280-EX2, DEBUG3)

  #else
    // Replicator uses a 3-wire SR controller with HD44780
    #define SR_DATA_PIN                       34  // C3
    #define SR_CLK_PIN                        35  // C2
    #define SR_STROBE_PIN                     33  // C4

    #define BTN_UP                            75  // J4
    #define BTN_DWN                           73  // J3
    #define BTN_LFT                           72  // J2
    #define BTN_RT                            14  // J1

    // Disable encoder
    #undef BTN_EN1
    #undef BTN_EN2

    #define BEEPER_PIN                         4  // G5

    #define STAT_LED_RED_PIN                  32  // C5
    #define STAT_LED_BLUE_PIN                 31  // C6 (Actually green)

  #endif

  #define BTN_CENTER                          15  // J0
  #define BTN_ENC                     BTN_CENTER

#endif // HAS_WIRED_LCD

//
// SD Card
//
#define SDSS                                  53  // B0
#define SD_DETECT_PIN                          9  // H6

#if HAS_TMC_UART
  /**
   * TMC220x stepper drivers
   *
   * Hardware serial communication ports.
   * If undefined software serial is used according to the pins below
   */
  #define X_HARDWARE_SERIAL Serial2
  #define Y_HARDWARE_SERIAL Serial1

  /**
   * Software serial
   */

  #define X_SERIAL_TX_PIN                     16
  #define X_SERIAL_RX_PIN                     17

  #define Y_SERIAL_TX_PIN                     18
  #define Y_SERIAL_RX_PIN                     19

  #define Z_SERIAL_TX_PIN                     41
  #define Z_SERIAL_RX_PIN                     66

  #define E0_SERIAL_TX_PIN                    40
  #define E0_SERIAL_RX_PIN                    67

  #define E1_SERIAL_TX_PIN                    37
  #define E1_SERIAL_RX_PIN                    68

#endif
