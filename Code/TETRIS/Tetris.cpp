#include "Tetris.h"

Tetris::Tetris() {
  changeGameState(0);  // 0 Menu, 1 Game, 2 Lose
  for (int i = 0; i < 7; i++) {
    pinMode(buttonPins[i], INPUT);
  }

  char inputDisplay[8][16] = { { 'B', 'B', 'W', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'Y', 'O', 'R', 'O', 'Y' },
                               { 'B', 'W', 'W', 'W', 'B', 'B', 'B', 'B', 'W', 'B', 'B', 'Y', 'Y', 'O', 'Y', 'Y' },
                               { 'B', 'B', 'B', 'B', 'R', 'B', 'B', 'W', 'W', 'W', 'B', 'B', 'Y', 'Y', 'Y', 'B' },
                               { 'B', 'B', 'B', 'R', 'P', 'R', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B' },
                               { 'B', 'B', 'R', 'P', 'P', 'P', 'R', 'C', 'C', 'C', 'C', 'C', 'B', 'C', 'C', 'C' },
                               { 'C', 'C', 'C', 'P', 'P', 'P', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C' },
                               { 'G', 'G', 'C', 'G', 'G', 'G', 'C', 'G', 'G', 'G', 'G', 'C', 'G', 'G', 'G', 'G' },
                               { 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G' } };

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++) {
      switch (inputDisplay[i][j]) {
        case 'R':
          display[i][j] = Colour::RED;
          break;
        case 'B':
          display[i][j] = Colour::BLUE;
          break;
        case 'G':
          display[i][j] = Colour::GREEN;
          break;
        case 'Y':
          display[i][j] = Colour::YELLOW;
          break;
        case 'P':
          display[i][j] = Colour::PURPLE;
          break;
        case 'W':
          display[i][j] = Colour::WHITE;
          break;
        case 'O':
          display[i][j] = Colour::ORANGE;
          break;
        case 'C':
          display[i][j] = Colour::CYAN;
          break;
      }
    }
  }
}

void Tetris::readInputs() {
  inputs = 0;
  for (int i = 0; i < 7; i++) {
    inputs |= digitalRead(buttonPins[i]) << i;
  }
}

void Tetris::update() {
  readInputs();
  music.update();
  if (gameState == 0) {
    menu.update(inputs);
  } else if (gameState == 1) {
    game.update(inputs);
  } else {
    menu.loseUpdate(inputs);
  }
}

byte Tetris::getGameState() {
  return gameState;
}

void Tetris::changeGameState(byte state) {
  if (state == 0) {
    menu.init();
    gameState = 0;
  } else if (state == 1) {
    game.init();
    gameState = 1;
  } else {
    menu.loseInit();
    gameState = 2;
  }
}

Colour (&Tetris::getDisplay())[8][16] {
  return display;
}