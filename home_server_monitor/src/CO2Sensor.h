//
// Created by cem on 26/05/2022.
//

#ifndef PROTOCOL_CO2SENSOR_H
#define PROTOCOL_CO2SENSOR_H

#include <Arduino.h>
//             |----------------|o CAL (5V)
//      PWM o|--                |o
//          o|                  |o TX_sensor
//      GND o|                  |o RX_sensor
//       5V o|__________________|o

class CO2Sensor {

public:
    CO2Sensor(int pwmPin, int rxdPin, int txdPin, HardwareSerial *uart_interface = &Serial1);

    CO2Sensor(int rxdPin, int txdPin, HardwareSerial *uart_interface = &Serial1);

    CO2Sensor(int pwmPin, HardwareSerial *uart_interface = &Serial1);

    float pwm_read();
    int digital_read(bool request_new = true);
    void set_auto_calibration(bool ON);


private:
    int8_t PWM_PIN;
    int8_t RXD_PIN;
    int8_t TXD_PIN;

    HardwareSerial* uart_interface_;

    bool is_digital;
    bool is_pwm;

    int last_digital_measurement_;

    char get_check_sum(const char *packet);
    void digital_measure();
};


#endif //PROTOCOL_CO2SENSOR_H
