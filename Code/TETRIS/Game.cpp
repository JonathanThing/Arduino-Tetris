#include "Game.h"

const byte startX = 2;
const byte startY = 13;

byte sevenBag[7] = { 0, 1, 2, 3, 4, 5, 6 };
long gameTimeAnchor = 0;
bool canHold;
bool emptyHold;
byte nextBlockIndex;
Tetromino currentBlock = I_BLOCK;
Tetromino nextBlock = I_BLOCK;
Tetromino holdBlock = Tetromino();
bool placeBlockGracePeriod = true;

void randomizeBag();
void getNextBlock();
void getHoldBlock();
void drawNextBlock();
void drawHoldBlock();
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
void removeLines();
void adjustFallSpeed();
char gameSpace[8][14];

const int defaultFallTime = 750;

long score = 0;
int linesRemoved = 0;
int timePerFall = defaultFallTime;


void clearDisplay() {
  for (int i = 0; i < 8; i++) {
    for (int j = 14; j < 16; j++) {
      writeColour(i, j, &GREY);
    }
  }
}

int currentX = startX;
int currentY = startY;
byte currentRotation = 0;

void initGame(long seed) {
  Serial.print("Seed: ");
  Serial.println(seed);
  clearDisplay();
  randomSeed(seed);
  randomizeBag();
  emptyHold = true;
  canHold = true;
  nextBlockIndex = 1;
  currentBlock = blocks[sevenBag[0]];
  nextBlock = blocks[sevenBag[nextBlockIndex]];
  drawNextBlock();
  drawHoldBlock();
  updateGameScreen();
  drawCurrentBlock();

  score = 0;
  linesRemoved = 0;
  timePerFall = defaultFallTime;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 14; j++) {
      gameSpace[i][j] = 0;
    }
  }
}

// 0 right, 1 left, 2 clockwise, 3 counter clockwise, 4 soft drop, 5 hard drop, 6 hold

long moveAnchorTime = 0;

void updateGame() {
  clearDisplay();
  long deltaTime = millis() - gameTimeAnchor;
  long moveDeltaTime = millis() - moveAnchorTime;

  if (moveDeltaTime > timePerFall) {
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
  drawHoldBlock();
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
  for (int rows = 0; rows < 2; rows++) {
    for (int cols = 0; cols < 4; cols++) {
      if (nextBlock.tiles[0] & (1 << (rows * 4 + cols))) {
        writeColour(4 + cols, 15 - rows, nextBlock.colour);
      }
    }
  }
}

void drawHoldBlock() {
  if (!emptyHold) {
    for (int rows = 0; rows < 2; rows++) {
      for (int cols = 0; cols < 4; cols++) {
        if (holdBlock.tiles[0] & (1 << (rows * 4 + cols))) {
          writeColour(cols, 15 - rows, holdBlock.colour);
        }
      }
    }
  }
}

void getNextBlock() {
  placeBlockGracePeriod = true;
  moveAnchorTime = millis();
  canHold = true;
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
  if (canHold) {
    if (emptyHold) {
      emptyHold = false;
      holdBlock = currentBlock;
      getNextBlock();
    } else {
      Tetromino tempBlock = currentBlock;
      currentBlock = holdBlock;
      holdBlock = tempBlock;
      canHold = false;
    }
    currentX = startX;
    currentY = startY;
    currentRotation = 0;
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
    getHoldBlock();
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
  }
}

void moveY(int deltaY) {
  int tempY = currentY + deltaY;
  if (checkCollision(currentX, tempY, currentRotation)) {
    currentY += deltaY;
  } else {
    if (!placeBlockGracePeriod || (currentX == startX && currentY == startY)) {
      placeBlock();
    }
    placeBlockGracePeriod = false;
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
  if (currentX == startX && currentY == startY) {
    clearDisplay();
    Serial.print("Score: ");
    Serial.print(score);
    Serial.print("\tLines: ");
    Serial.println(linesRemoved);
    changeGameState(2);
    return;
  }

  for (int rows = 0; rows < 4; rows++) {
    for (int cols = 0; cols < 4; cols++) {
      int tileX = currentX + cols;
      int tileY = currentY - rows;

      if (currentBlock.tiles[currentRotation] & (1 << (rows * 4 + cols))) {
        gameSpace[tileX][tileY] = currentBlock.symbol;
      }
    }
  }

  removeLines();
  getNextBlock();
  currentX = startX;
  currentY = startY;
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

void removeLines() {
  byte remainingLines[14];
  byte numberOfLines = 0;
  byte lineIndex = 0;
  for (int y = 0; y < 14; y++) {
    bool full = true;
    for (int x = 0; x < 8; x++) {
      if (gameSpace[x][y] == 0) {
        full = false;
        break;
      }
    }
    if (full) {
      numberOfLines++;
    } else {
      remainingLines[lineIndex] = y;
      lineIndex++;
    }
  }

  linesRemoved += numberOfLines;
  adjustFallSpeed();

  switch (numberOfLines) {
    case 1:
    score += 100;
    break;
    case 2:
    score += 300;
    break;
    case 3:
    score += 500;
    break;
    case 4:
    score += 800;
    break;
  }

  char displayTemp[8][14];
  for (int i = 0; i < lineIndex; i++) {
    for (int x = 0; x < 8; x++) {
      displayTemp[x][i] = gameSpace[x][remainingLines[i]];
    }
  }
  for (int i = lineIndex; i < 14; i++) {
    for (int x = 0; x < 8; x++) {
      displayTemp[x][i] = 0;
    }
  }

  for (int y = 0; y < 14; y++) {
    for (int x = 0; x < 8; x++) {
      gameSpace[x][y] = displayTemp[x][y];
    }
  }
}

void hardDrop() {
  currentY = findLowestSpot();
  placeBlock();
}

void drawOutlineBlock() {
  int lowestY = findLowestSpot();
  for (int rows = 0; rows < 4; rows++) {
    for (int cols = 0; cols < 4; cols++) {
      byte tileX = currentX + cols;
      byte tileY = lowestY - rows;

      if ((17 >= tileX) && (7 >= tileX)) {
        if (currentBlock.tiles[currentRotation] & (1 << (rows * 4 + cols))) {
          writeColour(tileX, tileY, &GREY);
        }
      }
    }
  }
}

int findLowestSpot() {
  int lowestY = currentY;
  if (!checkCollision(currentX, lowestY, currentRotation)) {
    return lowestY;
  } else {
    while (checkCollision(currentX, lowestY, currentRotation)) {
      lowestY--;
    }
    lowestY++;
    return lowestY;
  }
}

void adjustFallSpeed() {
  timePerFall = defaultFallTime - 25 * (linesRemoved%8);
}