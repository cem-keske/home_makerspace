#ifndef BUTTON_LIB_H
#define BUTTON_LIB_H

#include <array>

struct Button_Matrix{
  
  static const unsigned rows = 4;
  static const unsigned cols = 4;
  
  const std::array<unsigned, rows + cols> pins;
  
  unsigned state;

 /*
 * button_pins: pins from 1 to 8 in a row
 */
  Button_Matrix(std::array<unsigned, rows+cols> button_pins);

  /*
   * Fetch user input and update the btm state
   */
  void fetch();
  
  /**
   * Returns if the button is pressed at the current state.
   * button_x = [0,3]
   * button_y = [0,3]
   * fetch_first: Fetch before decision
   */
  bool is_pressed(unsigned button_x, unsigned button_y, bool fetch_first = true);

};

#endif
