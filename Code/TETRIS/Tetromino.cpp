#include "Tetromino.h"

/*
0123
4567
89AB
CDEF
*/

const int I_BLOCK_TILES[4] = { 0b0000000011110000, 0b0100010001000100, 0b0000111100000000, 0b0010001000100010 };
/*
0000 0010 0000 0100 
1111 0010 0000 0100 
0000 0010 1111 0100 
0000 0010 0000 0100 
*/
const int L_BLOCK_TILES[4] = { 0b0000000001110001, 0b0000001000100110, 0b0000010001110000, 0b0000001100100010 };
/*
1000 0110 0000 0100  
1110 0100 1110 0100 
0000 0100 0010 1100 
0000 0000 0000 0000 
*/
const int J_BLOCK_TILES[4] = { 0b0000000001110100, 0b0000011000100010, 0b0000000101110000, 0b0000001000100011 };
/*
0010 0100 0000 1100  
1110 0100 1110 0100 
0000 0110 1000 0100 
0000 0000 0000 0000 
*/
const int O_BLOCK_TILES[4] = { 0b0000000000110011, 0b0000000000110011, 0b0000000000110011, 0b0000000000110011 };
/*
1100 1100 1100 1100
1100 1100 1100 1100
0000 0000 0000 0000
0000 0000 0000 0000
*/
const int Z_BLOCK_TILES[4] = { 0b0000000001100011, 0b0000001001100100, 0b0000011000110000, 0b0000000100110010 };
/*
1100 0010 0000 0100  
0110 0110 1100 1100 
0000 0100 0110 1000 
0000 0000 0000 0000 
*/
const int S_BLOCK_TILES[4] = { 0b0000000000110110, 0b0000010001100010, 0b0000001101100000, 0b0000001000110001 };
/*
0110 0100 0000 1000  
1100 0110 0110 1100 
0000 0010 1100 0100 
0000 0000 0000 0000 
*/
const int T_BLOCK_TILES[4] = { 0b0000000001110010, 0b0000001001100010, 0b0000001001110000, 0b0000001000110010 };
/*
0100 0100 0000 0100  
1110 0110 1110 1100 
0000 0100 0100 0100 
0000 0000 0000 0000 
*/

const Tetromino I_BLOCK = { &CYAN, I_BLOCK_TILES };
const Tetromino L_BLOCK = { &BLUE, L_BLOCK_TILES };
const Tetromino J_BLOCK = { &ORANGE, J_BLOCK_TILES };
const Tetromino O_BLOCK = { &YELLOW, O_BLOCK_TILES };
const Tetromino Z_BLOCK = { &RED, Z_BLOCK_TILES };
const Tetromino S_BLOCK = { &GREEN, S_BLOCK_TILES };
const Tetromino T_BLOCK = { &PURPLE, T_BLOCK_TILES };

const Tetromino blocks[7] = {I_BLOCK, L_BLOCK, J_BLOCK, O_BLOCK, Z_BLOCK, S_BLOCK, T_BLOCK};

Tetromino::Tetromino(Colour *colour, int *tiles) {
  this->positionX = 0;
  this->positionY = 0;
  this->rotation = 0;
  this->colour = colour;
  this->tiles = tiles;
}

void Tetromino::printOut() {
  Serial.print("Colour: ");
  colour->printOut();
  Serial.println();
}

bool Tetromino::rotate(bool direction) {
  if (direction) {
    rotation++;
    if (rotation >= 4) {
      rotation = 0;
    }
  } else {
    rotation--;
    if (rotation < 0) {
      rotation = 3;
    }
  }

  return true;
}
