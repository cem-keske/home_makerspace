#ifndef RGB_LED_LIB_H
#define  RGB_LED_LIB_H

#include <array>

class RGB_Led {
  enum PIN_INDEXES{R_IDX = 0, G_IDX, B_IDX, GND_IDX, PINS_SIZE};
  
  const std::array<int, PINS_SIZE> pins;

public:

  float r;
  float g;
  float b;
  

  RGB_Led(int R_PIN, int G_PIN, int B_PIN);

  RGB_Led(int R_PIN, int G_PIN, int B_PIN, int GND_PIN);

  void dim_brighten(float factor);
  
  void seti_r(int r, bool show = true);

  void seti_g(int g, bool show = true);

  void seti_b(int b, bool show = true);

  void seti_rgb(int r, int g, int b, bool show = true);
  

  void setf_r(float r, bool show = true);

  void setf_g(float g, bool show = true);

  void setf_b(float b, bool show = true);

  void setf_rgb(float r, float g, float b, bool show = true);
  

  void refresh();

  void turn_on();

  void turn_off();
};

#endif
