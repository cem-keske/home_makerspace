#include "button_lib.h"



Button_Matrix btm({15, 2, 0, 4, 16, 17, 5, 18});


void setup() {
  Serial.begin(115200);
}

void loop() {
//  Serial.println("looping");
  delay(100);
  btm.fetch();
  for(int i = 0; i<4; i++){
    for(int j = 0; j<4; j++){
      if(btm.is_pressed(i,j, false)){
         Serial.print("Pressed: ");
         Serial.println(i + j*4 + 1);
      }
    }
  }
}
