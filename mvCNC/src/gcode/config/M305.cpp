/**
 * Modern Vintage CNC Firmware
*/

#include "../../inc/mvCNCConfig.h"

#if HAS_USER_THERMISTORS

#include "../gcode.h"
#include "../../module/temperature.h"

/**
 * M305: Set (or report) custom thermistor parameters
 *
 *   P[index]  Thermistor table index
 *   R[ohms]   Pullup resistor value
 *   T[ohms]   Resistance at 25C
 *   B[beta]   Thermistor "beta" value
 *   C[coeff]  Steinhart-Hart Coefficient 'C'
 *
 *   Format: M305 P[tbl_index] R[pullup_resistor_val] T[therm_25C_resistance] B[therm_beta] C[Steinhart_Hart_C_coeff]
 *
 * Examples: M305 P0 R4700 T100000 B3950 C0.0
 *           M305 P0 R4700
 *           M305 P0 T100000
 *           M305 P0 B3950
 *           M305 P0 C0.0
 */
void GcodeSuite::M305() {
  const int8_t t_index = parser.intval('P', -1);
  const bool do_set = parser.seen("BCRT");

  // A valid P index is required
  if (t_index >= (USER_THERMISTORS) || (do_set && t_index < 0))
    SERIAL_ECHO_MSG("!Invalid index. (0 <= P <= ", USER_THERMISTORS - 1, ")");
  else if (do_set) {
    if (parser.seen('R')) // Pullup resistor value
      if (!thermalManager.set_pull_up_res(t_index, parser.value_float()))
        SERIAL_ECHO_MSG("!Invalid series resistance. (0 < R < 1000000)");

    if (parser.seen('T')) // Resistance at 25C
      if (!thermalManager.set_res25(t_index, parser.value_float()))
        SERIAL_ECHO_MSG("!Invalid 25C resistance. (0 < T < 10000000)");

    if (parser.seen('B')) // Beta value
      if (!thermalManager.set_beta(t_index, parser.value_float()))
        SERIAL_ECHO_MSG("!Invalid beta. (0 < B < 1000000)");

    if (parser.seen('C')) // Steinhart-Hart C coefficient
      if (!thermalManager.set_sh_coeff(t_index, parser.value_float()))
        SERIAL_ECHO_MSG("!Invalid Steinhart-Hart C coeff. (-0.01 < C < +0.01)");
  }                       // If not setting then report parameters
  else if (t_index < 0) { // ...all user thermistors
    LOOP_L_N(i, USER_THERMISTORS)
      thermalManager.M305_report(i);
  }
  else                    // ...one user thermistor
    thermalManager.M305_report(t_index);
}

#endif // HAS_USER_THERMISTORS
