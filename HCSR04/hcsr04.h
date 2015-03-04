#ifndef _HCSR04_H_
#define _HCSR04_H_

#include <Arduino.h>

/* Class to operate a HC-SR04 distance sensor. */
class HCSR04 {
  public:
    HCSR04(int trig, int echo) {
      pinMode(trig, OUTPUT);
      pinMode(echo, INPUT);

      this->trigPin = trig;
      this->echoPin = echo;
    }

    // The method is used to measure the distance. Returns the distance in centimeter.
    const unsigned int get() {
      digitalWrite(this->trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(this->trigPin, LOW);

      return pulseIn(this->echoPin, HIGH) * 0.034 / 2;
    }

  private:
    int trigPin;
    int echoPin;
};
#endif