/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * ZRIB V2.0 & V3.0 pin assignments
 * V2 and V3 Boards only differ in USB controller, nothing affecting the pins.
 */

#include "pins_MKS_GEN_13.h" // ... RAMPS

#define ZRIB_V20_D6_PIN                        6  // Fan
#define ZRIB_V20_D9_PIN                        9  // Fan2
#define ZRIB_V20_A10_PIN                      10
#define ZRIB_V20_D16_PIN                      16
#define ZRIB_V20_D17_PIN                      17
#define ZRIB_V20_D23_PIN                      23
#define ZRIB_V20_D25_PIN                      25
#define ZRIB_V20_D27_PIN                      27
#define ZRIB_V20_D29_PIN                      29
#define ZRIB_V20_D37_PIN                      37

//
// Auto fans
//
#ifndef E0_AUTO_FAN_PIN
  #define E0_AUTO_FAN_PIN        ZRIB_V20_D6_PIN
#endif
#ifndef E1_AUTO_FAN_PIN
  #define E1_AUTO_FAN_PIN        ZRIB_V20_D6_PIN
#endif
#ifndef E2_AUTO_FAN_PIN
  #define E2_AUTO_FAN_PIN        ZRIB_V20_D6_PIN
#endif
#ifndef E3_AUTO_FAN_PIN
  #define E3_AUTO_FAN_PIN        ZRIB_V20_D6_PIN
#endif

#ifndef FILWIDTH_PIN
  #define FILWIDTH_PIN                        11  // Analog Input
#endif

#if ENABLED(ZONESTAR_LCD)
  #undef LCD_PINS_RS
  #undef LCD_PINS_ENABLE
  #undef LCD_PINS_D4
  #undef LCD_PINS_D5
  #undef LCD_PINS_D6
  #undef LCD_PINS_D7
  #undef ADC_KEYPAD_PIN
  #undef BEEPER_PIN

  #undef SHIFT_OUT_PIN
  #undef SHIFT_CLK_PIN
  #undef SHIFT_LD_PIN
  #undef BTN_EN1
  #undef BTN_EN2
  #undef BTN_ENC

  #define LCD_PINS_RS           ZRIB_V20_D16_PIN
  #define LCD_PINS_ENABLE       ZRIB_V20_D17_PIN
  #define LCD_PINS_D4           ZRIB_V20_D23_PIN
  #define LCD_PINS_D5           ZRIB_V20_D25_PIN
  #define LCD_PINS_D6           ZRIB_V20_D27_PIN
  #define LCD_PINS_D7           ZRIB_V20_D29_PIN
  #define ADC_KEYPAD_PIN        ZRIB_V20_A10_PIN
  #define BEEPER_PIN            ZRIB_V20_D37_PIN
#endif
