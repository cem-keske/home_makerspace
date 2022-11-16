#include <Arduino.h>
#include <string>



#include "CO2Sensor.h"

#define PWM_PIN 14
const unsigned RX_PIN = 17;
const unsigned TX_PIN = 18;

CO2Sensor co2_sensor(PWM_PIN,RX_PIN,TX_PIN, &Serial1);
const unsigned char readCO2_command[] = {   0xFF, 0x01,
                                            0x86,0x00,
                                            0x00,0x00,
                                            0x00,0x00,
                                            0x79};

void setup() {
    //delay(5000);
    //Serial1.begin(9600,SERIAL_8N1,RX_PIN, TX_PIN);
    //Serial.begin(115200);
}

void loop() {
    delay(1000);
    int value = co2_sensor.digital_read();
    //Serial.println(value);
    float val = co2_sensor.pwm_read();
    //Serial.println(val);
//    Serial1.write(readCO2_command, 9);
    //Serial.println("Looping");
    //    int dig_value = co2_sensor.digital_read();
//    float pwm_value = co2_sensor.pwm_read();
//
//    Serial.print("Digital read: ");
//    Serial.println(dig_value);
//    Serial.print("PWM pin read: ");
//    Serial.println(pwm_value);
//    Serial.println("--------------------");
    delay(1000);
}