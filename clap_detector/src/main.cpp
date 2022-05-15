#include <Arduino.h>
#include <rgb_led.h>

const int analog_pin = 39;
const int digital_pin = 36;
RGB_Led indicator_led(33,25,26,27);

void setup() {
    Serial.begin(115200);
    indicator_led.setf_rgb(1,1,1);
    pinMode(digital_pin, INPUT);
}

void loop() {

    bool clap = digitalRead(digital_pin);
    if(clap) {
        indicator_led.toggle();
        delay(300);
    }
    Serial.println(clap);
    delay(1);

}