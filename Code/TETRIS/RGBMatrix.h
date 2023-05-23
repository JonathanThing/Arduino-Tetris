#ifndef RGB_MATRIX_H
#define RGB_MATRIX_H
#include <Arduino.h>
#include "Tetris.h"
#include "Colour.h"

void setupRGBMatrix();
void draw(Colour (&displayInput)[8][16]);

#endif