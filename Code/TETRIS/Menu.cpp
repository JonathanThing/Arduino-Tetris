#include "Menu.h"

long deltaTimeButton = 0;

void menuFunnyFunction() {
  char inputDisplay[8][16] = { { 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B' },
                               { 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B' },
                               { 'Y', 'B', 'B', 'B', 'Y', 'B', 'P', 'B', 'P', 'P', 'O', 'B', 'O', 'O', 'O', 'B' },
                               { 'Y', 'B', 'Y', 'B', 'Y', 'P', 'B', 'P', 'B', 'B', 'O', 'B', 'O', 'B', 'O', 'B' },
                               { 'Y', 'Y', 'Y', 'Y', 'Y', 'P', 'P', 'P', 'P', 'P', 'O', 'O', 'O', 'B', 'O', 'B' },
                               { 'R', 'B', 'B', 'B', 'B', 'G', 'B', 'B', 'B', 'B', 'W', 'B', 'B', 'B', 'W', 'B' },
                               { 'R', 'R', 'R', 'R', 'R', 'G', 'G', 'G', 'G', 'G', 'W', 'W', 'W', 'W', 'W', 'B' },
                               { 'R', 'B', 'B', 'B', 'B', 'G', 'B', 'B', 'B', 'B', 'W', 'B', 'B', 'B', 'W', 'B' } };

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

void initMenu() {
  deltaTimeButton = 0;
  menuFunnyFunction();
}

void initLoseMenu() {
  deltaTimeButton = 0;
}

void updateMenu() {
}

void updateLoseMenu() {
}

void awaitInput() {
  bool buttonPressed = false;
  buttonPressed = (inputs > 0);
  if (buttonPressed && deltaTimeButton == 0) {
    deltaTimeButton = micros();
  } else if (!buttonPressed && deltaTimeButton > 0) {
    changeGameState(1);
  }
}