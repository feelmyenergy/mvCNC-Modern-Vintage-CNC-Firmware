/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * stepper/L64xx.h
 * Stepper driver indirection for L64XX drivers
 */

#include "../../inc/mvCNCConfig.h"
#include "../../libs/L64XX/L64XX_mvCNC.h"

// Convert option names to L64XX classes
#define CLASS_L6470       L6470
#define CLASS_L6474       L6474
#define CLASS_POWERSTEP01 powerSTEP01

#define __L64XX_CLASS(TYPE) CLASS_##TYPE
#define _L64XX_CLASS(TYPE)  __L64XX_CLASS(TYPE)
#define L64XX_CLASS(ST)     _L64XX_CLASS(ST##_DRIVER_TYPE)

#define L6474_DIR_WRITE(A,STATE) do{ L64xxManager.dir_commands[A] = dSPIN_L6474_ENABLE; WRITE(A##_DIR_PIN, STATE); }while(0)
#define L64XX_DIR_WRITE(A,STATE) do{ L64xxManager.dir_commands[A] = (STATE) ? dSPIN_STEP_CLOCK_REV : dSPIN_STEP_CLOCK_FWD; }while(0)

// X Stepper
#if AXIS_IS_L64XX(X)
  extern L64XX_CLASS(X)         stepperX;
  #define X_ENABLE_INIT()       NOOP
  #define X_ENABLE_WRITE(STATE) (STATE ? stepperX.hardStop() : stepperX.free())
  #define X_ENABLE_READ()       (stepperX.getStatus() & STATUS_HIZ)
  #if AXIS_DRIVER_TYPE_X(L6474)
    #define X_DIR_INIT()        SET_OUTPUT(X_DIR_PIN)
    #define X_DIR_WRITE(STATE)  L6474_DIR_WRITE(X, STATE)
    #define X_DIR_READ()        READ(X_DIR_PIN)
  #else
    #define X_DIR_INIT()        NOOP
    #define X_DIR_WRITE(STATE)  L64XX_DIR_WRITE(X, STATE)
    #define X_DIR_READ()        (stepper##X.getStatus() & STATUS_DIR);
    #if AXIS_DRIVER_TYPE_X(L6470)
      #define DISABLE_STEPPER_X() stepperX.free()
    #endif
  #endif
#endif

// Y Stepper
#if AXIS_IS_L64XX(Y)
  extern L64XX_CLASS(Y)         stepperY;
  #define Y_ENABLE_INIT()       NOOP
  #define Y_ENABLE_WRITE(STATE) (STATE ? stepperY.hardStop() : stepperY.free())
  #define Y_ENABLE_READ()       (stepperY.getStatus() & STATUS_HIZ)
  #if AXIS_DRIVER_TYPE_Y(L6474)
    #define Y_DIR_INIT()        SET_OUTPUT(Y_DIR_PIN)
    #define Y_DIR_WRITE(STATE)  L6474_DIR_WRITE(Y, STATE)
    #define Y_DIR_READ()        READ(Y_DIR_PIN)
  #else
    #define Y_DIR_INIT()        NOOP
    #define Y_DIR_WRITE(STATE)  L64XX_DIR_WRITE(Y, STATE)
    #define Y_DIR_READ()        (stepper##Y.getStatus() & STATUS_DIR);
    #if AXIS_DRIVER_TYPE_Y(L6470)
      #define DISABLE_STEPPER_Y() stepperY.free()
    #endif
  #endif
#endif

