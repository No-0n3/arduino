#ifndef _WATCHDOG_H_
#define _WATCHDOG_H_

#include <avr/interrupt.h>

/*
 * Configuration
 */
#ifdef WDP3
    #define _WD_PS3_MASK    _BV(WDP3)
#else
    #define _WD_PS3_MASK    0x00
#endif

#ifdef WDTCSR
    #define _WD_CONTROL_REG     WDTCSR
#else
    #define _WD_CONTROL_REG     WDTCR
#endif

#ifdef WDTOE
    #define _WD_CHANGE_BIT      WDTOE
#else
    #define _WD_CHANGE_BIT      WDCE
#endif

/*
 * Watchdog modes
 * Interrupt - Only raise an interrupt when the watchdog times out.
 * 
 * Reset - Only make a system reset when the watchdog times out.
 * 
 * Interrupt and reset - Raise an interrupt at first timeout and do a system
 * reset at second timeout. To stay in Interrupt and reset mode the WDIE bit
 * must be set after each interrupt.
 */
#define WDT_INT_M _BV(WDIE)
#define WDT_RST_M _BV(WDE)
#define WDT_IR_M _BV(WDIE) | _BV(WDE)

/*
 * Watchdog timeouts
 */
#define WDTO_16MS 0
#define WDTO_32MS 1
#define WDTO_64MS 2
#define WDTO_125MS 3
#define WDTO_250MS 4
#define WDTO_500MS 5
#define WDTO_1S 6
#define WDTO_2S 7

#ifdef WDP3
    #define WDTO_4S 8
    #define WDTO_8S 9
#endif

/*
 * Function to reset the watchdog timer.
 */
#define resetWatchdog() __asm__ __volatile__ ("wdr")

#if defined(__AVR_AT90CAN32__) \
|| defined(__AVR_AT90CAN64__) \
|| defined(__AVR_AT90CAN128__) \
|| defined(__AVR_AT90PWM1__) \
|| defined(__AVR_AT90PWM2__) \
|| defined(__AVR_AT90PWM216__) \
|| defined(__AVR_AT90PWM2B__) \
|| defined(__AVR_AT90PWM3__) \
|| defined(__AVR_AT90PWM316__) \
|| defined(__AVR_AT90PWM3B__) \
|| defined(__AVR_AT90PWM81__) \
|| defined(__AVR_AT90USB1286__) \
|| defined(__AVR_AT90USB1287__) \
|| defined(__AVR_AT90USB162__) \
|| defined(__AVR_AT90USB646__) \
|| defined(__AVR_AT90USB647__) \
|| defined(__AVR_AT90USB82__) \
|| defined(__AVR_ATmega1280__) \
|| defined(__AVR_ATmega1281__) \
|| defined(__AVR_ATmega1284P__) \
|| defined(__AVR_ATmega128RFA1__) \
|| defined(__AVR_ATmega164__) \
|| defined(__AVR_ATmega164A__) \
|| defined(__AVR_ATmega164P__) \
|| defined(__AVR_ATmega165__) \
|| defined(__AVR_ATmega165A__) \
|| defined(__AVR_ATmega165P__) \
|| defined(__AVR_ATmega168__) \
|| defined(__AVR_ATmega168A__) \
|| defined(__AVR_ATmega168P__) \
|| defined(__AVR_ATmega169__) \
|| defined(__AVR_ATmega169A__) \
|| defined(__AVR_ATmega169P__) \
|| defined(__AVR_ATmega169PA__) \
|| defined(__AVR_ATmega16HVA__) \
|| defined(__AVR_ATmega16HVA2__) \
|| defined(__AVR_ATmega16HVB__) \
|| defined(__AVR_ATmega16HVBREVB__) \
|| defined(__AVR_ATmega16M1__) \
|| defined(__AVR_ATmega16U2__) \
|| defined(__AVR_ATmega16U4__) \
|| defined(__AVR_ATmega2560__) \
|| defined(__AVR_ATmega2561__) \
|| defined(__AVR_ATmega324__) \
|| defined(__AVR_ATmega324A__) \
|| defined(__AVR_ATmega324P__) \
|| defined(__AVR_ATmega324PA__) \
|| defined(__AVR_ATmega325__) \
|| defined(__AVR_ATmega325A__) \
|| defined(__AVR_ATmega325P__) \
|| defined(__AVR_ATmega3250__) \
|| defined(__AVR_ATmega3250A__) \
|| defined(__AVR_ATmega3250P__) \
|| defined(__AVR_ATmega328__) \
|| defined(__AVR_ATmega328P__) \
|| defined(__AVR_ATmega329__) \
|| defined(__AVR_ATmega329A__) \
|| defined(__AVR_ATmega329P__) \
|| defined(__AVR_ATmega329PA__) \
|| defined(__AVR_ATmega3290__) \
|| defined(__AVR_ATmega3290A__) \
|| defined(__AVR_ATmega3290P__) \
|| defined(__AVR_ATmega32C1__) \
|| defined(__AVR_ATmega32HVB__) \
|| defined(__AVR_ATmega32HVBREVB__) \
|| defined(__AVR_ATmega32M1__) \
|| defined(__AVR_ATmega32U2__) \
|| defined(__AVR_ATmega32U4__) \
|| defined(__AVR_ATmega32U6__) \
|| defined(__AVR_ATmega406__) \
|| defined(__AVR_ATmega48__) \
|| defined(__AVR_ATmega48A__) \
|| defined(__AVR_ATmega48P__) \
|| defined(__AVR_ATmega640__) \
|| defined(__AVR_ATmega644__) \
|| defined(__AVR_ATmega644A__) \
|| defined(__AVR_ATmega644P__) \
|| defined(__AVR_ATmega644PA__) \
|| defined(__AVR_ATmega645__) \
|| defined(__AVR_ATmega645A__) \
|| defined(__AVR_ATmega645P__) \
|| defined(__AVR_ATmega6450__) \
|| defined(__AVR_ATmega6450A__) \
|| defined(__AVR_ATmega6450P__) \
|| defined(__AVR_ATmega649__) \
|| defined(__AVR_ATmega649A__) \
|| defined(__AVR_ATmega6490__) \
|| defined(__AVR_ATmega6490A__) \
|| defined(__AVR_ATmega6490P__) \
|| defined(__AVR_ATmega649P__) \
|| defined(__AVR_ATmega64C1__) \
|| defined(__AVR_ATmega64HVE__) \
|| defined(__AVR_ATmega64M1__) \
|| defined(__AVR_ATmega88__) \
|| defined(__AVR_ATmega88A__) \
|| defined(__AVR_ATmega88P__) \
|| defined(__AVR_ATmega88PA__) \
|| defined(__AVR_ATmega8HVA__) \
|| defined(__AVR_ATmega8U2__) \
|| defined(__AVR_ATtiny48__) \
|| defined(__AVR_ATtiny88__) \
|| defined(__AVR_ATtiny87__) \
|| defined(__AVR_ATtiny167__) \
|| defined(__AVR_AT90SCR100__) \
|| defined(__AVR_ATA6289__)
/*
 * Function to enable the watchdog. Takes two arguments, timeout and mode.
 * The different available timeouts and modes are defined. When using the
 * "Interrupt and reset"-mode a call to this function is needed after the 
 * interrupt to reset the WDIE-flag else will the next timeout result in a
 * system reset.
 * 
 * The function shouldn't be called from within the ISR function!
 */
