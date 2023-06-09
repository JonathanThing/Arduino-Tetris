#ifndef GAME_H
#define GAME_H
#include <Arduino.h>
#include "Tetris.h"
#include "Tetromino.h"

void updateGame();
void getNextPiece();
void randomizeBag();
void initGame(long seed);

#endif