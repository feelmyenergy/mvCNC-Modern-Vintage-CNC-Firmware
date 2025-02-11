/**
 * Modern Vintage CNC Firmware
*/

/**
 * M421.cpp - Auto Bed Leveling
 */

#include "../../../inc/mvCNCConfig.h"

#if ENABLED(AUTO_BED_LEVELING_BILINEAR)

#include "../../gcode.h"
#include "../../../feature/bedlevel/bedlevel.h"

#if ENABLED(EXTENSIBLE_UI)
  #include "../../../lcd/extui/ui_api.h"
#endif

/**
 * M421: Set one or more Mesh Bed Leveling Z coordinates
 *
 * Usage:
 *   M421 I<xindex> J<yindex> Z<linear>
 *   M421 I<xindex> J<yindex> Q<offset>
 *
 *  - If I is omitted, set the entire row
 *  - If J is omitted, set the entire column
 *  - If both I and J are omitted, set all
 */
void GcodeSuite::M421() {
  int8_t ix = parser.intval('I', -1), iy = parser.intval('J', -1);
  const bool hasZ = parser.seenval('Z'),
             hasQ = !hasZ && parser.seenval('Q');

  if (hasZ || hasQ) {
    if (WITHIN(ix, -1, GRID_MAX_POINTS_X - 1) && WITHIN(iy, -1, GRID_MAX_POINTS_Y - 1)) {
      const float zval = parser.value_linear_units();
      uint8_t sx = ix >= 0 ? ix : 0, ex = ix >= 0 ? ix : GRID_MAX_POINTS_X - 1,
              sy = iy >= 0 ? iy : 0, ey = iy >= 0 ? iy : GRID_MAX_POINTS_Y - 1;
      LOOP_S_LE_N(x, sx, ex) {
        LOOP_S_LE_N(y, sy, ey) {
          z_values[x][y] = zval + (hasQ ? z_values[x][y] : 0);
          TERN_(EXTENSIBLE_UI, ExtUI::onMeshUpdate(x, y, z_values[x][y]));
        }
      }
      TERN_(ABL_BILINEAR_SUBDIVISION, bed_level_virt_interpolate());
    }
    else
      SERIAL_ERROR_MSG(STR_ERR_MESH_XY);
  }
  else
    SERIAL_ERROR_MSG(STR_ERR_M421_PARAMETERS);
}

#endif // AUTO_BED_LEVELING_BILINEAR
