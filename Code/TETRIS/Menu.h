#ifndef MENU_H
#define MENU_H
#include <Arduino.h>
#include "Tetris.h"

void initMenu();
void initLoseMenu();
void updateMenu();
void updateLoseMenu();
void awaitInput();

extern long deltaTimeButton;

#endif