#ifndef TETROMINO_H
#define TETROMINO_H
#include <Arduino.h>
#include "Colour.h"

class Tetromino {
private:
  byte positionX;
  byte positionY;
  byte rotation;
  Colour colour;
  int tiles[4];
public:
  Tetromino(Colour colour, int tiles[4]);
  byte getX();
  byte getY();
  byte getRotation();
  int getTiles(byte rotation);
  void setX(byte x);
  void setY(byte y);
  void setRotate(byte r);
  void changeX(byte delta);
  void changeY(byte delta);
};




#endif