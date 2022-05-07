#include "button_lib.h"
#include <arduino.h>
int read_button_state(const int button_pins[8]) {
  int button_state = 0;
  for(int row = 0; row < 4; row++){
    digitalWrite(button_pins[row], HIGH);
    for(int col = 0; col < 4; col++) {
      int button = digitalRead(button_pins[4 + col]);
      button_state ^= button << (row * 4 +col);
    }
    digitalWrite(button_pins[row], LOW);
  }
  return button_state;
}
