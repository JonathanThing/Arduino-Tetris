#ifndef TETRS_H
#define TETRS_H
#include <Arduino.h>
#include "Colour.h"

class Tetris {
private:
  byte gameState;
  Colour display[8][16];

public:
  Tetris();
  void update();
  byte getGameState();
  Colour (&getDisplay())[8][16];
};
#endif