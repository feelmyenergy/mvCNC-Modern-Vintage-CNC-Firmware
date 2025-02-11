/**
 * Modern Vintage CNC Firmware
*/
#pragma once

// R25 = 100 kOhm, beta25 = 4092 K, 8.2 kOhm pull-up, 100k Epcos (?) thermistor
constexpr temp_entry_t temptable_6[] PROGMEM = {
  { OV(   1), 350 },
  { OV(  28), 250 }, // top rating 250C
  { OV(  31), 245 },
  { OV(  35), 240 },
  { OV(  39), 235 },
  { OV(  42), 230 },
  { OV(  44), 225 },
  { OV(  49), 220 },
  { OV(  53), 215 },
  { OV(  62), 210 },
  { OV(  71), 205 }, // fitted graphically
  { OV(  78), 200 }, // fitted graphically
  { OV(  94), 190 },
  { OV( 102), 185 },
  { OV( 116), 170 },
  { OV( 143), 160 },
  { OV( 183), 150 },
  { OV( 223), 140 },
  { OV( 270), 130 },
  { OV( 318), 120 },
  { OV( 383), 110 },
  { OV( 413), 105 },
  { OV( 439), 100 },
  { OV( 484),  95 },
  { OV( 513),  90 },
  { OV( 607),  80 },
  { OV( 664),  70 },
  { OV( 781),  60 },
  { OV( 810),  55 },
  { OV( 849),  50 },
  { OV( 914),  45 },
  { OV( 914),  40 },
  { OV( 935),  35 },
  { OV( 954),  30 },
  { OV( 970),  25 },
  { OV( 978),  22 },
  { OV(1008),   3 },
  { OV(1023),   0 } // to allow internal 0 degrees C
};
