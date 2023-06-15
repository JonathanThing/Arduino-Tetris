#ifndef MENU_H
#define MENU_H
#include <Arduino.h>
#include "Tetris.h"
#include "Colour.h"

void initMenu();
void initLoseMenu();
void updateMenu();
void updateLoseMenu();
void handleMenuInput();

extern long deltaTimeButton;

#endif