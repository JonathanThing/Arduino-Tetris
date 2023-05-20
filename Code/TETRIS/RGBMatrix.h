#ifndef RGB_MATRIX_H
#define RGB_MATRIX_H
#include <Arduino.h>
#include "Colour.h"

class RGBMatrix {
private:
public:
  RGBMatrix();
  void draw(Colour (&displayInput)[8][16]);
};
#endif