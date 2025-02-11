/**
 * Modern Vintage CNC Firmware
*/

#include "../../../inc/mvCNCConfigPre.h"

#if HAS_TFT_LVGL_UI

#include "draw_ui.h"
#include <lv_conf.h>

#include "../../../module/temperature.h"
#include "../../../gcode/queue.h"
#include "../../../gcode/gcode.h"
#include "../../../inc/mvCNCConfig.h"

extern lv_group_t *g;
static lv_obj_t *scr, *fanText;

enum {
  ID_F_ADD = 1,
  ID_F_DEC,
  ID_F_HIGH,
  ID_F_MID,
  ID_F_OFF,
  ID_F_RETURN
};

uint8_t fanPercent = 0;
static void event_handler(lv_obj_t *obj, lv_event_t event) {
  if (event != LV_EVENT_RELEASED) return;
  const uint8_t temp = map(thermalManager.fan_speed[0], 0, 255, 0, 100);
  if (abs(fanPercent - temp) > 2) fanPercent = temp;
  switch (obj->mks_obj_id) {
    case ID_F_ADD: if (fanPercent < 100) fanPercent++; break;
    case ID_F_DEC: if (fanPercent !=  0) fanPercent--; break;
    case ID_F_HIGH: fanPercent = 100; break;
    case ID_F_MID:  fanPercent =  50; break;
    case ID_F_OFF:  fanPercent =   0; break;
    case ID_F_RETURN: goto_previous_ui(); return;
  }
  thermalManager.set_fan_speed(0, map(fanPercent, 0, 100, 0, 255));
  if (obj->mks_obj_id != ID_F_RETURN) disp_fan_value();
}

void lv_draw_fan() {
  lv_obj_t *buttonAdd;

  scr = lv_screen_create(FAN_UI);
  // Create an Image button
  buttonAdd = lv_big_button_create(scr, "F:/bmp_Add.bin", fan_menu.add, INTERVAL_V, titleHeight, event_handler, ID_F_ADD);
  lv_obj_clear_protect(buttonAdd, LV_PROTECT_FOLLOW);
  lv_big_button_create(scr, "F:/bmp_Dec.bin", fan_menu.dec, BTN_X_PIXEL * 3 + INTERVAL_V * 4, titleHeight, event_handler, ID_F_DEC);
  lv_big_button_create(scr, "F:/bmp_speed255.bin", fan_menu.full, INTERVAL_V, BTN_Y_PIXEL + INTERVAL_H + titleHeight, event_handler, ID_F_HIGH);
  lv_big_button_create(scr, "F:/bmp_speed127.bin", fan_menu.half, BTN_X_PIXEL + INTERVAL_V * 2, BTN_Y_PIXEL + INTERVAL_H + titleHeight, event_handler, ID_F_MID);
  lv_big_button_create(scr, "F:/bmp_speed0.bin", fan_menu.off, BTN_X_PIXEL * 2 + INTERVAL_V * 3, BTN_Y_PIXEL + INTERVAL_H + titleHeight, event_handler, ID_F_OFF);
  lv_big_button_create(scr, "F:/bmp_return.bin", common_menu.text_back, BTN_X_PIXEL * 3 + INTERVAL_V * 4, BTN_Y_PIXEL + INTERVAL_H + titleHeight, event_handler, ID_F_RETURN);

  fanText = lv_label_create_empty(scr);
  lv_obj_set_style(fanText, &tft_style_label_rel);
  disp_fan_value();
}

void disp_fan_value() {
  #if HAS_FAN
    sprintf_P(public_buf_l, PSTR("%s: %3d%%"), fan_menu.state, fanPercent);
  #else
    sprintf_P(public_buf_l, PSTR("%s: ---"), fan_menu.state);
  #endif
  lv_label_set_text(fanText, public_buf_l);
  lv_obj_align(fanText, nullptr, LV_ALIGN_CENTER, 0, -65);
}

void lv_clear_fan() {
  #if HAS_ROTARY_ENCODER
    if (gCfgItems.encoder_enable) lv_group_remove_all_objs(g);
  #endif
  lv_obj_del(scr);
}

#endif // HAS_TFT_LVGL_UI
