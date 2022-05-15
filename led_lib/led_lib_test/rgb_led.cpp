#include "rgb_led.h"
#include <arduino.h>

RGB_Led::RGB_Led(int r, int g, int b): RGB_Led(r,g,b, -1){}

RGB_Led::RGB_Led(int r, int g, int b, int gnd): pins({r,g,b, gnd}), on_off_state(false){
  
  // configure LED PWM functionalitites
  ledcSetup(R_IDX, 5000, 8);
  ledcSetup(G_IDX, 5000, 8);
  ledcSetup(B_IDX, 5000, 8);
  
  ledcAttachPin(pins[R_IDX], R_IDX);
  ledcAttachPin(pins[G_IDX], G_IDX);
  ledcAttachPin(pins[B_IDX], B_IDX); 

  if (gnd > 0) { // configure ground if artificial ground is used
    pinMode(pins[GND_IDX], OUTPUT);
    digitalWrite(pins[GND_IDX], LOW);
  }
}

std::string RGB_Led::to_string(){

std::string str = "RGB LED object connected to the pins: [R,G,B,GND] = [" + std::to_string(pins[R_IDX]) +
  "," + std::to_string(pins[G_IDX]) +
  "," + std::to_string(pins[B_IDX]) +
  "," + std::to_string(pins[GND_IDX]) + "]\n";
  
  str += "[r,g,b] = [" + std::to_string(int(r*255)) + "," + std::to_string(int(g*255)) + "," + std::to_string(int(b*255)) + "]\n";

  str += std::string("State: ") + ((on_off_state) ? "ON\n" : "OFF\n");

  return str;
  
}

void RGB_Led::seti_r(int r, bool show){
  this->r = r/255.;
  if(show){
    ledcWrite(R_IDX, int(this->r * 255));
    on_off_state = true;
  }
}

void RGB_Led::seti_g(int g, bool show){
  this->g = g/255.;
  if(show){
    ledcWrite(G_IDX, int(this->g * 255));
    on_off_state = true;
  }
}

void RGB_Led::seti_b(int b, bool show){
  this->b = b/255.;
  if(show){
    ledcWrite(B_IDX, int(this->b * 255));
    on_off_state = true;
  }
}

void RGB_Led::seti_rgb(int r, int g, int b, bool show){
  seti_r(r, show);
  seti_g(g, show);
  seti_b(b, show);
}

void RGB_Led::setf_r(float r, bool show){
  this->r = r;
  if(show){
    ledcWrite(R_IDX, int(this->r * 255));
    on_off_state = true;
  }
}

void RGB_Led::setf_g(float g, bool show){
  this->g = g;
  if(show){
    ledcWrite(G_IDX, int(this->g * 255));
    on_off_state = true;
  }
}

void RGB_Led::setf_b(float b, bool show){
  this->b = b;
  if(show){
    ledcWrite(B_IDX, int(this->b * 255));
    on_off_state = true;
  }
}

void RGB_Led::setf_rgb(float r, float g, float b, bool show){
  setf_r(r, show);
  setf_g(g, show);
  setf_b(b, show);
}

void RGB_Led::dim_brighten(float factor, bool show){
  
  float ri = r * factor;
  float gi = g * factor;
  float bi = b * factor;


  if (ri > 1 || gi > 1 || bi > 1){
    return;
  }
  if (ri < 1/255. || gi < 1/255. || bi < 1/255.){
    return;
  }
  r = ri;
  g = gi;
  b = bi;
  if (show){
    turn_on();
  }
}



void RGB_Led::turn_on(){
  ledcWrite(R_IDX, int(this->r * 255));
  ledcWrite(G_IDX, int(this->g * 255));
  ledcWrite(B_IDX, int(this->b * 255));  
  on_off_state = true;
  
}

void RGB_Led::turn_off(){
  ledcWrite(R_IDX, 0);
  ledcWrite(G_IDX, 0);
  ledcWrite(B_IDX, 0);
  on_off_state = false;
}

void RGB_Led::toggle(){
  if (on_off_state == true){
    turn_off();
  } else {
    turn_on();
  }
}
