#include "Menu.h"

Menu::Menu() {
}

void Menu::init() {
  deltaTimeButton = 0;
}
void Menu::loseUpdate(byte inputs) {
}
void Menu::loseInit() {
  deltaTimeButton = 0;  
}

void Menu::update(byte inputs) {
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