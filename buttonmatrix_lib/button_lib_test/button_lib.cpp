#include "button_lib.h"
#include <arduino.h>


/*
 * Fetch user input and update the btm state
 */
void Button_Matrix::fetch(){
  unsigned button_state = 0;
  for(unsigned row = 0; row < rows ; row++){
    digitalWrite(pins[row], HIGH);
    for(unsigned col = 0; col < cols; col++) {
      unsigned button = digitalRead(pins[rows + col]);
      button_state ^= button << (row * cols +col);
    }
    digitalWrite(pins[row], LOW);
  }
  state = button_state;
}

/**
 * Returns if the button is pressed at the current state.
 * button_x = [0,3]
 * button_y = [0,3]
 * fetch_first: Fetch before decision
 */
bool Button_Matrix::is_pressed(unsigned button_x, unsigned button_y, bool fetch_first){
  
if (fetch_first){
  fetch();
}

return (state) & 1 << ((button_y * rows) + button_x);

}

/*
 * button_pins: pins from 1 to 8 in a row
 */
Button_Matrix::Button_Matrix(std::array<unsigned, rows + cols> button_pins): pins(button_pins){
  for (int i = 0; i < 7; i++)
    if (i < rows){
      pinMode(pins[i], OUTPUT);
      digitalWrite(pins[i], LOW);
    }
    else {
      pinMode(button_pins[i], INPUT_PULLDOWN);
    }
}