// Z Stepper
#if AXIS_IS_L64XX(Z)
  extern L64XX_CLASS(Z)         stepperZ;
  #define Z_ENABLE_INIT()       NOOP
  #define Z_ENABLE_WRITE(STATE) (STATE ? stepperZ.hardStop() : stepperZ.free())
  #define Z_ENABLE_READ()       (stepperZ.getStatus() & STATUS_HIZ)
  #if AXIS_DRIVER_TYPE_Z(L6474)
    #define Z_DIR_INIT()        SET_OUTPUT(Z_DIR_PIN)
    #define Z_DIR_WRITE(STATE)  L6474_DIR_WRITE(Z, STATE)
    #define Z_DIR_READ()        READ(Z_DIR_PIN)
  #else
    #define Z_DIR_INIT()        NOOP
    #define Z_DIR_WRITE(STATE)  L64XX_DIR_WRITE(Z, STATE)
    #define Z_DIR_READ()        (stepper##Z.getStatus() & STATUS_DIR);
    #if AXIS_DRIVER_TYPE_Z(L6470)
      #define DISABLE_STEPPER_Z() stepperZ.free()
    #endif
  #endif
#endif

// X2 Stepper
#if HAS_X2_ENABLE && AXIS_IS_L64XX(X2)
  extern L64XX_CLASS(X2)         stepperX2;
  #define X2_ENABLE_INIT()       NOOP
  #define X2_ENABLE_WRITE(STATE) (STATE ? stepperX2.hardStop() : stepperX2.free())
  #define X2_ENABLE_READ()       (stepperX2.getStatus() & STATUS_HIZ)
  #if AXIS_DRIVER_TYPE_X2(L6474)
    #define X2_DIR_INIT()        SET_OUTPUT(X2_DIR_PIN)
    #define X2_DIR_WRITE(STATE)  L6474_DIR_WRITE(X2, STATE)
    #define X2_DIR_READ()        READ(X2_DIR_PIN)
  #else
    #define X2_DIR_INIT()        NOOP
    #define X2_DIR_WRITE(STATE)  L64XX_DIR_WRITE(X2, STATE)
    #define X2_DIR_READ()        (stepper##X2.getStatus() & STATUS_DIR);
  #endif
#endif

#if AXIS_DRIVER_TYPE_X2(L6470)
  #define DISABLE_STEPPER_X2() stepperX2.free()
#endif

// Y2 Stepper
#if HAS_Y2_ENABLE && AXIS_IS_L64XX(Y2)
  extern L64XX_CLASS(Y2)         stepperY2;
  #define Y2_ENABLE_INIT()       NOOP
  #define Y2_ENABLE_WRITE(STATE) (STATE ? stepperY2.hardStop() : stepperY2.free())
  #define Y2_ENABLE_READ()       (stepperY2.getStatus() & STATUS_HIZ)
  #if AXIS_DRIVER_TYPE_Y2(L6474)
    #define Y2_DIR_INIT()        SET_OUTPUT(Y2_DIR_PIN)
    #define Y2_DIR_WRITE(STATE)  L6474_DIR_WRITE(Y2, STATE)
    #define Y2_DIR_READ()        READ(Y2_DIR_PIN)
  #else
    #define Y2_DIR_INIT()        NOOP
    #define Y2_DIR_WRITE(STATE)  L64XX_DIR_WRITE(Y2, STATE)
    #define Y2_DIR_READ()        (stepper##Y2.getStatus() & STATUS_DIR);
  #endif
#endif

#if AXIS_DRIVER_TYPE_Y2(L6470)
  #define DISABLE_STEPPER_Y2() stepperY2.free()
#endif

// Z2 Stepper
#if HAS_Z2_ENABLE && AXIS_IS_L64XX(Z2)
  extern L64XX_CLASS(Z2)         stepperZ2;
  #define Z2_ENABLE_INIT()       NOOP
  #define Z2_ENABLE_WRITE(STATE) (STATE ? stepperZ2.hardStop() : stepperZ2.free())
  #define Z2_ENABLE_READ()       (stepperZ2.getStatus() & STATUS_HIZ)
  #if AXIS_DRIVER_TYPE_Z2(L6474)
    #define Z2_DIR_INIT()        SET_OUTPUT(Z2_DIR_PIN)
    #define Z2_DIR_WRITE(STATE)  L6474_DIR_WRITE(Z2, STATE)
    #define Z2_DIR_READ()        READ(Z2_DIR_PIN)
  #else
    #define Z2_DIR_INIT()        NOOP
    #define Z2_DIR_WRITE(STATE)  L64XX_DIR_WRITE(Z2, STATE)
    #define Z2_DIR_READ()        (stepper##Z2.getStatus() & STATUS_DIR);
  #endif
