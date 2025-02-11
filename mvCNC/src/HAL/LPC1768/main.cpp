/**
 * Modern Vintage CNC Firmware
*/
#ifdef TARGET_LPC1768

#include <usb/usb.h>
#include <usb/usbcfg.h>
#include <usb/usbhw.h>
#include <usb/usbcore.h>
#include <usb/cdc.h>
#include <usb/cdcuser.h>
#include <usb/mscuser.h>
#include <CDCSerial.h>
#include <usb/mscuser.h>

#include "../../inc/mvCNCConfig.h"
#include "../../core/millis_t.h"

#include "../../sd/cardreader.h"

extern uint32_t MSC_SD_Init(uint8_t pdrv);

extern "C" {
  #include <debug_frmwrk.h>
  extern "C" int isLPC1769();
  extern "C" void disk_timerproc();
}

void SysTick_Callback() { disk_timerproc(); }

TERN_(POSTMORTEM_DEBUGGING, extern void install_min_serial());

void HAL_init() {

  // Init LEDs
  #if PIN_EXISTS(LED)
    SET_DIR_OUTPUT(LED_PIN);
    WRITE_PIN_CLR(LED_PIN);
    #if PIN_EXISTS(LED2)
      SET_DIR_OUTPUT(LED2_PIN);
      WRITE_PIN_CLR(LED2_PIN);
      #if PIN_EXISTS(LED3)
        SET_DIR_OUTPUT(LED3_PIN);
        WRITE_PIN_CLR(LED3_PIN);
        #if PIN_EXISTS(LED4)
          SET_DIR_OUTPUT(LED4_PIN);
          WRITE_PIN_CLR(LED4_PIN);
        #endif
      #endif
    #endif

    // Flash status LED 3 times to indicate mvCNC has started booting
    LOOP_L_N(i, 6) {
      TOGGLE(LED_PIN);
      delay(100);
    }
  #endif

  // Init Servo Pins
  #define INIT_SERVO(N) OUT_WRITE(SERVO##N##_PIN, LOW)
  #if HAS_SERVO_0
    INIT_SERVO(0);
  #endif
  #if HAS_SERVO_1
    INIT_SERVO(1);
  #endif
  #if HAS_SERVO_2
    INIT_SERVO(2);
  #endif
  #if HAS_SERVO_3
    INIT_SERVO(3);
  #endif

  //debug_frmwrk_init();
  //_DBG("\n\nDebug running\n");
  // Initialize the SD card chip select pins as soon as possible
  #if PIN_EXISTS(SD_SS)
    OUT_WRITE(SD_SS_PIN, HIGH);
  #endif

  #if PIN_EXISTS(ONBOARD_SD_CS) && ONBOARD_SD_CS_PIN != SD_SS_PIN
    OUT_WRITE(ONBOARD_SD_CS_PIN, HIGH);
  #endif

  #ifdef LPC1768_ENABLE_CLKOUT_12M
   /**
    * CLKOUTCFG register
    * bit 8 (CLKOUT_EN) = enables CLKOUT signal. Disabled for now to prevent glitch when enabling GPIO.
    * bits 7:4 (CLKOUTDIV) = set to 0 for divider setting of /1
    * bits 3:0 (CLKOUTSEL) = set to 1 to select main crystal oscillator as CLKOUT source
    */
    LPC_SC->CLKOUTCFG = (0<<8)|(0<<4)|(1<<0);
    // set P1.27 pin to function 01 (CLKOUT)
    PINSEL_CFG_Type PinCfg;
    PinCfg.Portnum = 1;
    PinCfg.Pinnum = 27;
    PinCfg.Funcnum = 1;    // function 01 (CLKOUT)
    PinCfg.OpenDrain = 0;  // not open drain
    PinCfg.Pinmode = 2;    // no pull-up/pull-down
    PINSEL_ConfigPin(&PinCfg);
    // now set CLKOUT_EN bit
    SBI(LPC_SC->CLKOUTCFG, 8);
  #endif

  USB_Init();                               // USB Initialization
  USB_Connect(false);                       // USB clear connection
  delay(1000);                              // Give OS time to notice
  USB_Connect(true);

  TERN_(HAS_SD_HOST_DRIVE, MSC_SD_Init(0)); // Enable USB SD card access

  const millis_t usb_timeout = millis() + 2000;
  while (!USB_Configuration && PENDING(millis(), usb_timeout)) {
    delay(50);
    HAL_idletask();
    #if PIN_EXISTS(LED)
      TOGGLE(LED_PIN);     // Flash quickly during USB initialization
    #endif
  }

  HAL_timer_init();

  TERN_(POSTMORTEM_DEBUGGING, install_min_serial()); // Install the min serial handler
}

// HAL idle task
void HAL_idletask() {
  #if HAS_SHARED_MEDIA
    // If mvCNC is using the SD card we need to lock it to prevent access from
    // a PC via USB.
    // Other HALs use IS_SD_PRINTING() and IS_SD_FILE_OPEN() to check for access but
    // this will not reliably detect delete operations. To be safe we will lock
    // the disk if mvCNC has it mounted. Unfortunately there is currently no way
    // to unmount the disk from the LCD menu.
    // if (IS_SD_PRINTING() || IS_SD_FILE_OPEN())
    if (card.isMounted())
      MSC_Aquire_Lock();
    else
      MSC_Release_Lock();
  #endif
  // Perform USB stack housekeeping
  MSC_RunDeferredCommands();
}

#endif // TARGET_LPC1768