#define enableWatchdog(timeout, mode) \
__asm__ __volatile__ ( \
    "in __tmp_reg__,__SREG__" "\n\t"    \
    "cli" "\n\t"    \
    "wdr" "\n\t"    \
    "sts %0,%1" "\n\t"  \
    "out __SREG__,__tmp_reg__" "\n\t"   \
    "sts %0,%2" "\n\t" \
    : /* no outputs */  \
    : "M" (_SFR_MEM_ADDR(_WD_CONTROL_REG)), \
    "r" (_BV(_WD_CHANGE_BIT) | _BV(WDE)), \
    "r" ((uint8_t) ((timeout & 0x08 ? _WD_PS3_MASK : 0x00) | \
        mode | (timeout & 0x07)) ) \
    : "r0"  \
)

/*
 * Function to disable the watchdog.
 * The function shouldn't be called from within the ISR function!
 */
#define disableWatchdog() \
__asm__ __volatile__ (  \
    "in __tmp_reg__, __SREG__" "\n\t" \
    "cli" "\n\t" \
    "sts %0, %1" "\n\t" \
    "sts %0, __zero_reg__" "\n\t" \
    "out __SREG__,__tmp_reg__" "\n\t" \
    : /* no outputs */ \
    : "M" (_SFR_MEM_ADDR(_WD_CONTROL_REG)), \
    "r" ((uint8_t)(_BV(_WD_CHANGE_BIT) | _BV(WDE))) \
    : "r0" \
)

#ifdef WDT_INT
/*
 * Functions to handle the interrupt sub routine for the watchdog.
 */
void (* wdtisr)() = 0;

void attachWatchdogInterrupt(void (*func)()) {
    wdtisr = func;
}

void detachWatchdogInterrupt() {
    wdtisr = 0;
}

ISR(WDT_vect) {
	if(wdtisr != 0) {
		wdtisr();
	}
}
#endif
#else
#error The processor is not supported!
#endif
#endif /* _WATCHDOG_H_ */
