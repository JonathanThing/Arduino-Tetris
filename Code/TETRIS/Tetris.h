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
void writeColour(byte x, byte y, Colour *colour);

extern byte inputs;
extern Colour *display[16][8];
extern byte gameState;

#endif