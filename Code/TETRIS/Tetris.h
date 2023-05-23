#ifndef TETRS_H
#define TETRS_H
#include <Arduino.h>
#include "Colour.h"
#include "Game.h"
#include "Menu.h"
#include "MusicPlayer.h"

class Tetris {
private:
  byte gameState;
  Colour display[8][16];
  byte inputs;
  const byte buttonPins[7] = { 19, 3, 18, 15, 16, 17, 2 };
  Game game;
  Menu menu;
  MusicPlayer music;

  void readInputs();
public:
  Tetris();
  void update();
  byte getGameState();
  void changeGameState(byte state);
  Colour (&getDisplay())[8][16];
};
#endif