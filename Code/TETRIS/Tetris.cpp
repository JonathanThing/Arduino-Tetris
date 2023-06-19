#include "Tetris.h"

const byte numberOfButtons = 7;
const byte buttonPins[numberOfButtons] = { 19, 3, 18, 15, 16, 17, 2 };

byte gameState;
Colour *display[16][8];
byte inputs = 0;
long anchorSongTime = 0;

void setupTetris() {
  for (int i = 0; i < 7; i++) {
    pinMode(buttonPins[i], INPUT);
  }
  setupMusicPlayer();
  changeGameState(0);  // 0 Menu, 1 Game, 2 Lose
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

  if (millis() - anchorSongTime > 25) { // Update the music every 25ms
    updateMusicPlayer();
    anchorSongTime = millis();
  }
}

void readInputs() {
  inputs = 0;
  for (int i = 0; i < numberOfButtons; i++) {
    inputs |= digitalRead(buttonPins[i]) << i;
  }
}

void changeGameState(byte state) {
  if (state == 0) {
    initMenu();
    gameState = 0;
    changeMusic(0);
  } else if (state == 1) {
    initGame(deltaTimeButton);
    gameState = 1;
    changeMusic(1);
  } else {
    initLoseMenu();
    gameState = 2;
    changeMusic(0);
  }
}

// Convert game space coordinate to screen space (0,0) at bottom left to top left flipped.
// (0,0) --> (15,7), (7,0) --> (15,0), (0,15) --> (0,7), (7,15) --> (0,0)
void writeColour(byte x, byte y, Colour *colour) {
  display[15-y][7-x] = colour;
}