#endif

#if AXIS_DRIVER_TYPE_Z2(L6470)
  #define DISABLE_STEPPER_Z2() stepperZ2.free()
#endif

// Z3 Stepper
#if HAS_Z3_ENABLE && AXIS_IS_L64XX(Z3)
  extern L64XX_CLASS(Z3)         stepperZ3;
  #define Z3_ENABLE_INIT()       NOOP
  #define Z3_ENABLE_WRITE(STATE) (STATE ? stepperZ3.hardStop() : stepperZ3.free())
  #define Z3_ENABLE_READ()       (stepperZ3.getStatus() & STATUS_HIZ)
  #if AXIS_DRIVER_TYPE_Z3(L6474)
    #define Z3_DIR_INIT()        SET_OUTPUT(Z3_DIR_PIN)
    #define Z3_DIR_WRITE(STATE)  L6474_DIR_WRITE(Z3, STATE)
    #define Z3_DIR_READ()        READ(Z3_DIR_PIN)
  #else
    #define Z3_DIR_INIT()        NOOP
    #define Z3_DIR_WRITE(STATE)  L64XX_DIR_WRITE(Z3, STATE)
    #define Z3_DIR_READ()        (stepper##Z3.getStatus() & STATUS_DIR);
  #endif
#endif

#if AXIS_DRIVER_TYPE_Z3(L6470)
  #define DISABLE_STEPPER_Z3() stepperZ3.free()
#endif

// Z4 Stepper
#if HAS_Z4_ENABLE && AXIS_IS_L64XX(Z4)
  extern L64XX_CLASS(Z4)         stepperZ4;
  #define Z4_ENABLE_INIT()       NOOP
  #define Z4_ENABLE_WRITE(STATE) (STATE ? stepperZ4.hardStop() : stepperZ4.free())
  #define Z4_ENABLE_READ()       (stepperZ4.getStatus() & STATUS_HIZ)
  #if AXIS_DRIVER_TYPE_Z4(L6474)
    #define Z4_DIR_INIT()        SET_OUTPUT(Z4_DIR_PIN)
    #define Z4_DIR_WRITE(STATE)  L6474_DIR_WRITE(Z4, STATE)
    #define Z4_DIR_READ()        READ(Z4_DIR_PIN)
  #else
    #define Z4_DIR_INIT()        NOOP
    #define Z4_DIR_WRITE(STATE)  L64XX_DIR_WRITE(Z4, STATE)
    #define Z4_DIR_READ()        (stepper##Z4.getStatus() & STATUS_DIR);
  #endif
#endif

#if AXIS_DRIVER_TYPE_Z4(L6470)
  #define DISABLE_STEPPER_Z4() stepperZ4.free()
#endif

// I Stepper
#if AXIS_IS_L64XX(I)
  extern L64XX_CLASS(I)         stepperI;
  #define I_ENABLE_INIT()       NOOP
  #define I_ENABLE_WRITE(STATE) (STATE ? stepperI.hardStop() : stepperI.free())
  #define I_ENABLE_READ()       (stepperI.getStatus() & STATUS_HIZ)
  #if AXIS_DRIVER_TYPE_I(L6474)
    #define I_DIR_INIT()        SET_OUTPUT(I_DIR_PIN)
    #define I_DIR_WRITE(STATE)  L6474_DIR_WRITE(I, STATE)
    #define I_DIR_READ()        READ(I_DIR_PIN)
  #else
    #define I_DIR_INIT()        NOOP
    #define I_DIR_WRITE(STATE)  L64XX_DIR_WRITE(I, STATE)
    #define I_DIR_READ()        (stepper##I.getStatus() & STATUS_DIR);
    #if AXIS_DRIVER_TYPE_I(L6470)
      #define DISABLE_STEPPER_I() stepperI.free()
    #endif
  #endif
