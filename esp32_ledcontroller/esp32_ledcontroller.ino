#include "button_lib.h"

// Red, green, and blue pins for PWM control
const int redPin = 13;     // 13 corresponds to GPIO13
const int greenPin = 12;   // 12 corresponds to GPIO12
const int bluePin = 14;    // 14 corresponds to GPIO14

const int button_pins[] = {15, 2, 0, 4, 16, 17, 5, 18};
int button_state = 0;

// Setting PWM frequency, channels and bit resolution
const int freq = 5000;
const int redChannel = 0;
const int greenChannel = 1;
const int blueChannel = 2;
// Bit resolution 2^8 = 256
const int resolution = 8;

// RGB values
int r,g,b = 0;

void setup() {
  Serial.begin(115200);

  
  // configure LED PWM functionalitites
  ledcSetup(redChannel, freq, resolution);
  ledcSetup(greenChannel, freq, resolution);
  ledcSetup(blueChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(redPin, redChannel);
  ledcAttachPin(greenPin, greenChannel);
  ledcAttachPin(bluePin, blueChannel);

  // attach button pins
  for (int i = 0; i < 7; i++)
    if (i < 4) pinMode(button_pins[i],OUTPUT);
    else pinMode(button_pins[i], INPUT_PULLDOWN);
}

void loop(){
  ledcWrite(redChannel, r);
  ledcWrite(greenChannel, g);
  ledcWrite(blueChannel, b);

//  r++;
//  g++;
//  b++;
//
//  if (r > 63) r++;
//  if (g > 63) g++;
//  if (b > 63) b++;
//    
//  if (r > 127) r = 0;
//  if (g > 127) g = 0;
//  if (b > 127) b = 0;

  delay(40);

  button_state = read_button_state(button_pins);
//  Serial.println("Button state = ");
//  Serial.println(button_state, BIN);
 
  int rgb_step = 2;
  int rgb_max = 128;
  
  if (button_state & 1<<0) if (r < 2 * rgb_max- 2 * rgb_step) r += 2 * rgb_step; else r = 2 * rgb_max;
  if (button_state & 1<<4) if (r > 2 * rgb_step) r -= 2 * rgb_step; else r = 0;
  
  if (button_state & 1<<1) if (g < rgb_max-rgb_step) g += rgb_step; else g = rgb_max;
  if (button_state & 1<<5) if (g > rgb_step) g -= rgb_step; else g = 0;

 
  if (button_state & 1<<2) if (b < rgb_max - rgb_step) b += rgb_step; else b = rgb_max;
  if (button_state & 1<<6) if (b > rgb_step) b -= rgb_step; else b = 0;
}




bool is_button_pressed() {
  return false;
}
