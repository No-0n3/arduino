This is a library to ease the use of the watchdog in avr-gcc library . The information in this
document is based on the datasheet for ATmega2560 (http://www.atmel.com/images/doc2549.pdf) 
and the documentation for avr-gcc (http://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html).
Read the documentation for your microcontroller to see so it works. This library have been
fully tested for ATmega2560 (Arduino Mega 2560) and ATmega32U4 (Arduino Leonardo and Arduino Yun).
A diretive for which models it should be compatible with has been added as a build directive.

I'm happy if someone could do some tests for other Arduinos and report it to me.


Configuration:
Use the defined values included in the header. When using the watchdog as an interrupt
you also need to define WDT_INT to enable the functions for handling the
interrupt. This is to save programming space because an ISR vector where the interrupt
is called from is created in the library.

	Watchdog-modes:
		The watchdog on the AVR-microcontrollers can be set to 3 different modes:
		Interrupt - Only raise an interrupt when the watchdog times out.
		Reset - Only make a system reset when the watchdog times out.
		Interrupt and reset - Raise an interrupt at first timeout and do a 
		  system reset at second timeout. WDIE is cleared in hardware when it
		  triggers. To stay in Interrupt and reset mode the WDIE bit must be set
		  after each interrupt.

		Defines for the modes:
		WDT_INT_M - Interrupt mode
		WDT_RST_M - Reset mode
		WDT_IR_M - Interrupt and reset mode

	Watchdog timeout time:
		The watchdog can be configured to different durations. I have included a constant
		for each of this timer modes.

		Defines for timer:
        WDTO_16MS - 16 ms
		WDTO_32MS - 32 ms
		WDTO_64MS - 64 ms
		WDTO_125MS - 125 ms
		WDTO_250MS - 250 ms
		WDTO_500MS - 500 ms
		WDTO_1S - 1 s
		WDTO_2S - 2 s
		WDTO_4S - 4 s
		WDTO_8S - 8 s

Macro functions:
These functions are macros for inline assembler code.

resetWatchdog() - Resets the watchdog timer
enableWatchdog(timeout, mode) - Enable the watchdog. Use the defines that have been mentioned earlier. Do not call it from an interrupt vector!
disableWatchdog() - Disable the watchdog. Do not call it from an interrupt vector!

Functions:
These functions attach and detach an interrupt function to the watchdog interrupt. Only a
function with return type void and no arguments can attached, like for all interrupts. To
save some memory these functions need to be enabled by setting the define WDT_INT in your
sketch like "#define WDT_INT".

void attachWatchdogInterrupt(void (*func)()) - Attach a function to the watchdog interrupt.
void detachWatchdogInterrupt() - Detach the attached function from the interrupt.


Example:
```C
#define WDT_INT
#include <watchdog.h>

volatile boolean led = false;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    
    Serial.begin(115200);
    
    while(! Serial);
    
    attachWatchdogInterrupt(wdt_interrupt); //Attach interrupt function
    enableWatchdog(WDT_IR_M, WDTO_1S); //Enable watchdog
}

void loop() {
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    
    if(led) {
        digitalWrite(LED_BUILTIN, HIGH);
        led = false;
        
        Serial.println(F("WDT INTERRUPT!"));
        delay(1000);
    }
}

void wdt_interrupt() {
    led = true;
}
```
