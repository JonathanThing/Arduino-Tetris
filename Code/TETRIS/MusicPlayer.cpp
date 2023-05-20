#include "MusicPlayer.h"

const byte numberOfBuzzers = 4;
// Piezo Buzzers
const byte buzzerPins[numberOfBuzzers] = { 9, 8, 7, 6 };
static Tone buzzers[numberOfBuzzers];

MusicPlayer::MusicPlayer() {
  // Piezo Buzzers
  for (int i = 0; i < numberOfBuzzers; i++) {
    pinMode(buzzerPins[i], OUTPUT);
    buzzers[i].begin(buzzerPins[i]);
  }
  // // This code is needed for the rgbmatrix to not break, Idk why
  buzzers[0].play(440, 1);
  buzzers[1].play(440, 1);
  buzzers[2].play(440, 1);
  buzzers[3].play(440, 1);
}

void MusicPlayer::update() {
  
}