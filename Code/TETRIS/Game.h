#ifndef GAME_H
#define GAME_H
#include <Arduino.h>
#include "Colour.h"

class Game {
private:

public:
  Game();
  void update(byte inputs);
  void init(long seed);
};
#endif