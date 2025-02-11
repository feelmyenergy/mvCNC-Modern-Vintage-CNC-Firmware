/**
 * Modern Vintage CNC Firmware
*/

/**
 * lcd/extui/malyan/malyan_extui.cpp
 */

#include "../../../inc/mvCNCConfigPre.h"

#if ENABLED(MALYAN_LCD)

#include "../ui_api.h"
#include "malyan.h"

//#include "../../mvcncui.h"
//#include "../../../sd/cardreader.h"
//#include "../../../module/temperature.h"
//#include "../../../module/stepper.h"
//#include "../../../module/motion.h"
//#include "../../../libs/duration_t.h"
//#include "../../../module/printcounter.h"
//#include "../../../gcode/queue.h"

namespace ExtUI {
  void onStartup() {
    /**
     * The Malyan LCD actually runs as a separate MCU on Serial 1.
     * This code's job is to siphon the weird curly-brace commands from
     * it and translate into ExtUI operations where possible.
     */
    inbound_count = 0;

    #ifndef LCD_BAUDRATE
      #define LCD_BAUDRATE 500000
    #endif
    LCD_SERIAL.begin(LCD_BAUDRATE);

    // Signal init
    write_to_lcd(F("{SYS:STARTED}\r\n"));

    // send a version that says "unsupported"
    write_to_lcd(F("{VER:99}\r\n"));

    // No idea why it does this twice.
    write_to_lcd(F("{SYS:STARTED}\r\n"));
    update_usb_status(true);
  }

  void onIdle() {
    /**
     * - from cnc on startup:
     * {SYS:STARTED}{VER:29}{SYS:STARTED}{R:UD}
     */

    // First report USB status.
    update_usb_status(false);

    // now drain commands...
    while (LCD_SERIAL.available())
      parse_lcd_byte((byte)LCD_SERIAL.read());

    #if ENABLED(SDSUPPORT)
      // The way last printing status works is simple:
      // The UI needs to see at least one TQ which is not 100%
      // and then when the print is complete, one which is.
      static uint8_t last_percent_done = 100;

      // If there was a print in progress, we need to emit the final
      // print status as {TQ:100}. Reset last percent done so a new print will
      // issue a percent of 0.
      const uint8_t percent_done = (ExtUI::isPrinting() || ExtUI::isPrintingFromMediaPaused()) ? ExtUI::getProgress_percent() : last_printing_status ? 100 : 0;
      if (percent_done != last_percent_done) {
        char message_buffer[16];
        sprintf_P(message_buffer, PSTR("{TQ:%03i}"), percent_done);
        write_to_lcd(message_buffer);
        last_percent_done = percent_done;
        last_printing_status = ExtUI::isPrinting();
      }
    #endif
  }

  void onCNCKilled(FSTR_P const error, FSTR_P const component) {
    set_lcd_error(error, component);
  }

  #if HAS_PID_HEATING

    void onPidTuning(const result_t rst) {
      // Called for temperature PID tuning result
      //SERIAL_ECHOLNPGM("OnPidTuning:", rst);
      switch (rst) {
        case PID_STARTED:
          set_lcd_error(GET_TEXT_F(MSG_PID_AUTOTUNE));
          break;
        case PID_BAD_EXTRUDER_NUM:
          set_lcd_error(GET_TEXT_F(MSG_PID_BAD_EXTRUDER_NUM));
          break;
        case PID_TEMP_TOO_HIGH:
          set_lcd_error(GET_TEXT_F(MSG_PID_TEMP_TOO_HIGH));
          break;
        case PID_TUNING_TIMEOUT:
          set_lcd_error(GET_TEXT_F(MSG_PID_TIMEOUT));
          break;
        case PID_DONE:
          set_lcd_error(GET_TEXT_F(MSG_PID_AUTOTUNE_DONE));
          break;
      }
    }

  #endif

  void onPrintTimerStarted() { write_to_lcd(F("{SYS:BUILD}")); }
  void onPrintTimerPaused() {}
  void onPrintTimerStopped() { write_to_lcd(F("{TQ:100}")); }

  // Not needed for Malyan LCD
  void onStatusChanged(const char * const) {}
  void onMediaInserted() {}
  void onMediaError() {}
  void onMediaRemoved() {}
  void onPlayTone(const uint16_t, const uint16_t) {}
  void onFilamentRunout(const extruder_t extruder) {}
  void onUserConfirmRequired(const char * const) {}
  void onHomingStart() {}
  void onHomingComplete() {}
  void onPrintFinished() {}
  void onFactoryReset() {}
  void onStoreSettings(char*) {}
  void onLoadSettings(const char*) {}
  void onPostprocessSettings() {}
  void onConfigurationStoreWritten(bool) {}
  void onConfigurationStoreRead(bool) {}

  #if HAS_MESH
    void onMeshLevelingStart() {}
    void onMeshUpdate(const int8_t xpos, const int8_t ypos, const_float_t zval) {}
    void onMeshUpdate(const int8_t xpos, const int8_t ypos, const ExtUI::probe_state_t state) {}
  #endif

  #if ENABLED(POWER_LOSS_RECOVERY)
    void onPowerLossResume() {}
  #endif

  void onSteppersDisabled() {}
  void onSteppersEnabled()  {}
}

#endif // MALYAN_LCD
