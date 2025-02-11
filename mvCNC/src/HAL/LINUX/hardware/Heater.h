/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "Gpio.h"

struct LowpassFilter {
  uint64_t data_delay = 0;
  uint16_t update(uint16_t value) {
    data_delay = data_delay - (data_delay >> 6) + value;
    return (uint16_t)(data_delay >> 6);
  }
};

class Heater: public Peripheral {
public:
  Heater(pin_t heater, pin_t adc);
  virtual ~Heater();
  void interrupt(GpioEvent ev);
  void update();

  pin_t heater_pin, adc_pin;
  uint16_t room_temp_raw;
  uint16_t heater_state;
  LowpassFilter pwmcap;
  double heat;
  uint64_t last;
};
