#include <Arduino.h>
#include "dht.h"

    DHT mydht(26,DHT22);

void setup() {

// write your initialization code here

    Serial.begin(115200);
    mydht.begin();
}

void loop() {
    // write your code here
    float result = mydht.readTemperature();
    Serial.print("Temperature: ");
    Serial.println(result);

    result = mydht.readHumidity();
    Serial.print("Humidity:    ");
    Serial.println(result);
    delay(500);

}