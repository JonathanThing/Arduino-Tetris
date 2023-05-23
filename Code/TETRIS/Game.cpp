#include "Game.h"
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

void update() {
  getNextPiece();
}

void initGame() {
  randomizeBag();
  nextPiece = sevenBag[0];
  currentIndex = 1;
}