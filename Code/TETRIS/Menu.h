#ifndef MENU_H
#define MENU_H
#include <Arduino.h>
#include "Colour.h"

class Menu {
private:
  long deltaTimeButton;
public:
  Menu();
  void update(byte inputs);
  void init();
  void loseUpdate(byte inputs);
  void loseInit();
};
#endif