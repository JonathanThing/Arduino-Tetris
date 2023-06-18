#include "MusicPlayer.h"

const byte numberOfBuzzers = 4;
const byte buzzerPins[numberOfBuzzers] = { 9, 8, 7, 6 };
static Tone buzzers[numberOfBuzzers];
MusicTrack *currentTracks;
byte numberOfTracks;

unsigned long startTime = 0;
unsigned long musicLength = 0;
long deltaSongTime = 0; 
void startMusic();

uint16_t freq[]

byte numberOfTracks = 4;

byte noteIndexCounter[numberOfTracks]; // HARD CODED FIX LATER

void setupMusicPlayer() {
  for (int i = 0; i < numberOfBuzzers; i++) {
    pinMode(buzzerPins[i], OUTPUT);
    buzzers[i].begin(buzzerPins[i]);
  }
}

void changeMusic(byte selection) {
  if (selection == 0) { // Menu - Tetris Theme B
    currentTracks = tracksTetrisMusic;
  } else if (selection == 1) { // Game - Tetris Theme A
    currentTracks = tracksMenuMusic;
  }
  initMusic();
  startMusic();
}

void initMusic() 
  musicLength = currentTracks[0].time[currentTracks[0].trackLength-1];
  for (int i = 1; i < numberOfTracks; i++) { // HARD CODED FIX LATER
    unsigned long tempLength = currentTracks[i].time[currentTracks[i].trackLength-1]
    if (musicLength > tempLength) {
      musicLength = tempLength;
    }
  }
}

void startMusic() {
  for (int i = 0; i < 4; i++) {
    noteIndexCounter[i] = 0;
  }
  startTime = millis();
}

void updateMusicPlayer() {
  deltaSongTime = millis() - startTime;

  if (deltaSongTime > musicLength) {
    startMusic();
  } else {
    for (int i = 0; i < numberOfTracks; i++) {
      if ()
    }
  }
}