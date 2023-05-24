#ifndef TETRS_H
#define TETRS_H
#include <Arduino.h>
#include "Colour.h"
#include "Game.h"
#include "Menu.h"

void readInputs();

void setupTetris();
void updateTetris();
byte getGameState();
void changeGameState(byte state);

extern byte inputs;
extern byte gameState;

#endif