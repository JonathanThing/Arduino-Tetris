#include "Game.h"
// 0 I, 1 J, 2 L, 3 O, 4 S, 5 T, 6 Z

byte sevenBag[7] = { 0, 1, 2, 3, 4, 5, 6 };
byte nextPiece = 7;
byte holdPiece = 7;
byte currentIndex = 7;
byte currentPiece = 7;

void funnyFunction() {
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

void initGame(long seed) {
  funnyFunction();
  Serial.println(seed);
  randomSeed(seed);
  randomizeBag();
  nextPiece = sevenBag[0];
  currentIndex = 1;
}

void updateGame() {
  getNextPiece();
}

void randomizeBag() {
  for (int i = 0; i < 7; i++) {
    byte index = random(7);
    byte temp = sevenBag[index];
    sevenBag[index] = sevenBag[i];
    sevenBag[i] = temp;
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
