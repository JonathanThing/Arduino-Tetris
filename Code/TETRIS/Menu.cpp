#include "Menu.h"

long deltaTimeButton = 0;

void menuFunnyFunction() {
  char inputDisplay[8][16] = { { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },
                               { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },
                               { 'Y', 'N', 'N', 'N', 'Y', 'N', 'P', 'N', 'P', 'P', 'O', 'N', 'O', 'O', 'O', 'N' },
                               { 'Y', 'N', 'Y', 'N', 'Y', 'P', 'N', 'P', 'N', 'N', 'O', 'N', 'O', 'N', 'O', 'N' },
                               { 'Y', 'Y', 'Y', 'Y', 'Y', 'P', 'P', 'P', 'P', 'P', 'O', 'O', 'O', 'N', 'O', 'N' },
                               { 'R', 'N', 'N', 'N', 'N', 'G', 'N', 'N', 'N', 'N', 'B', 'N', 'N', 'N', 'B', 'N' },
                               { 'R', 'R', 'R', 'R', 'R', 'G', 'G', 'G', 'G', 'G', 'B', 'B', 'B', 'B', 'B', 'N' },
                               { 'R', 'N', 'N', 'N', 'N', 'G', 'N', 'N', 'N', 'N', 'B', 'N', 'N', 'N', 'B', 'N' } };

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++) {
      switch (inputDisplay[i][j]) {
        case 'R':
          display[i][j] = RED;
          break;
        case 'B':
          display[i][j] = BLUE;
          break;
        case 'G':
          display[i][j] = GREEN;
          break;
        case 'Y':
          display[i][j] = YELLOW;
          break;
        case 'P':
          display[i][j] = PURPLE;
          break;
        case 'W':
          display[i][j] = WHITE;
          break;
        case 'O':
          display[i][j] = ORANGE;
          break;
        case 'C':
          display[i][j] = CYAN;
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

long deltaColourTimeThing = millis();

byte colourIndex = 0;

void cycleColour() {
  ALL_COLOURS[colourIndex].printOut();
  
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++) {
      display[i][j] = ALL_COLOURS[colourIndex];
    }
  }

  colourIndex++;
  if (colourIndex > 9) {
    colourIndex = 0;
  }
}

void updateMenu() {
  awaitInput();
  // long deltaTime = millis() - deltaColourTimeThing;
  // if (deltaTime > 500) {
  //   cycleColour();
  //   deltaColourTimeThing = millis();
  // }
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