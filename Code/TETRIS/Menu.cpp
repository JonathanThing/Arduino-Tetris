#include "Menu.h"


long deltaTimeButton = 0;


void setupMenu() {

}

void initMenu() {
  deltaTimeButton = 0;
}
void updateLoseMenu() {
}
void initLoseMenu() {
  deltaTimeButton = 0;  
}

void updateMenu() {
  bool buttonPressed = false;
  for (int i = 0; i < 7; i++) {
    buttonPressed = buttonPressed || (inputs & 1 << 0);
  }
  if (buttonPressed && deltaTimeButton == 0) {
    deltaTimeButton = micros();
  } else if (buttonPressed == 0 && deltaTimeButton > 0) {
    randomSeed(micros() - deltaTimeButton);

    deltaTimeButton = 0;
    gameState = 1;
  }
}