#endif

// J Stepper
#if AXIS_IS_L64XX(J)
  extern L64XX_CLASS(J)         stepperJ;
  #define J_ENABLE_INIT()       NOOP
  #define J_ENABLE_WRITE(STATE) (STATE ? stepperJ.hardStop() : stepperJ.free())
  #define J_ENABLE_READ()       (stepperJ.getStatus() & STATUS_HIZ)
  #if AXIS_DRIVER_TYPE_J(L6474)
    #define J_DIR_INIT()        SET_OUTPUT(J_DIR_PIN)
    #define J_DIR_WRITE(STATE)  L6474_DIR_WRITE(J, STATE)
    #define J_DIR_READ()        READ(J_DIR_PIN)
  #else
    #define J_DIR_INIT()        NOOP
    #define J_DIR_WRITE(STATE)  L64XX_DIR_WRITE(J, STATE)
    #define J_DIR_READ()        (stepper##J.getStatus() & STATUS_DIR);
    #if AXIS_DRIVER_TYPE_J(L6470)
      #define DISABLE_STEPPER_J() stepperJ.free()
    #endif
  #endif
#endif

// K Stepper
#if AXIS_IS_L64XX(K)
  extern L64XX_CLASS(K)         stepperK;
  #define K_ENABLE_INIT()       NOOP
  #define K_ENABLE_WRITE(STATE) (STATE ? stepperK.hardStop() : stepperK.free())
  #define K_ENABLE_READ()       (stepperK.getStatus() & STATUS_HIZ)
  #if AXIS_DRIVER_TYPE_K(L6474)
    #define K_DIR_INIT()        SET_OUTPUT(K_DIR_PIN)
    #define K_DIR_WRITE(STATE)  L6474_DIR_WRITE(K, STATE)
    #define K_DIR_READ()        READ(K_DIR_PIN)
  #else
    #define K_DIR_INIT()        NOOP
    #define K_DIR_WRITE(STATE)  L64XX_DIR_WRITE(K, STATE)
    #define K_DIR_READ()        (stepper##K.getStatus() & STATUS_DIR);
    #if AXIS_DRIVER_TYPE_K(L6470)
      #define DISABLE_STEPPER_K() stepperK.free()
    #endif
  #endif
#endif

// E0 Stepper
#if AXIS_IS_L64XX(E0)
  extern L64XX_CLASS(E0)         stepperE0;
  #define E0_ENABLE_INIT()       NOOP
  #define E0_ENABLE_WRITE(STATE)  (STATE ? stepperE0.hardStop() : stepperE0.free())
  #define E0_ENABLE_READ()       (stepperE0.getStatus() & STATUS_HIZ)
  #if AXIS_DRIVER_TYPE_E0(L6474)
    #define E0_DIR_INIT()        SET_OUTPUT(E0_DIR_PIN)
    #define E0_DIR_WRITE(STATE)  L6474_DIR_WRITE(E0, STATE)
    #define E0_DIR_READ()        READ(E0_DIR_PIN)
  #else
    #define E0_DIR_INIT()        NOOP
    #define E0_DIR_WRITE(STATE)  L64XX_DIR_WRITE(E0, STATE)
    #define E0_DIR_READ()        (stepper##E0.getStatus() & STATUS_DIR);
    #if AXIS_DRIVER_TYPE_E0(L6470)
      #define DISABLE_STEPPER_E0() do{ stepperE0.free(); }while(0)
    #endif
  #endif
#endif

