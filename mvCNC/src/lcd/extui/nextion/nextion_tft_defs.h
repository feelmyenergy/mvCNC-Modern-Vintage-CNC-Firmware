/**
 * Modern Vintage CNC Firmware
 * Copyright (c) 2021 mvCNCFirmware [https://github.com/Domush/Webber-Ranch-CNC-Firmware]
 *
 * Based on Marlin and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

/* ****************************************
 * lcd/extui/nextion/nextion_tft_defs.h
 * ****************************************
 * Extensible_UI implementation for Nextion
 * https://github.com/Skorpi08
 * ***************************************/

#include "../../../inc/mvCNCConfigPre.h"

//#define NEXDEBUGLEVEL 255
#if NEXDEBUGLEVEL
  // Bit-masks for selective debug:
  enum NexDebugMask : uint8_t {
    N_INFO   = _BV(0),
    N_ACTION = _BV(1),
    N_FILE   = _BV(2),
    N_PANEL  = _BV(3),
    N_mvCNC = _BV(4),
    N_SOME   = _BV(5),
    N_ALL    = _BV(6)
  };
  #define NEXDEBUG(M) (((M) & NEXDEBUGLEVEL) == M)  // Debug flag macro
#else
  #define NEXDEBUG(M) false
#endif

#define MAX_FOLDER_DEPTH                4    // Limit folder depth TFT has a limit for the file path
#define MAX_CMND_LEN                   16 * MAX_FOLDER_DEPTH // Maximum Length for a Panel command
#define MAX_PATH_LEN                   16 * MAX_FOLDER_DEPTH // Maximum number of characters in a SD file path

 // TFT panel commands
#define  msg_welcome                MACHINE_NAME " Ready."

#define SEND_TEMP(x,y,t,z)  (nextion.SendtoTFT(F(x)), nextion.SendtoTFT(F(".txt=\"")), LCD_SERIAL.print(y), nextion.SendtoTFT(F(t)), LCD_SERIAL.print(z), nextion.SendtoTFT(F("\"\xFF\xFF\xFF")))
#define SEND_VAL(x,y)       (nextion.SendtoTFT(F(x)), nextion.SendtoTFT(F(".val=")),   LCD_SERIAL.print(y), nextion.SendtoTFT(F("\xFF\xFF\xFF")))
#define SEND_TXT(x,y)       (nextion.SendtoTFT(F(x)), nextion.SendtoTFT(F(".txt=\"")), nextion.SendtoTFT(F(y)), nextion.SendtoTFT(F("\"\xFF\xFF\xFF")))
#define SEND_TXT_F(x,y)     (nextion.SendtoTFT(F(x)), nextion.SendtoTFT(F(".txt=\"")), nextion.SendtoTFT(y), nextion.SendtoTFT(F("\"\xFF\xFF\xFF")))
#define SEND_VALasTXT(x,y)  (nextion.SendtoTFT(F(x)), nextion.SendtoTFT(F(".txt=\"")), LCD_SERIAL.print(y), nextion.SendtoTFT(F("\"\xFF\xFF\xFF")))
#define SEND_TXT_END(x)     (nextion.SendtoTFT(F(x)), nextion.SendtoTFT(F("\xFF\xFF\xFF")))
#define SEND_PCO2(x,y,z)    (nextion.SendtoTFT(F(x)), LCD_SERIAL.print(y), nextion.SendtoTFT(F(".pco=")), nextion.SendtoTFT(F(z)), nextion.SendtoTFT(F("\xFF\xFF\xFF")))
