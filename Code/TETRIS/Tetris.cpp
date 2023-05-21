#include "Tetris.h"

const byte numberOfButtons = 7;

// Buttons
const byte buttonPins[numberOfButtons] = { 19, 3, 18, 15, 16, 17, 2 };
bool inputs[numberOfButtons] = { 0, 0, 0, 0, 0, 0, 0 };

long anchorTime = 0;
long deltaTime = 0;

long deltaButtonTime = 0;

Tetris::Tetris() {
  gameState = 0;  // 0 Menu, 1 Game, 2 Lose
  anchorTime = millis();
  // Buttons
  for (int i = 0; i < numberOfButtons; i++) {
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

void handleInput() {
  for (int i = 0; i < numberOfButtons; i++) {
    inputs[i] = digitalRead(buttonPins[i]);
  }
}

// 0 I, 1 J, 2 L, 3 O, 4 S, 5 T, 6 Z

byte sevenBag[7] = { 0, 1, 2, 3, 4, 5, 6 };
byte nextPiece = 7;
byte holdPiece = 7;
byte currentIndex = 7;
byte currentPiece = 7;

void randomizeBag() {
  for (int i = 0; i < 7; i++) {
    byte index = random(7);
    byte temp = sevenBag[index];
    sevenBag[index] = sevenBag[i];
    sevenBag[i] = temp;
  }

  for (int i = 0; i < 7; i++) {
    Serial.print(sevenBag[i]);
  }
}

void getNextPiece() {
  if (currentIndex == 7) {
    randomizeBag();
    currentIndex = 0;
  } 

  currentPiece = nextPiece;
  nextPiece = sevenBag[currentIndex];
  currentIndex++;
}

void Tetris::menuUpdate() {
  bool buttonPressed = false;
  for (int i = 0; i < numberOfButtons; i++) {
    buttonPressed = buttonPressed || digitalRead(buttonPins[i]);
  }
  if (buttonPressed && deltaButtonTime == 0) {
    deltaButtonTime = micros();
  } else if (buttonPressed == 0 && deltaButtonTime > 0) {
    randomSeed(micros() - deltaButtonTime);
    randomizeBag();
    nextPiece = sevenBag[0];
    currentIndex = 1;
    deltaButtonTime = 0;
    gameState = 1;
  }
}

void Tetris::gameUpdate() {
  getNextPiece();
}

void Tetris::loseUpdate() {
}


void Tetris::update() {
  handleInput();
  if (gameState == 0) {
    menuUpdate();
  } else if (gameState == 1) {
    gameUpdate();
  } else {
    loseUpdate();
  }
}

byte Tetris::getGameState() {
  return gameState;
}

Colour (&Tetris::getDisplay())[8][16] {
  return display;
}