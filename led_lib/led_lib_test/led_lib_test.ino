#include "rgb_led.h"

// Red, green, and blue pins for PWM control
const int redPin = 13;     // 13 corresponds to GPIO13
const int greenPin = 12;   // 12 corresponds to GPIO12
const int bluePin = 14;    // 14 corresponds to GPIO14

RGB_Led led(redPin, greenPin, bluePin);

void setup() {
  Serial.begin(115200);
  led.setf_rgb(1,1,1);
}

void loop(){

  delay(500);
  led.turn_off();
  delay(500);
  led.turn_on();
  delay(500);
  led.dim_brighten(0.5);
  delay(500);
  led.toggle();
  delay(500);
  led.toggle();

  Serial.println(led.to_string().c_str());

}
