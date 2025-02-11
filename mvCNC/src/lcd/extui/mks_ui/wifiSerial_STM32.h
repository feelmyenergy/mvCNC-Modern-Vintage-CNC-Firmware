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

#include <inttypes.h>
#include "Stream.h"
#include "uart.h"

class WifiSerial {
  protected:
    // Has any byte been written to the UART since begin()
    bool _written;
    serial_t _serial;
  public:
    uint8_t wifiRxBuf[WIFI_RX_BUF_SIZE];
    uint8_t wifiTxBuf[WIFI_TX_BUF_SIZE];
    WifiSerial(void *peripheral);

    // Set up / tear down
    void begin(uint32_t baud);
    void begin(uint32_t baud, uint8_t config);
    void end();
    int available();
    int read();
    int write(uint8_t);

    // Interrupt handlers
    static int _tx_complete_irq(serial_t *obj);
    static void _rx_complete_irq(serial_t *obj);

    void flush();
    bool isHalfDuplex() const;
    void enableHalfDuplexRx();

  private:
    void setRx(uint32_t _rx);
    void setTx(uint32_t _tx);
    void setRx(PinName _rx);
    void setTx(PinName _tx);
    void init(PinName _rx, PinName _tx);
    bool _rx_enabled;
    uint8_t _config;
    unsigned long _baud;
};
