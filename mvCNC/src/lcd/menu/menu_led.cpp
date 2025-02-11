/**
 * Modern Vintage CNC Firmware
*/

//
// LED Menu
//

#include "../../inc/mvCNCConfigPre.h"

#if HAS_MVCNCUI_MENU && EITHER(LED_CONTROL_MENU, CASE_LIGHT_MENU)

#include "menu_item.h"

#if ENABLED(PSU_CONTROL)
  #include "../../feature/power.h"
#endif

#if ENABLED(LED_CONTROL_MENU)
  #include "../../feature/leds/leds.h"

  #if ENABLED(LED_COLOR_PRESETS)

    void menu_led_presets() {
      START_MENU();
      #if LCD_HEIGHT > 2
        STATIC_ITEM(MSG_LED_PRESETS, SS_DEFAULT|SS_INVERT);
      #endif
      BACK_ITEM(MSG_LED_CONTROL);
      ACTION_ITEM(MSG_SET_LEDS_WHITE,  leds.set_white);
      ACTION_ITEM(MSG_SET_LEDS_RED,    leds.set_red);
      ACTION_ITEM(MSG_SET_LEDS_ORANGE, leds.set_orange);
      ACTION_ITEM(MSG_SET_LEDS_YELLOW, leds.set_yellow);
      ACTION_ITEM(MSG_SET_LEDS_GREEN,  leds.set_green);
      ACTION_ITEM(MSG_SET_LEDS_BLUE,   leds.set_blue);
      ACTION_ITEM(MSG_SET_LEDS_INDIGO, leds.set_indigo);
      ACTION_ITEM(MSG_SET_LEDS_VIOLET, leds.set_violet);
      END_MENU();
    }

  #endif

  #if ENABLED(NEO2_COLOR_PRESETS)

    void menu_leds2_presets() {
      START_MENU();
      #if LCD_HEIGHT > 2
        STATIC_ITEM(MSG_NEO2_PRESETS, SS_DEFAULT|SS_INVERT);
      #endif
      BACK_ITEM(MSG_LED_CONTROL);
      ACTION_ITEM(MSG_SET_LEDS_WHITE,  leds2.set_white);
      ACTION_ITEM(MSG_SET_LEDS_RED,    leds2.set_red);
      ACTION_ITEM(MSG_SET_LEDS_ORANGE, leds2.set_orange);
      ACTION_ITEM(MSG_SET_LEDS_YELLOW, leds2.set_yellow);
      ACTION_ITEM(MSG_SET_LEDS_GREEN,  leds2.set_green);
      ACTION_ITEM(MSG_SET_LEDS_BLUE,   leds2.set_blue);
      ACTION_ITEM(MSG_SET_LEDS_INDIGO, leds2.set_indigo);
      ACTION_ITEM(MSG_SET_LEDS_VIOLET, leds2.set_violet);
      END_MENU();
    }

  #endif

  void menu_led_custom() {
    START_MENU();
    BACK_ITEM(MSG_LED_CONTROL);
    #if ENABLED(NEOPIXEL2_SEPARATE)
      STATIC_ITEM_N(MSG_LED_CHANNEL_N, 1, SS_DEFAULT|SS_INVERT);
    #endif
    EDIT_ITEM(uint8, MSG_INTENSITY_R, &leds.color.r, 0, 255, leds.update, true);
    EDIT_ITEM(uint8, MSG_INTENSITY_G, &leds.color.g, 0, 255, leds.update, true);
    EDIT_ITEM(uint8, MSG_INTENSITY_B, &leds.color.b, 0, 255, leds.update, true);
    #if HAS_WHITE_LED
      EDIT_ITEM(uint8, MSG_INTENSITY_W, &leds.color.w, 0, 255, leds.update, true);
    #endif
    #if ENABLED(NEOPIXEL_LED)
      EDIT_ITEM(uint8, MSG_LED_BRIGHTNESS, &leds.color.i, 0, 255, leds.update, true);
    #endif
    #if ENABLED(NEOPIXEL2_SEPARATE)
      STATIC_ITEM_N(MSG_LED_CHANNEL_N, 2, SS_DEFAULT|SS_INVERT);
      EDIT_ITEM(uint8, MSG_INTENSITY_R, &leds2.color.r, 0, 255, leds2.update, true);
      EDIT_ITEM(uint8, MSG_INTENSITY_G, &leds2.color.g, 0, 255, leds2.update, true);
      EDIT_ITEM(uint8, MSG_INTENSITY_B, &leds2.color.b, 0, 255, leds2.update, true);
      #if HAS_WHITE_LED2
        EDIT_ITEM(uint8, MSG_INTENSITY_W, &leds2.color.w, 0, 255, leds2.update, true);
      #endif
      EDIT_ITEM(uint8, MSG_NEO2_BRIGHTNESS, &leds2.color.i, 0, 255, leds2.update, true);
    #endif
    END_MENU();
  }
#endif

#if ENABLED(CASE_LIGHT_MENU)
  #include "../../feature/caselight.h"

  #define CASELIGHT_TOGGLE_ITEM() EDIT_ITEM(bool, MSG_CASE_LIGHT, (bool*)&caselight.on, caselight.update_enabled)

  #if CASELIGHT_USES_BRIGHTNESS
    void menu_case_light() {
      START_MENU();
      BACK_ITEM(MSG_CONFIGURATION);
      EDIT_ITEM(percent, MSG_CASE_LIGHT_BRIGHTNESS, &caselight.brightness, 0, 255, caselight.update_brightness, true);
      CASELIGHT_TOGGLE_ITEM();
      END_MENU();
    }
  #endif
#endif

void menu_led() {
  START_MENU();
  BACK_ITEM(MSG_MAIN);

  #if ENABLED(LED_CONTROL_MENU)
    if (TERN1(PSU_CONTROL, powerManager.psu_on)) {
      editable.state = leds.lights_on;
      EDIT_ITEM(bool, MSG_LEDS, &editable.state, leds.toggle);
    }

    #if ENABLED(LED_COLOR_PRESETS)
      ACTION_ITEM(MSG_SET_LEDS_DEFAULT, leds.set_default);
    #endif

    #if ENABLED(NEOPIXEL2_SEPARATE)
      editable.state = leds2.lights_on;
      EDIT_ITEM(bool, MSG_LEDS2, &editable.state, leds2.toggle);
      #if ENABLED(NEO2_COLOR_PRESETS)
        ACTION_ITEM(MSG_SET_LEDS_DEFAULT, leds2.set_default);
      #endif
    #endif
    #if ENABLED(LED_COLOR_PRESETS)
      SUBMENU(MSG_LED_PRESETS, menu_led_presets);
    #endif
    #if ENABLED(NEO2_COLOR_PRESETS)
      SUBMENU(MSG_NEO2_PRESETS, menu_leds2_presets);
    #endif
    SUBMENU(MSG_CUSTOM_LEDS, menu_led_custom);
  #endif

  //
  // Set Case light on/off/brightness
  //
  #if ENABLED(CASE_LIGHT_MENU)
    #if CASELIGHT_USES_BRIGHTNESS
      if (caselight.has_brightness())
        SUBMENU(MSG_CASE_LIGHT, menu_case_light);
      else
    #endif
        CASELIGHT_TOGGLE_ITEM();
  #endif

  END_MENU();
}

#endif // HAS_MVCNCUI_MENU && LED_CONTROL_MENU
