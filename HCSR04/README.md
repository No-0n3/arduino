<h1>HCSR04 library</h1>
This is a library to use with the ultrasonic ranging module HC-SR04 (http://www.micropik.com/PDF/HCSR04.pdf). This library have been fully tested for ATmega2560 (Arduino Mega 2560) and ATmega32U4 (Arduino Leonardo and Arduino Yun).

I'm happy if someone could do some tests for other Arduinos and report it to me.

<h2>Classes</h2>
HCSR04 - A class that controls the module.

<h3>Functions and methods</h3>

<li>
<ul>HCSR04(int trig, int echo) - Constructor. Assign which pins to use as the trigger pin and echo pin. Echo pin must be connected to a PWM.</ul>
<ul>const unsigned int get() - Activates the module to determine distance. Returns an integer which is the distance measured in centimeters.</ul>
</li>

<h2>Example</h2>
```C
#include <hcsr04.h>

HCSR04 dist(22, 8);

void setup() {
  Serial.begin(9600);
  
  while(! Serial);
}

void loop() {
  Serial.print("Distance: ");
  Serial.print(dist.get());
  Serial.println(" cm");

  delay(2000);
}
```
