#include "Game.h"

const byte startX = 2;
const byte startY = 13;
const int defaultFallTime = 750;
int currentX = startX;
int currentY = startY;
byte currentRotation = 0;

long score = 0;
int totalLinesRemoved = 0;
int timePerFall = defaultFallTime;

byte sevenBag[7] = { 0, 1, 2, 3, 4, 5, 6 };

long inputAnchorTime = 0;  // Anchor time for user input
long fallAnchorTime = 0;   // Anchor time for falling
byte nextBlockIndex;

bool gameLost;
bool canHold;
bool emptyHold;
bool placeBlockGracePeriod;

Tetromino currentBlock = I_BLOCK;
Tetromino nextBlock = I_BLOCK;
Tetromino holdBlock = Tetromino();

char gameSpace[8][14];


void removeLines();
void adjustFallSpeed();
void randomizeBag();
void getNextBlock();
void getHoldBlock();
bool checkCollision(int x, int y, byte rotation);
int findLowestSpot();
void placeBlock();
void handleGameInput();
void moveX(int deltaX);
void moveY(int deltaY);
void rotateBlock(bool clockwise);
void hardDrop();
void drawHoldBlock();
void drawNextBlock();
void drawCurrentBlock();
void drawOutlineBlock();
void drawGameSpace();
void endGame();

void initGame(long seed) {
  // Randomizing the game
  Serial.print("Seed: ");
  Serial.println(seed);
  randomSeed(seed);
  randomizeBag();

  // Reseting Variables
  gameLost = false;
  emptyHold = true;
  canHold = true;
  nextBlockIndex = 1;
  currentBlock = blocks[sevenBag[0]];
  nextBlock = blocks[sevenBag[nextBlockIndex]];
  score = 0;
  totalLinesRemoved = 0;
  timePerFall = defaultFallTime;

  // Clearing game space
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 14; j++) {
      gameSpace[i][j] = 0;
    }
  }
}

void updateGame() {
  long inputDeltaTime = millis() - inputAnchorTime;
  long fallDeltaTime = millis() - fallAnchorTime;

  if (fallDeltaTime > timePerFall) {
    fallAnchorTime = millis();
    moveY(-1);
  }
  if (inputDeltaTime > 250) {
    handleGameInput();
    if (inputs > 0) {  // If a button was pressed
      inputAnchorTime = millis();
    }
  }

  drawHoldBlock();
  drawNextBlock();
  drawGameSpace();
  drawOutlineBlock();
  drawCurrentBlock();

  if (gameLost) {
    endGame();
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

  // Reset Values for new Block
  placeBlockGracePeriod = true;
  canHold = true;
  currentX = startX;
  currentY = startY;
  currentRotation = 0;
  fallAnchorTime = millis();
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

    // Reset Values for new Block
    placeBlockGracePeriod = true;
    currentX = startX;
    currentY = startY;
    currentRotation = 0;
    fallAnchorTime = millis();
  }
}

void handleGameInput() {
  if (inputs & 1 << 0) {  // Right
    moveX(1);
  } else if (inputs & 1 << 1) {  // Left
    moveX(-1);
  } else if (inputs & 1 << 2) {  // Clockwise
    rotateBlock(true);
  } else if (inputs & 1 << 3) {  // Counter Clockwise
    rotateBlock(false);
  } else if (inputs & 1 << 4) {  // Soft Drop
    moveY(-1);
  } else if (inputs & 1 << 5) {  // Hard Drop
    hardDrop();
  } else if (inputs & 1 << 6) {  // Hold Block
    getHoldBlock();
  }
}

// Given parameters, check if currentBlock can be there
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
  if (currentX == startX && currentY == startY) {  // If you lose
    gameLost = true;
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
}

// Remove Full lines and handles the effects of it
void removeLines() {
  // Remove Lines
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

  // Update Score, totalLinesremoved, and fall speed
  totalLinesRemoved += numberOfLines;
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

  // Update Display
  char tempArray[8][14];

  // Create temporary array
  for (int i = 0; i < lineIndex; i++) {
    for (int x = 0; x < 8; x++) {
      tempArray[x][i] = gameSpace[x][remainingLines[i]];
    }
  }
  for (int i = lineIndex; i < 14; i++) {
    for (int x = 0; x < 8; x++) {
      tempArray[x][i] = 0;
    }
  }

  // Trasnfer temporary array to gamespace
  for (int y = 0; y < 14; y++) {
    for (int x = 0; x < 8; x++) {
      gameSpace[x][y] = tempArray[x][y];
    }
  }
}

// Find the lowestY the current block can go to
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

void hardDrop() {
  currentY = findLowestSpot();
  placeBlock();
}

void adjustFallSpeed() {
  timePerFall = defaultFallTime - 25 * (totalLinesRemoved % 8);
}

void drawNextBlock() {
  for (int rows = 0; rows < 2; rows++) {
    for (int cols = 0; cols < 4; cols++) {
      if (nextBlock.tiles[0] & (1 << (rows * 4 + cols))) {
        writeColour(4 + cols, 15 - rows, nextBlock.colour);
      } else {
        writeColour(4 + cols, 15 - rows, &GREY);
      }
    }
  }
}

void drawHoldBlock() {
  for (int rows = 0; rows < 2; rows++) {
    for (int cols = 0; cols < 4; cols++) {
      if (!emptyHold && holdBlock.tiles[0] & (1 << (rows * 4 + cols))) {
        writeColour(cols, 15 - rows, holdBlock.colour);
      } else {
        writeColour(cols, 15 - rows, &GREY);
      }
    }
  }
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

// Transfer gameSpace array to display array
void drawGameSpace() {
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

void endGame() {
  Serial.print("Score: ");
  Serial.print(score);
  Serial.print("\tLines: ");
  Serial.println(totalLinesRemoved);
  changeGameState(2);
}