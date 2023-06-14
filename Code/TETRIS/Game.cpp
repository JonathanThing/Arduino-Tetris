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
void drawCurrentBlock();

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

byte blockX = 0;
byte blockY = 0;
byte rotation = 0;

void printBlocks() {
  Serial.print("Current: ");
  Serial.print(currentBlock.symbol);
  Serial.print(" ");
  currentBlock.colour->printOut();
  Serial.print(" ");
  currentBlock.printRotation(rotation);
  Serial.print("\tNext: ");
  Serial.print(nextBlock.symbol);
  Serial.print(" ");
  nextBlock.colour->printOut();
  Serial.print(" ");
  nextBlock.printRotation(rotation);
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

// 0 right, 1 left, 2 clockwise, 3 counter clockwise, 4 soft drop, 5 hard drop, 6 hold

void updateGame() {
  long deltaTime = millis() - gameTimeAnchor;
  if (deltaTime > 250) {
    if (inputs & 1<<4) {
      getNextBlock();
      printBlocks();
    } else if (inputs & 1<<3) {
      rotation++;
      if (rotation > 3) {
        rotation = 0;
      }
    } else if (inputs & 1<<2) {
      rotation--;
      if (rotation > 3) {
        rotation = 3;
      }
    } else if (inputs & 1<<0) {
      blockX--;
    } else if (inputs & 1<<1) {
      blockX++;
    } else if (inputs & 1<<5) {
      blockY++;
    }

    if (inputs > 0) {
      gameTimeAnchor = millis();
      drawNextBlock();
      drawCurrentBlock();
      Serial.println(rotation);
    }
  }
}

void drawCurrentBlock() {
  for (int rows = 0; rows < 4; rows++) {
    for (int cols = 0; cols < 4; cols++) {
      byte screenX = blockX+cols+4;
      byte screenY = blockY+rows;

      if (currentBlock.tiles[rotation] & (1<<(rows*4 + cols)) && (17 >= screenY && screenY >= 0) && (7 >= screenX && screenX >= 0)) {
        display[screenX][screenY] = currentBlock.colour;
      } else {
        display[screenX][screenY] = &BLACK;
      }
    }
  }
}

void drawNextBlock() {
  for (int i = 0; i < 8; i++) {
      for (int j = 2; j < 16; j++) {
        display[i][j] = &BLACK;
      }
    }
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