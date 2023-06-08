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
  void setRotation(byte r);
  bool changeX(byte delta);
  bool changeY(byte delta);
  bool rotate(bool direction);
  Colour getColour();
};

extern const Tetromino L_BLOCK;
extern const Tetromino I_BLOCK;
extern const Tetromino J_BLOCK;
extern const Tetromino O_BLOCK;
extern const Tetromino Z_BLOCK;
extern const Tetromino S_BLOCK;
extern const Tetromino T_BLOCK;


#endif