// E1 Stepper
#if AXIS_IS_L64XX(E1)
  extern L64XX_CLASS(E1)         stepperE1;
  #define E1_ENABLE_INIT()       NOOP
  #define E1_ENABLE_WRITE(STATE) (STATE ? stepperE1.hardStop() : stepperE1.free())
  #define E1_ENABLE_READ()       (stepperE1.getStatus() & STATUS_HIZ)
  #if AXIS_DRIVER_TYPE_E1(L6474)
    #define E1_DIR_INIT()        SET_OUTPUT(E1_DIR_PIN)
    #define E1_DIR_WRITE(STATE)  L6474_DIR_WRITE(E1, STATE)
    #define E1_DIR_READ()        READ(E1_DIR_PIN)
  #else
    #define E1_DIR_INIT()        NOOP
    #define E1_DIR_WRITE(STATE)  L64XX_DIR_WRITE(E1, STATE)
    #define E1_DIR_READ()        (stepper##E1.getStatus() & STATUS_DIR);
    #if AXIS_DRIVER_TYPE_E1(L6470)
      #define DISABLE_STEPPER_E1() do{ stepperE1.free(); }while(0)
    #endif
  #endif
#endif

// E2 Stepper
#if AXIS_IS_L64XX(E2)
  extern L64XX_CLASS(E2)         stepperE2;
  #define E2_ENABLE_INIT()       NOOP
  #define E2_ENABLE_WRITE(STATE) (STATE ? stepperE2.hardStop() : stepperE2.free())
  #define E2_ENABLE_READ()       (stepperE2.getStatus() & STATUS_HIZ)
  #if AXIS_DRIVER_TYPE_E2(L6474)
    #define E2_DIR_INIT()        SET_OUTPUT(E2_DIR_PIN)
    #define E2_DIR_WRITE(STATE)  L6474_DIR_WRITE(E2, STATE)
    #define E2_DIR_READ()        READ(E2_DIR_PIN)
  #else
    #define E2_DIR_INIT()        NOOP
    #define E2_DIR_WRITE(STATE)  L64XX_DIR_WRITE(E2, STATE)
    #define E2_DIR_READ()        (stepper##E2.getStatus() & STATUS_DIR);
    #if AXIS_DRIVER_TYPE_E2(L6470)
      #define DISABLE_STEPPER_E2() do{ stepperE2.free(); }while(0)
    #endif
  #endif
#endif

// E3 Stepper
#if AXIS_IS_L64XX(E3)
  extern L64XX_CLASS(E3)         stepperE3;
  #define E3_ENABLE_INIT()       NOOP
  #define E3_ENABLE_WRITE(STATE) (STATE ? stepperE3.hardStop() : stepperE3.free())
  #define E3_ENABLE_READ()       (stepperE3.getStatus() & STATUS_HIZ)
  #if AXIS_DRIVER_TYPE_E3(L6474)
    #define E3_DIR_INIT()        SET_OUTPUT(E3_DIR_PIN)
    #define E3_DIR_WRITE(STATE)  L6474_DIR_WRITE(E3, STATE)
    #define E3_DIR_READ()        READ(E3_DIR_PIN)
  #else
    #define E3_DIR_INIT()        NOOP
    #define E3_DIR_WRITE(STATE)  L64XX_DIR_WRITE(E3, STATE)
    #define E3_DIR_READ()        (stepper##E3.getStatus() & STATUS_DIR);
  #endif
#endif

// E4 Stepper
#if AXIS_IS_L64XX(E4)
  extern L64XX_CLASS(E4)         stepperE4;
  #define E4_ENABLE_INIT()       NOOP
  #define E4_ENABLE_WRITE(STATE) (STATE ? stepperE4.hardStop() : stepperE4.free())
  #define E4_ENABLE_READ()       (stepperE4.getStatus() & STATUS_HIZ)
  #if AXIS_DRIVER_TYPE_E4(L6474)
    #define E4_DIR_INIT()        SET_OUTPUT(E4_DIR_PIN)
    #define E4_DIR_WRITE(STATE)  L6474_DIR_WRITE(E4, STATE)
    #define E4_DIR_READ()        READ(E4_DIR_PIN)
  #else
    #define E4_DIR_INIT()        NOOP
    #define E4_DIR_WRITE(STATE)  L64XX_DIR_WRITE(E4, STATE)
    #define E4_DIR_READ()        (stepper##E4.getStatus() & STATUS_DIR);
    #if AXIS_DRIVER_TYPE_E4(L6470)
      #define DISABLE_STEPPER_E4() do{ stepperE4.free(); }while(0)
    #endif
  #endif
