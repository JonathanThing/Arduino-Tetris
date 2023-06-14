#ifndef TETRS_H
#define TETRS_H
#include <Arduino.h>
#include "Colour.h"
#include "Game.h"
#include "Menu.h"
#include "MusicPlayer.h"

void readInputs();
void setupTetris();
void updateTetris();
void changeGameState(byte state);

extern byte inputs;
extern Colour display[8][16];
extern byte gameState;

#endif