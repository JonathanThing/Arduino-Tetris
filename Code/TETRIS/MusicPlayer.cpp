#include "MusicPlayer.h"

const byte numberOfBuzzers = 4;
const byte buzzerPins[numberOfBuzzers] = { 9, 8, 7, 6 };
static Tone buzzers[numberOfBuzzers];

void setupMusicPlayer() {
  for (int i = 0; i < numberOfBuzzers; i++) {
    pinMode(buzzerPins[i], OUTPUT);
    buzzers[i].begin(buzzerPins[i]);
  }
}

void updateMusicPlayer() {
  
}