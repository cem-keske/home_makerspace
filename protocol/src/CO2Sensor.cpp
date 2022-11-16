//
// Created by cem on 26/05/2022.
//

#include "CO2Sensor.h"

const unsigned SENSOR_BAUD = 9600;

const unsigned SENSOR_RESOLUTION = 5000; //ppm

const unsigned char readCO2_command[] = {   0xFF, 0x01,
                                    0x86,0x00,
                                    0x00,0x00,
                                    0x00,0x00,
                                    0x79};

const unsigned char calibration_off_command[] = {   0xFF, 0x01,
                                           0x79,0x00,
                                           0x00,0x00,
                                           0x00,0x00,
                                           0x86};

const unsigned char calibration_on_command[] = {   0xFF, 0x01,
                                            0x79,0xA0,
                                            0x00,0x00,
                                            0x00,0x00,
                                            0xe6};

CO2Sensor::CO2Sensor(int pwmPin, int rxdPin, int txdPin, HardwareSerial* uart_interface) : PWM_PIN(pwmPin),
                                                                                    RXD_PIN(rxdPin),
                                                                                    TXD_PIN(txdPin),
                                                                                    uart_interface_(uart_interface),
                                                                                    is_digital(true),
                                                                                    is_pwm(true),
                                                                                    last_digital_measurement_(-1){
    uart_interface_->begin(SENSOR_BAUD, SERIAL_8N1, RXD_PIN, TXD_PIN);
    delay(200);
    uart_interface_->write(calibration_off_command, 9);

    pinMode(PWM_PIN, INPUT);
}

CO2Sensor::CO2Sensor(int rxdPin, int txdPin, HardwareSerial *uart_interface): PWM_PIN(-1),
                                                                            RXD_PIN(rxdPin),
                                                                            TXD_PIN(txdPin),
                                                                            uart_interface_(uart_interface),
                                                                            is_digital(true),
                                                                            is_pwm(false),
                                                                            last_digital_measurement_(-1){
    uart_interface_->begin(SENSOR_BAUD, SERIAL_8N1, RXD_PIN, TXD_PIN);
    delay(200);
    uart_interface_->write(calibration_off_command, 9);
}

CO2Sensor::CO2Sensor(int pwmPin, HardwareSerial *uart_interface): PWM_PIN(pwmPin),
                                                                RXD_PIN(-1),
                                                                TXD_PIN(-1),
                                                                uart_interface_(uart_interface),
                                                                is_digital(false),
                                                                is_pwm(true),
                                                                last_digital_measurement_(-1){
    pinMode(PWM_PIN, INPUT);
}

char CO2Sensor::get_check_sum(const char *packet) {
    char i, checksum;
    for (i = 1; i < 8; i++) {
        checksum += packet[i];
    }
    checksum = 0xff - checksum;
    return checksum + 1;
}

float CO2Sensor::pwm_read() {
    if (!is_pwm)
        return -1;
    unsigned long pwm_value = pulseIn(PWM_PIN, HIGH,2000000L);

    return (pwm_value - 2.0 * 1e3) / 1e6 * SENSOR_RESOLUTION;
}

int CO2Sensor::digital_read(bool request_new) {

    if (!is_digital)
        return -1;

    if (request_new)
        digital_measure();

    return last_digital_measurement_;

}

void CO2Sensor::digital_measure() {

    uart_interface_->write(readCO2_command,9);

    delay(1000);

    //-----Read response-----
    char buffer[9];
    uart_interface_->read(buffer,9);
    int ppm = buffer[2] << 8 | buffer[3];


    Serial.println("Received CO2 buffer:");
    for (int i = 0; i < 9; i++) {
        Serial.print("0x");
        Serial.print((int)buffer[i], HEX);
        Serial.println();
    }
    Serial.println("-------------");


    if (get_check_sum(buffer) == buffer[8]) //checksum valid, update
        last_digital_measurement_ = ppm;
}

void CO2Sensor::set_auto_calibration(bool ON) {

    uart_interface_->write((ON) ? calibration_on_command : calibration_off_command, 9);

}

