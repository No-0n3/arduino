<h1>WDT library</h1>
This is a library to ease the use of the watchdog in avr-gcc library . The information in this document is based on the datasheet for ATmega2560 (http://www.atmel.com/images/doc2549.pdf) and the documentation for avr-gcc (http://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html). Read the documentation for your microcontroller to see so it works. This library have been fully tested for ATmega2560 (Arduino Mega 2560) and ATmega32U4 (Arduino Leonardo and Arduino Yun). A diretive for which models it should be compatible with has been added as a build directive.

I'm happy if someone could do some tests for other Arduinos and report it to me.

<h2>Configuration</h2>
Use the defined values included in the header. When using the watchdog as an interrupt you also need to define WDT_INT to enable the functions for handling the interrupt. This is to save programming space because an ISR vector where the interrupt is called from is created in the library.

<h3>Watchdog-modes</h3>
The watchdog on the AVR-microcontrollers can be set to 3 different modes:<br>
<li>
<ul>Interrupt - Only raise an interrupt when the watchdog times out.</ul>
<ul>Reset - Only make a system reset when the watchdog times out.</ul>
<ul>Interrupt and reset - Raise an interrupt at first timeout and do a system reset at second timeout. WDIE is cleared in hardware when it triggers. To stay in Interrupt and reset mode the WDIE bit must be set after each interrupt.</ul>
<li>

Defines for the modes:<br>
<li>
<ul>WDT_INT_M - Interrupt mode</ul>
<ul>WDT_RST_M - Reset mode</ul>
<ul>WDT_IR_M - Interrupt and reset mode</ul>
</li>

<h3>Watchdog timeout time</h3>
The watchdog can be configured to different durations. I have included a constant
for each of this timer modes.

Defines for timer<br>
<li>
<ul>WDTO_16MS - 16 ms</ul>
<ul>WDTO_32MS - 32 ms</ul>
<ul>WDTO_64MS - 64 ms</ul>
<ul>WDTO_125MS - 125 ms</ul>
<ul>WDTO_250MS - 250 ms</ul>
<ul>WDTO_500MS - 500 ms</ul>
<ul>WDTO_1S - 1 s</ul>
<ul>WDTO_2S - 2 s</ul>
<ul>WDTO_4S - 4 s</ul>
<ul>WDTO_8S - 8 s</ul>
</li>

<h2>Macro functions</h2>
These functions are macros for inline assembler code.

<li>
<ul>resetWatchdog() - Resets the watchdog timer</ul>
<ul>enableWatchdog(timeout, mode) - Enable the watchdog. Use the defines that have been mentioned earlier. Do not <ul>call it from an interrupt vector!</ul>
<ul>disableWatchdog() - Disable the watchdog. Do not call it from an interrupt vector!</ul>
</li>

<h2>Functions</h2>
These functions attach and detach an interrupt function to the watchdog interrupt. Only a
function with return type void and no arguments can attached, like for all interrupts. To
save some memory these functions need to be enabled by setting the define WDT_INT in your
sketch like "#define WDT_INT".

<li>
<ul>void attachWatchdogInterrupt(void (*func)()) - Attach a function to the watchdog interrupt.</ul>
<ul>void detachWatchdogInterrupt() - Detach the attached function from the interrupt.</ul>
</li>

<h2>Example</h2>
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
