#ifndef TETROMINO_H
#define TETROMINO_H
#include <Arduino.h>
#include "Colour.h"

struct Tetromino {
  char symbol;
  Colour *colour;
  int *tiles;
  Tetromino();
  Tetromino(Colour *colour, int *tiles, char symbol);
  void printRotation(byte rotation);
};

extern const Tetromino L_BLOCK;
extern const Tetromino I_BLOCK;
extern const Tetromino J_BLOCK;
extern const Tetromino O_BLOCK;
extern const Tetromino Z_BLOCK;
extern const Tetromino S_BLOCK;
extern const Tetromino T_BLOCK;

extern const Tetromino blocks[7];

#endif