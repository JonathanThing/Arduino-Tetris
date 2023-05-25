#include "Tetris.h"

byte gameState;
Colour display[8][16];
byte inputs;
const byte buttonPins[7] = { 19, 3, 18, 15, 16, 17, 2 };

void setupTetris() {
  for (int i = 0; i < 7; i++) {
    pinMode(buttonPins[i], INPUT);
  }

  changeGameState(0);  // 0 Menu, 1 Game, 2 Lose
}

void readInputs() {
  inputs = 0;
  for (int i = 0; i < 7; i++) {
    inputs |= digitalRead(buttonPins[i]) << i;
  }
}

void updateTetris() {
  readInputs();

  if (gameState == 0) {
    updateMenu();
  } else if (gameState == 1) {
    updateGame();
  } else {
    updateLoseMenu();
  }
}

byte getGameState() {
  return gameState;
}

void changeGameState(byte state) {
  if (state == 0) {
    initMenu();
    gameState = 0;
  } else if (state == 1) {
    initGame(deltaTimeButton);
    gameState = 1;
  } else {
    initLoseMenu();
    gameState = 2;
  }
}