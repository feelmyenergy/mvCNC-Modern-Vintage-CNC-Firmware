/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * Rapide Lite 200 v1 (RUMBA clone) pin assignments. Has slightly different assignment for
 * extruder motors due to dual Z motors. Pinout therefore based on pins_RUMBA.h.
 */

#define BOARD_INFO_NAME "RL200"
#define DEFAULT_MACHINE_NAME "Rapide Lite 200"

#if HOTENDS > 2 || E_STEPPERS > 2
  #error "RL200v1 supports up to 2 hotends / E-steppers. Comment out this line to continue."
#elif NUM_Z_STEPPER_DRIVERS != 2
  #error "RL200 uses dual Z stepper motors. Set NUM_Z_STEPPER_DRIVERS to 2 or comment out this line to continue."
#elif !(AXIS_DRIVER_TYPE_X(DRV8825) && AXIS_DRIVER_TYPE_Y(DRV8825) && AXIS_DRIVER_TYPE_Z(DRV8825) && AXIS_DRIVER_TYPE_Z2(DRV8825) && AXIS_DRIVER_TYPE_E0(DRV8825))
  #error "You must set ([XYZ]|Z2|E0)_DRIVER_TYPE to DRV8825 in Configuration.h for RL200."
#endif

#define E0_STEP_PIN                           26  // (RUMBA E1 pins)
#define E0_DIR_PIN                            25
#define E0_ENABLE_PIN                         27

#define E1_STEP_PIN                           29  // (RUMBA E2 pins)
#define E1_DIR_PIN                            28
#define E1_ENABLE_PIN                         39

#define Z2_STEP_PIN                           23  // (RUMBA E0 pins)
#define Z2_DIR_PIN                            22
#define Z2_ENABLE_PIN                         24

#include "pins_RUMBA.h"
