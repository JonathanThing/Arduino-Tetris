#ifndef RGB_MATRIX_H
#define RGB_MATRIX_H
#include <Arduino.h>
#include "Colour.h"

class RGBMatrix {
private:
  Colour display[8][16];
  byte currentRow;
  void cyclePower();
  void displayRed();
  void displayGreen();
  void displayBlue();
public:
  RGBMatrix();
  void draw();
  void init();
};
#endif