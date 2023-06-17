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
          display[j][i] = &RED;
          break;
        case 'B':
          display[j][i] = &BLUE;
          break;
        case 'G':
          display[j][i] = &GREEN;
          break;
        case 'Y':
          display[j][i] = &YELLOW;
          break;
        case 'P':
          display[j][i] = &PURPLE;
          break;
        case 'W':
          display[j][i] = &WHITE;
          break;
        case 'O':
          display[j][i] = &ORANGE;
          break;
        case 'C':
          display[j][i] = &CYAN;
          break;
        case 'N':
          display[j][i] = &BLACK;
          break;
      }
    }
  }
}

void menuFunnyFunctionDie() {
  char inputDisplay[16][8] = {
    { 'G', 'G', 'G', 'N', 'N', 'Y', 'N', 'N' },
    { 'G', 'N', 'N', 'N', 'Y', 'N', 'Y', 'N' },
    { 'G', 'N', 'G', 'N', 'Y', 'Y', 'Y', 'N' },
    { 'G', 'G', 'G', 'N', 'Y', 'N', 'Y', 'N' },
    { 'B', 'N', 'B', 'N', 'P', 'P', 'P', 'N' },
    { 'B', 'B', 'B', 'N', 'P', 'N', 'N', 'N' },
    { 'B', 'N', 'B', 'N', 'P', 'P', 'N', 'N' },
    { 'B', 'N', 'B', 'N', 'P', 'P', 'P', 'N' },
    { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },
    { 'C', 'C', 'C', 'N', 'O', 'N', 'O', 'N' },
    { 'C', 'N', 'C', 'N', 'O', 'N', 'O', 'N' },
    { 'C', 'C', 'C', 'N', 'N', 'O', 'N', 'N' },
    { 'R', 'R', 'R', 'N', 'W', 'W', 'N', 'N' },
    { 'R', 'N', 'N', 'N', 'W', 'N', 'W', 'N' },
    { 'R', 'R', 'N', 'N', 'W', 'W', 'N', 'N' },
    { 'R', 'R', 'R', 'N', 'W', 'N', 'W', 'N' }
  };

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++) {
      switch (inputDisplay[j][7-i]) {
        case 'R':
          display[j][i] = &RED;
          break;
        case 'B':
          display[j][i] = &BLUE;
          break;
        case 'G':
          display[j][i] = &GREEN;
          break;
        case 'Y':
          display[j][i] = &YELLOW;
          break;
        case 'P':
          display[j][i] = &PURPLE;
          break;
        case 'W':
          display[j][i] = &WHITE;
          break;
        case 'O':
          display[j][i] = &ORANGE;
          break;
        case 'C':
          display[j][i] = &CYAN;
          break;
        case 'N':
          display[j][i] = &BLACK;
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
  menuFunnyFunctionDie();
}


/*
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

// long deltaTime = millis() - deltaColourTimeThing;
// if (deltaTime > 500) {
//   cycleColour();
//   deltaColourTimeThing = millis();
// }
*/

void updateMenu() {
  menuFunnyFunction();
  handleMenuInput();
}

void updateLoseMenu() {
  menuFunnyFunctionDie();
  handleMenuInput();
}

void handleMenuInput() {
  bool buttonPressed = false;
  buttonPressed = (inputs > 0);
  if (buttonPressed && deltaTimeButton == 0) {
    deltaTimeButton = micros();
  } else if (!buttonPressed && deltaTimeButton > 0) {
    changeGameState(1);
  }
}