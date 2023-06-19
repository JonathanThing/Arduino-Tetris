#include "MusicPlayer.h"

MusicTrack *currentTracks;

unsigned long startTime = 0;
unsigned long deltaSongTime = 0;
unsigned long musicLength = 0xFFFFFFFF;

const byte buzzerPins[NUMBER_OF_TRACKS] = { 9, 8, 7, 6 };
Tone buzzers[NUMBER_OF_TRACKS];

int noteIndexCounter[NUMBER_OF_TRACKS];
int currentFreq[NUMBER_OF_TRACKS];
unsigned long currentTime[NUMBER_OF_TRACKS];
int trackLengths[NUMBER_OF_TRACKS];

void startMusic();

void setupMusicPlayer() {
  for (int i = 0; i < NUMBER_OF_TRACKS; i++) {
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
  startMusic();
}

void startMusic() {
  musicLength = 0xFFFFFFFF;
  for (int i = 0; i < NUMBER_OF_TRACKS; i++) {
    // Getting the time of the first notes
    currentTime[i] = pgm_read_dword(&(currentTracks[i].time[0]));

    // Getting frequency of the first notes
    if (currentTime[i] > 0) {  // First note is not at time = 0
      currentFreq[i] = 0;      // Do not play anything
    } else {
      currentFreq[i] = pgm_read_word(&(currentTracks[i].freq[0]));
    }

    // Getting track length
    trackLengths[i] = currentTracks[i].trackLength;

    // Determine total length of the music
    unsigned long tempLength = pgm_read_dword(&(currentTracks[i].time[trackLengths[i] - 1]));
    if (musicLength > tempLength) {
      musicLength = tempLength;
    }

    noteIndexCounter[i] = 0;
    buzzers[i].stop();
  }
  startTime = millis();
}

void updateMusicPlayer() {
  deltaSongTime = millis() - startTime;

  if (deltaSongTime >= musicLength) {  // If song is over, restart
    startMusic();
  } else {
    for (int i = 0; i < NUMBER_OF_TRACKS; i++) {
      if (noteIndexCounter[i] < trackLengths[i]) {  // If track is not complete
        // Playing Frequency
        if (currentFreq[i] > 0) {
          buzzers[i].play(currentFreq[i]);
        } else {
          buzzers[i].stop();
        }

        // If the next note should be played
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