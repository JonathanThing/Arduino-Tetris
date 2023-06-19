#include "Menu.h"

long deltaTimeButton = 0;
long menuAnchor = 0;

void menuDisplay();
void loseDisplay();

void initMenu() {
  deltaTimeButton = 0;
  menuDisplay();
  menuAnchor = millis();
}

void initLoseMenu() {
  deltaTimeButton = 0;
  loseDisplay();
  menuAnchor = millis();
}

void updateMenu() {
  handleMenuInput();
}

void updateLoseMenu() {
  if (millis() - menuAnchor > 250) { // Delay before game starts reading input
    handleMenuInput();
  }
}

// Measure the button press length
void handleMenuInput() {
  bool buttonPressed = false;
  buttonPressed = (inputs > 0);
  if (buttonPressed && deltaTimeButton == 0) {
    deltaTimeButton = micros();
  } else if (!buttonPressed && deltaTimeButton > 0) {
    changeGameState(1);
  }
}

void menuDisplay() {
  char inputDisplay[16][8] = {
    { 'R', 'R', 'R', 'Y', 'Y', 'Y', 'N', 'N' },
    { 'N', 'R', 'N', 'Y', 'N', 'N', 'N', 'N' },
    { 'N', 'R', 'N', 'Y', 'Y', 'N', 'N', 'N' },
    { 'N', 'R', 'N', 'Y', 'N', 'N', 'N', 'N' },
    { 'N', 'R', 'N', 'Y', 'Y', 'Y', 'N', 'N' },
    { 'G', 'G', 'G', 'P', 'P', 'N', 'N', 'N' },
    { 'N', 'G', 'N', 'P', 'N', 'P', 'N', 'N' },
    { 'N', 'G', 'N', 'P', 'P', 'N', 'N', 'N' },
    { 'N', 'G', 'N', 'P', 'N', 'P', 'N', 'N' },
    { 'N', 'G', 'N', 'P', 'N', 'P', 'N', 'N' },
    { 'B', 'B', 'B', 'O', 'O', 'O', 'N', 'N' },
    { 'N', 'B', 'N', 'O', 'N', 'N', 'N', 'N' },
    { 'N', 'B', 'N', 'O', 'O', 'O', 'N', 'N' },
    { 'N', 'B', 'N', 'N', 'N', 'O', 'N', 'N' },
    { 'B', 'B', 'B', 'O', 'O', 'O', 'N', 'N' },
    { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' }
  };

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++) {
      switch (inputDisplay[j][7 - i]) {
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

void loseDisplay() {
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
      switch (inputDisplay[j][7 - i]) {
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