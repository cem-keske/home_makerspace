#include <Arduino.h>
#include "cmath"

constexpr int GND_PIN = 8;
constexpr int VCC_PIN = 15;
constexpr int X_PIN = 2;
constexpr int Y_PIN = 0;
constexpr int BUTTON_PIN = 4;

constexpr int DEBOUNCING_TIME = 200;

int X_MID;
int X_MAX;
int X_MIN;




void setup() {

    Serial.begin(115200);

    pinMode(GND_PIN, OUTPUT);
    pinMode(VCC_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    digitalWrite(VCC_PIN,true);
    digitalWrite(GND_PIN,false);

    delay(5000);
    Serial.println("Press X on the middle");

    int push_button = false;

    while( (push_button = !digitalRead(BUTTON_PIN)) == false );delay(DEBOUNCING_TIME); //wait for the press
    X_MID = analogRead(X_PIN);
    while( (push_button = !digitalRead(BUTTON_PIN)) == true );delay(DEBOUNCING_TIME); //wait for release

    Serial.println("Press X on the left");

    push_button = false;

    while( (push_button = !digitalRead(BUTTON_PIN)) == false );delay(DEBOUNCING_TIME); //wait for the press
    X_MIN = analogRead(X_PIN);
    while( (push_button = !digitalRead(BUTTON_PIN)) == true );delay(DEBOUNCING_TIME); //wait for release

    Serial.println("Press X on the right");

    push_button = false;

    while( (push_button = !digitalRead(BUTTON_PIN)) == false );delay(DEBOUNCING_TIME); //wait for the press
    X_MAX = analogRead(X_PIN);
    while( (push_button = !digitalRead(BUTTON_PIN)) == true );delay(DEBOUNCING_TIME); //wait for release


}

void loop() {
// write your code here


    Serial.print("X_MID ");
    Serial.print(X_MID);
    Serial.print("\t X_MAX ");
    Serial.print(X_MAX);
    Serial.print("\t X_MIN ");
    Serial.println(X_MIN);
    Serial.print("X_POS ");


    int x_axis = analogRead(X_PIN);
    float x_pos;
    if (std::abs(x_axis-X_MID) > (X_MAX-X_MIN)/100) { //
        if (x_axis > X_MID){
            x_pos = (x_axis-X_MID)/float(X_MAX-X_MID);
        } else {
            x_pos = -(x_axis-X_MID)/float(X_MIN-X_MID);
        }
    } else {
        x_pos = 0;
    }

    Serial.print("X_POS ");
    Serial.println(x_pos);

    delay(100);
}