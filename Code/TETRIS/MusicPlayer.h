#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H
#include <Arduino.h>
#include <Tone.h>
#include "Tetris.h"
#include "MusicTrack.h"
#include "TetrisMusic.h"
#include "MenuMusic.h"


void setupMusicPlayer();
void changeMusic(byte selection);
void updateMusicPlayer();


#endif