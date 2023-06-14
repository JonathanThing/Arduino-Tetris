#include "Game.h"
// 0 I, 2 O, 3 T, 4 J, 5 L, 5 S, 6 Z

// I_BLOCK, O_BLOCK, T_BLOCK, J_BLOCK, L_BLOCK, S_BLOCK, Z_BLOCK
byte sevenBag[7] = { 0, 1, 2, 3, 4, 5, 6 };
long gameTimeAnchor = 0;

bool emptyHold;
byte nextBlockIndex;
Tetromino currentBlock = I_BLOCK; 
Tetromino nextBlock = I_BLOCK;
Tetromino holdBlock = Tetromino();

void randomizeBag();
void getNextBlock();
void getHoldBlock();

byte gameSpace[8][14]; 

void funnyFunction() {
  char inputDisplay[8][16] = { { 'B', 'B', 'W', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'Y', 'O', 'R', 'O', 'Y' },
                               { 'B', 'W', 'W', 'W', 'B', 'B', 'B', 'B', 'W', 'B', 'B', 'Y', 'Y', 'O', 'Y', 'Y' },
                               { 'B', 'B', 'B', 'B', 'R', 'B', 'B', 'W', 'W', 'W', 'B', 'B', 'Y', 'Y', 'Y', 'B' },
                               { 'B', 'B', 'B', 'R', 'P', 'R', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B' },
                               { 'B', 'B', 'R', 'P', 'P', 'P', 'R', 'C', 'C', 'C', 'C', 'C', 'B', 'C', 'C', 'C' },
                               { 'C', 'C', 'C', 'P', 'P', 'P', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C' },
                               { 'G', 'G', 'C', 'G', 'G', 'G', 'C', 'G', 'G', 'G', 'G', 'C', 'G', 'G', 'G', 'G' },
                               { 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G' } };

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++) {
      switch (inputDisplay[i][j]) {
        case 'R':
          display[i][j] = RED;
          break;
        case 'B':
          display[i][j] = BLUE;
          break;
        case 'G':
          display[i][j] = GREEN;
          break;
        case 'Y':
          display[i][j] = YELLOW;
          break;
        case 'P':
          display[i][j] = PURPLE;
          break;
        case 'W':
          display[i][j] = WHITE;
          break;
        case 'O':
          display[i][j] = ORANGE;
          break;
        case 'C':
          display[i][j] = CYAN;
          break;
      }
    }
  }
}

void initGame(long seed) {
  Serial.println(seed);
  randomSeed(seed);
  randomizeBag();
  emptyHold = true;
  nextBlockIndex = 1;
  currentBlock = blocks[sevenBag[0]];
  nextBlock = blocks[sevenBag[nextBlockIndex]];
}

void updateGame() {
  long deltaTime = millis() - gameTimeAnchor;
  if (deltaTime > 1000) {
    gameTimeAnchor = millis();
    currentBlock.printRotation(0);
  } 

  if (deltaTime > 250) {
    if (inputs & 1) {
      getNextBlock();
    } else if (inputs & 2) {
    }
  } 
}

void getNextBlock() {
  currentBlock = nextBlock;
  nextBlock = blocks[sevenBag[nextBlockIndex]];
  nextBlockIndex++;

  if (nextBlockIndex == 7) {
    randomizeBag();
    nextBlockIndex = 0;
  }
}

void randomizeBag() {
  for (int i = 0; i < 7; i++) {
    byte index = random(7);
    byte temp = sevenBag[index];
    sevenBag[index] = sevenBag[i];
    sevenBag[i] = temp;
  }
}

void getHoldBlock() {
  if (emptyHold) {
    emptyHold = false;
    holdBlock = currentBlock;
    getNextPiece();
  } else {
    Tetromino tempBlock = currentBlock;
    currentBlock = holdBlock;
    holdBlock = currentBlock;
  }
}