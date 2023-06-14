#include "Game.h"
// 0 I, 1 O, 2 T, 3 J, 4 L, 5 S, 6 Z

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
void drawNextBlock();

byte gameSpace[8][14];

void clearDisplay() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 2; j++) {
      display[i][j] = &GREY;
    }
  }

  for (int i = 0; i < 8; i++) {
    for (int j = 2; j < 16; j++) {
      display[i][j] = &BLACK;
    }
  }
}

int test = 0;

void printBlocks() {
  Serial.print("Current: ");
  Serial.print(currentBlock.symbol);
  Serial.print(" ");
  currentBlock.colour->printOut();
  Serial.print(" ");
  currentBlock.printRotation(test);
  Serial.print("\tNext: ");
  Serial.print(nextBlock.symbol);
  Serial.print(" ");
  nextBlock.colour->printOut();
  Serial.print(" ");
  nextBlock.printRotation(test);
  Serial.println();
}

void initGame(long seed) {
  clearDisplay();
  Serial.println(seed);
  randomSeed(seed);
  randomizeBag();
  emptyHold = true;
  nextBlockIndex = 1;
  currentBlock = blocks[sevenBag[0]];
  nextBlock = blocks[sevenBag[nextBlockIndex]];
  printBlocks();
  drawNextBlock();
}

void updateGame() {
  long deltaTime = millis() - gameTimeAnchor;
  if (deltaTime > 250) {
    if (inputs & 1) {
      getNextBlock();
    } else if (inputs & 2) {
      test++;
      if (test > 4) {
        test = 0;
      }
    }
    if (inputs > 0) {
      gameTimeAnchor = millis();
      printBlocks();
      drawNextBlock();
    }
  }
}

void drawNextBlock() {
  for (int rows = 0; rows < 2; rows++) {
    for (int cols = 0; cols < 4; cols++) {
      if (nextBlock.tiles[0] & (1<<(rows*4 + cols))){
        display[3-cols][rows] = nextBlock.colour;
      } else {
        display[3-cols][rows] = &GREY;
      }
    }
  }
}

void getNextBlock() {
  currentBlock = nextBlock;
  nextBlockIndex++;
    if (nextBlockIndex == 7) {
    randomizeBag();
    nextBlockIndex = 0;
  }
  nextBlock = blocks[sevenBag[nextBlockIndex]];
}

void randomizeBag() {
  for (int i = 0; i < 7; i++) {
    byte index = random(7);
    byte temp = sevenBag[index];
    sevenBag[index] = sevenBag[i];
    sevenBag[i] = temp;
  }

  // Serial.println();

  // for(int i = 0; i < 7; i++) {
  //   Serial.print(sevenBag[i]);
  //   Serial.print(" ");
  // }

  // Serial.println();
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