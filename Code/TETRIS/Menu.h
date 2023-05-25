#ifndef MENU_H
#define MENU_H
#include <Arduino.h>
#include "Tetris.h"

void setupMenu();
void updateMenu();
void initMenu();
void updateLoseMenu();
void initLoseMenu();

extern long deltaTimeButton;

#endif