#include "MusicPlayer.h"

const byte numberOfBuzzers = 4;
const byte buzzerPins[numberOfBuzzers] = { 9, 8, 7, 6 };
Tone buzzers[numberOfBuzzers];

MusicTrack *currentTracks;

unsigned long startTime = 0;
unsigned long musicLength = 0xFFFFFFFF;
unsigned long deltaSongTime = 0;

int currentFreq[NUMBER_OF_TRACKS];
unsigned long currentTime[NUMBER_OF_TRACKS];
int trackLengths[NUMBER_OF_TRACKS];

void startMusic();
void initMusic();

int noteIndexCounter[NUMBER_OF_TRACKS];

void setupMusicPlayer() {
  for (int i = 0; i < numberOfBuzzers; i++) {
    pinMode(buzzerPins[i], OUTPUT);
    buzzers[i].begin(buzzerPins[i]);
  }
}

void changeMusic(byte selection) {
  if (selection == 0) {  // Menu - Tetris Theme B
    currentTracks = tracksMenuMusic;
  } else if (selection == 1) {  // Game - Tetris Theme A
    currentTracks = tracksTetrisMusic;
  }
  initMusic();
  startMusic();
}

void initMusic() {
  musicLength = 0xFFFFFFFF;
  for (int i = 0; i < NUMBER_OF_TRACKS; i++) {
    currentTime[i] = pgm_read_dword(&(currentTracks[i].time[0]));
    if (currentTime[i] > 0) {
      currentFreq[i] = 0;
      Serial.println(i);
    } else {
      currentFreq[i] = pgm_read_word(&(currentTracks[i].freq[0]));
    }
    trackLengths[i] = currentTracks[i].trackLength;
    unsigned long tempLength = pgm_read_dword(&(currentTracks[i].time[trackLengths[i] - 1]));
    if (musicLength > tempLength) {
      musicLength = tempLength;
    }
    noteIndexCounter[i] = 0;
    buzzers[i].stop();
  }
  Serial.println(musicLength);
}

void startMusic() {
  startTime = millis();
}

void updateMusicPlayer() {
  deltaSongTime = millis() - startTime;
  if (deltaSongTime > musicLength) {
    initMusic();
    startMusic();
  } else {
    for (int i = 0; i < NUMBER_OF_TRACKS; i++) {
      if (noteIndexCounter[i] < trackLengths[i]) {
        if (currentFreq[i] > 0) {
          buzzers[i].play(currentFreq[i]);
        } else {
          buzzers[i].stop();
        }

        if (deltaSongTime >= currentTime[i]) {
          noteIndexCounter[i]++;
          if (noteIndexCounter[i] < trackLengths[i]) {
            currentFreq[i] = pgm_read_word(&(currentTracks[i].freq[noteIndexCounter[i] - 1]));
            currentTime[i] = pgm_read_dword(&(currentTracks[i].time[noteIndexCounter[i]]));
          }
        }
      } else {
        buzzers[i].stop();
      }
    }
  }
}