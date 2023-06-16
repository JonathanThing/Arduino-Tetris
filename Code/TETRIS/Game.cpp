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
void handleGameInput();
void moveX(int deltaX);
void moveY(int deltaY);
void rotateBlock(bool clockwise);
void hardDrop();
void drawOutlineBlock();
bool checkCollision(int x, int y, byte rotation);
int findLowestSpot();
void placeBlock();
void updateGameScreen();

char gameSpace[8][14];

void clearDisplay() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 2; j++) {
      writeColour(i, j, &BLACK);
    }
  }

  for (int i = 0; i < 8; i++) {
    for (int j = 2; j < 16; j++) {
      writeColour(i, j, &BLACK);
    }
  }
}

int currentX = 3;
int currentY = 13;
byte currentRotation = 0;

void printBlocks() {
  Serial.print("Current: ");
  Serial.print(currentBlock.symbol);
  Serial.print(" ");
  currentBlock.colour->printOut();
  Serial.print(" ");
  currentBlock.printRotation(currentRotation);
  Serial.print("\tNext: ");
  Serial.print(nextBlock.symbol);
  Serial.print(" ");
  nextBlock.colour->printOut();
  Serial.print(" ");
  nextBlock.printRotation(currentRotation);
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
  updateGameScreen();
  drawCurrentBlock();

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 14; j++) {
      gameSpace[i][j] = 0;
    }
  }
}

// 0 right, 1 left, 2 clockwise, 3 counter clockwise, 4 soft drop, 5 hard drop, 6 hold

long moveAnchorTime = 0;

void updateGame() {
  long deltaTime = millis() - gameTimeAnchor;
  long moveDeltaTime = millis() - moveAnchorTime;

  if (moveDeltaTime > 750) {
    moveAnchorTime = millis();
    moveY(-1);
  }
  if (deltaTime > 250) {
    handleGameInput();
    if (inputs > 0) {

      gameTimeAnchor = millis();
    }
  }
  updateGameScreen();
  drawOutlineBlock();
  drawCurrentBlock();
  drawNextBlock();
}

void drawCurrentBlock() {
  for (int rows = 0; rows < 4; rows++) {
    for (int cols = 0; cols < 4; cols++) {
      int screenX = currentX + cols;
      int screenY = currentY - rows;

      if ((17 >= screenY) && (7 >= screenX)) {
        if (currentBlock.tiles[currentRotation] & (1 << (rows * 4 + cols))) {
          writeColour(screenX, screenY, currentBlock.colour);
        }
      }
    }
  }
}

void drawNextBlock() {
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 4; x++) {
      writeColour(x, 15 - y, &BLACK);
    }
  }
  for (int rows = 0; rows < 2; rows++) {
    for (int cols = 0; cols < 4; cols++) {
      if (nextBlock.tiles[0] & (1 << (rows * 4 + cols))) {
        writeColour(4 + cols, 15 - rows, nextBlock.colour);
      } else {
        writeColour(4 + cols, 15 - rows, &BLACK);
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
}

void getHoldBlock() {
  if (emptyHold) {
    emptyHold = false;
    holdBlock = currentBlock;
    getNextBlock();
  } else {
    Tetromino tempBlock = currentBlock;
    currentBlock = holdBlock;
    holdBlock = currentBlock;
  }
}

void handleGameInput() {
  if (inputs & 1 << 0) {
    moveX(1);
  } else if (inputs & 1 << 1) {
    moveX(-1);
  } else if (inputs & 1 << 2) {
    rotateBlock(true);
  } else if (inputs & 1 << 3) {
    rotateBlock(false);
  } else if (inputs & 1 << 4) {
    moveY(-1);
  } else if (inputs & 1 << 5) {
    hardDrop();
  } else if (inputs & 1 << 6) {
    getNextBlock();
    // getHoldBlock();
  }
}

bool checkCollision(int x, int y, byte rotation) {
  for (int rows = 0; rows < 4; rows++) {
    for (int cols = 0; cols < 4; cols++) {
      int tileX = x + cols;
      int tileY = y - rows;

      if (currentBlock.tiles[rotation] & (1 << (rows * 4 + cols))) {
        if (!(0 <= tileY && tileY <= 13 && 0 <= tileX && tileX <= 7) || gameSpace[tileX][tileY] > 0) {
          return false;
        }
      }
    }
  }

  return true;
}

void moveX(int deltaX) {
  int tempX = currentX + deltaX;
  if (checkCollision(tempX, currentY, currentRotation)) {
    currentX += deltaX;
    Serial.print(currentX);
    Serial.print(" ");
    Serial.println(currentY);
  }
}

void moveY(int deltaY) {
  int tempY = currentY + deltaY;
  if (checkCollision(currentX, tempY, currentRotation)) {
    currentY += deltaY;
  } else {
    placeBlock();
  }
}

void rotateBlock(bool clockwise) {
  byte tempRotation = currentRotation;
  if (clockwise) {
    tempRotation++;
    if (tempRotation > 3) {
      tempRotation = 0;
    }
  } else {
    tempRotation--;
    if (tempRotation > 3) {
      tempRotation = 3;
    }
  }

  if (checkCollision(currentX, currentY, tempRotation)) {
    currentRotation = tempRotation;
  }
}

void placeBlock() {
  for (int rows = 0; rows < 4; rows++) {
    for (int cols = 0; cols < 4; cols++) {
      int tileX = currentX + cols;
      int tileY = currentY - rows;

      if (currentBlock.tiles[currentRotation] & (1 << (rows * 4 + cols))) {
        gameSpace[tileX][tileY] = currentBlock.symbol;
      }
    }
  }

  getNextBlock();
  currentX = 3;
  currentY = 13;
  currentRotation = 0;
}

void updateGameScreen() {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 14; y++) {
      switch (gameSpace[x][y]) {
        case 'S':
          writeColour(x, y, &RED);
          break;
        case 'L':
          writeColour(x, y, &BLUE);
          break;
        case 'Z':
          writeColour(x, y, &GREEN);
          break;
        case 'O':
          writeColour(x, y, &YELLOW);
          break;
        case 'T':
          writeColour(x, y, &PURPLE);
          break;
        case 'J':
          writeColour(x, y, &ORANGE);
          break;
        case 'I':
          writeColour(x, y, &CYAN);
          break;
        case 0:
          writeColour(x, y, &BLACK);
          break;
      }
    }
  }
}

void clearLines() {

}

void hardDrop() {

}

void drawOutlineBlock() {
  int lowestY = findLowestSpot();
    for (int rows = 0; rows < 4; rows++) {
    for (int cols = 0; cols < 4; cols++) {
      byte tileX = currentX + cols;
      byte tileY = lowestY - rows;

      if ((17 >= tileY) && (7 >= tileY)) {
        if (currentBlock.tiles[currentRotation] & (1 << (rows * 4 + cols))) {
          writeColour(tileX, tileY, &GREY);
        }
      }
    }
  }
}

int findLowestSpot() {
  int lowestY = currentY;

  while (checkCollision(currentX, lowestY, currentRotation)) {
    lowestY--;
  }
  lowestY++;

  return lowestY;
}