#endif

// E5 Stepper
#if AXIS_IS_L64XX(E5)
  extern L64XX_CLASS(E5)         stepperE5;
  #define E5_ENABLE_INIT()       NOOP
  #define E5_ENABLE_WRITE(STATE) (STATE ? stepperE5.hardStop() : stepperE5.free())
  #define E5_ENABLE_READ()       (stepperE5.getStatus() & STATUS_HIZ)
  #if AXIS_DRIVER_TYPE_E5(L6474)
    #define E5_DIR_INIT()        SET_OUTPUT(E5_DIR_PIN)
    #define E5_DIR_WRITE(STATE)  L6474_DIR_WRITE(E5, STATE)
    #define E5_DIR_READ()        READ(E5_DIR_PIN)
  #else
    #define E5_DIR_INIT()        NOOP
    #define E5_DIR_WRITE(STATE)  L64XX_DIR_WRITE(E5, STATE)
    #define E5_DIR_READ()        (stepper##E5.getStatus() & STATUS_DIR);
    #if AXIS_DRIVER_TYPE_E5(L6470)
      #define DISABLE_STEPPER_E5() do{ stepperE5.free(); }while(0)
    #endif
  #endif
#endif

// E6 Stepper
#if AXIS_IS_L64XX(E6)
  extern L64XX_CLASS(E6)         stepperE6;
  #define E6_ENABLE_INIT()       NOOP
  #define E6_ENABLE_WRITE(STATE) (STATE ? stepperE6.hardStop() : stepperE6.free())
  #define E6_ENABLE_READ()       (stepperE6.getStatus() & STATUS_HIZ)
  #if AXIS_DRIVER_TYPE_E6(L6474)
    #define E6_DIR_INIT()        SET_OUTPUT(E6_DIR_PIN)
    #define E6_DIR_WRITE(STATE)  L6474_DIR_WRITE(E6, STATE)
    #define E6_DIR_READ()        READ(E6_DIR_PIN)
  #else
    #define E6_DIR_INIT()        NOOP
    #define E6_DIR_WRITE(STATE)  L64XX_DIR_WRITE(E6, STATE)
    #define E6_DIR_READ()        (stepper##E6.getStatus() & STATUS_DIR);
    #if AXIS_DRIVER_TYPE_E6(L6470)
      #define DISABLE_STEPPER_E6() do{ stepperE6.free(); }while(0)
    #endif
  #endif
#endif

// E7 Stepper
#if AXIS_IS_L64XX(E7)
  extern L64XX_CLASS(E7)         stepperE7;
  #define E7_ENABLE_INIT()       NOOP
  #define E7_ENABLE_WRITE(STATE) (STATE ? stepperE7.hardStop() : stepperE7.free())
  #define E7_ENABLE_READ()       (stepperE7.getStatus() & STATUS_HIZ)
  #if AXIS_DRIVER_TYPE_E7(L6474)
    #define E7_DIR_INIT()        SET_OUTPUT(E7_DIR_PIN)
    #define E7_DIR_WRITE(STATE)  L6474_DIR_WRITE(E7, STATE)
    #define E7_DIR_READ()        READ(E7_DIR_PIN)
  #else
    #define E7_DIR_INIT()        NOOP
    #define E7_DIR_WRITE(STATE)  L64XX_DIR_WRITE(E7, STATE)
    #define E7_DIR_READ()        (stepper##E7.getStatus() & STATUS_DIR);
    #if AXIS_DRIVER_TYPE_E7(L6470)
      #define DISABLE_STEPPER_E7() do{ stepperE7.free(); }while(0)
    #endif
  #endif
#endif
