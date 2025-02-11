/**
 * Modern Vintage CNC Firmware
*/

#include "../../../inc/mvCNCConfigPre.h"

#if HAS_ETHERNET

#include "../../../feature/ethernet.h"
#include "../../../core/serial.h"
#include "../../gcode.h"

void say_ethernet() { SERIAL_ECHOPGM("  Ethernet "); }

void ETH0_report() {
  say_ethernet();
  SERIAL_ECHO_TERNARY(ethernet.hardware_enabled, "port ", "en", "dis", "abled.\n");
  if (ethernet.hardware_enabled) {
    say_ethernet();
    SERIAL_ECHO_TERNARY(ethernet.have_telnet_client, "client ", "en", "dis", "abled.\n");
  }
  else
    SERIAL_ECHOLNPGM("Send 'M552 S1' to enable.");
}

void MAC_report() {
  uint8_t mac[6];
  if (ethernet.hardware_enabled) {
    Ethernet.MACAddress(mac);
    SERIAL_ECHOPGM("  MAC: ");
    LOOP_L_N(i, 6) {
      if (mac[i] < 16) SERIAL_CHAR('0');
      SERIAL_PRINT(mac[i], PrintBase::Hex);
      if (i < 5) SERIAL_CHAR(':');
    }
  }
  SERIAL_EOL();
}

// Display current values when the link is active,
// otherwise show the stored values
void ip_report(const uint16_t cmd, FSTR_P const post, const IPAddress &ipo) {
  SERIAL_CHAR('M'); SERIAL_ECHO(cmd); SERIAL_CHAR(' ');
  LOOP_L_N(i, 4) {
    SERIAL_ECHO(ipo[i]);
    if (i < 3) SERIAL_CHAR('.');
  }
  SERIAL_ECHOPGM(" ; ");
  SERIAL_ECHOLNF(post);
}

/**
 * M552: Set IP address, enable/disable network interface
 *
 *  S0   : disable networking
 *  S1   : enable networking
 *  S-1  : reset network interface
 *
 *  Pnnn : Set IP address, 0.0.0.0 means acquire an IP address using DHCP
 */
void GcodeSuite::M552() {
  const bool seenP = parser.seenval('P');
  if (seenP) ethernet.ip.fromString(parser.value_string());

  const bool seenS = parser.seenval('S');
  if (seenS) {
    switch (parser.value_int()) {
      case -1:
        if (ethernet.telnetClient) ethernet.telnetClient.stop();
        ethernet.init();
        break;
      case 0: ethernet.hardware_enabled = false; break;
      case 1: ethernet.hardware_enabled = true; break;
      default: break;
    }
  }
  const bool nopar = !seenS && !seenP;
  if (nopar || seenS) ETH0_report();
  if (nopar || seenP) M552_report();
}

void GcodeSuite::M552_report() {
  ip_report(552, F("ip address"), Ethernet.linkStatus() == LinkON ? Ethernet.localIP() : ethernet.ip);
}

/**
 * M553 Pnnn - Set netmask
 */
void GcodeSuite::M553() {
  if (parser.seenval('P'))
    ethernet.subnet.fromString(parser.value_string());
  else
    M553_report();
}

void GcodeSuite::M553_report() {
  ip_report(553, F("subnet mask"), Ethernet.linkStatus() == LinkON ? Ethernet.subnetMask() : ethernet.subnet);
}

/**
 * M554 Pnnn - Set Gateway
 */
void GcodeSuite::M554() {
  if (parser.seenval('P'))
    ethernet.gateway.fromString(parser.value_string());
  else
    M554_report();
}

void GcodeSuite::M554_report() {
  ip_report(554, F("gateway"), Ethernet.linkStatus() == LinkON ? Ethernet.gatewayIP() : ethernet.gateway);
}

#endif // HAS_ETHERNET
