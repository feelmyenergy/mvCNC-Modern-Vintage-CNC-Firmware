/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "../../../inc/mvCNCConfig.h"

enum MeshLevelingState : char {
  MeshReport,     // G29 S0
  MeshStart,      // G29 S1
  MeshNext,       // G29 S2
  MeshSet,        // G29 S3
  MeshSetZOffset, // G29 S4
  MeshReset       // G29 S5
};

#define MESH_X_DIST (float(MESH_MAX_X - (MESH_MIN_X)) / (GRID_MAX_CELLS_X))
#define MESH_Y_DIST (float(MESH_MAX_Y - (MESH_MIN_Y)) / (GRID_MAX_CELLS_Y))
#define _GET_MESH_X(I) mbl.index_to_xpos[I]
#define _GET_MESH_Y(J) mbl.index_to_ypos[J]
#define Z_VALUES_ARR mbl.z_values

class mesh_bed_leveling {
public:
  static float z_offset,
               z_values[GRID_MAX_POINTS_X][GRID_MAX_POINTS_Y],
               index_to_xpos[GRID_MAX_POINTS_X],
               index_to_ypos[GRID_MAX_POINTS_Y];

  mesh_bed_leveling();

  static void report_mesh();

  static void reset();

  FORCE_INLINE static bool has_mesh() {
    GRID_LOOP(x, y) if (z_values[x][y]) return true;
    return false;
  }

  static void set_z(const int8_t px, const int8_t py, const_float_t z) { z_values[px][py] = z; }

  static void zigzag(const int8_t index, int8_t &px, int8_t &py) {
    px = index % (GRID_MAX_POINTS_X);
    py = index / (GRID_MAX_POINTS_X);
    if (py & 1) px = (GRID_MAX_POINTS_X) - 1 - px; // Zig zag
  }

  static void set_zigzag_z(const int8_t index, const_float_t z) {
    int8_t px, py;
    zigzag(index, px, py);
    set_z(px, py, z);
  }

  static int8_t cell_index_x(const_float_t x) {
    int8_t cx = (x - (MESH_MIN_X)) * RECIPROCAL(MESH_X_DIST);
    return constrain(cx, 0, GRID_MAX_CELLS_X - 1);
  }
  static int8_t cell_index_y(const_float_t y) {
    int8_t cy = (y - (MESH_MIN_Y)) * RECIPROCAL(MESH_Y_DIST);
    return constrain(cy, 0, GRID_MAX_CELLS_Y - 1);
  }
  static xy_int8_t cell_indexes(const_float_t x, const_float_t y) {
    return { cell_index_x(x), cell_index_y(y) };
  }
  static xy_int8_t cell_indexes(const xy_pos_t &xy) { return cell_indexes(xy.x, xy.y); }

  static int8_t probe_index_x(const_float_t x) {
    int8_t px = (x - (MESH_MIN_X) + 0.5f * (MESH_X_DIST)) * RECIPROCAL(MESH_X_DIST);
    return WITHIN(px, 0, (GRID_MAX_POINTS_X) - 1) ? px : -1;
  }
  static int8_t probe_index_y(const_float_t y) {
    int8_t py = (y - (MESH_MIN_Y) + 0.5f * (MESH_Y_DIST)) * RECIPROCAL(MESH_Y_DIST);
    return WITHIN(py, 0, (GRID_MAX_POINTS_Y) - 1) ? py : -1;
  }
  static xy_int8_t probe_indexes(const_float_t x, const_float_t y) {
    return { probe_index_x(x), probe_index_y(y) };
  }
  static xy_int8_t probe_indexes(const xy_pos_t &xy) { return probe_indexes(xy.x, xy.y); }

  static float calc_z0(const_float_t a0, const_float_t a1, const_float_t z1, const_float_t a2, const_float_t z2) {
    const float delta_z = (z2 - z1) / (a2 - a1),
                delta_a = a0 - a1;
    return z1 + delta_a * delta_z;
  }

  static float get_z(const xy_pos_t &pos
    OPTARG(ENABLE_LEVELING_FADE_HEIGHT, const_float_t factor=1.0f)
  ) {
    #if DISABLED(ENABLE_LEVELING_FADE_HEIGHT)
      constexpr float factor = 1.0f;
    #endif
    const xy_int8_t ind = cell_indexes(pos);
    const float x1 = index_to_xpos[ind.x], x2 = index_to_xpos[ind.x+1],
                y1 = index_to_xpos[ind.y], y2 = index_to_xpos[ind.y+1],
                z1 = calc_z0(pos.x, x1, z_values[ind.x][ind.y  ], x2, z_values[ind.x+1][ind.y  ]),
                z2 = calc_z0(pos.x, x1, z_values[ind.x][ind.y+1], x2, z_values[ind.x+1][ind.y+1]),
                zf = calc_z0(pos.y, y1, z1, y2, z2);

    return z_offset + zf * factor;
  }

  #if IS_CARTESIAN && DISABLED(SEGMENT_LEVELED_MOVES)
    static void line_to_destination(const_feedRate_t scaled_fr_mm_s, uint8_t x_splits=0xFF, uint8_t y_splits=0xFF);
  #endif
};

extern mesh_bed_leveling mbl;
