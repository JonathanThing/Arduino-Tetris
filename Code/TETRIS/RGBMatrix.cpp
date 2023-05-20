#include "RGBMatrix.h"

const int MAX_INT = 65535;
const int timePerFrame = 15000;
const int timePerColour = timePerFrame / 3;
const int timePerRow = timePerColour / 8;
const int timePerResolution = (timePerRow - 17 * 16) / 16;

// 2 microsecond length
byte reverseByte(byte input) {
  byte output = input;
  for (int i = 0; i < 8; i++) {
    output <<= 1;
    output |= input & 1;
    input >>= 1;
  }
  return output;
}

// LEFT MSB 1000000010000000 LSB RIGHT
void writeRed(int value) {
  PORTL = (byte)(value >> 8 & 255);
  PORTK = reverseByte((byte)value);  // PORT K IS NOT INVERTED
}

void writeGreen(int value) {
  PORTC = (byte)(value >> 8 & 255);
  PORTA = (byte)(value);
}

void writeBlue(int value) {
  PORTB = (byte)(value >> 8 & 255);
  PORTF = reverseByte((byte)value);  // PORT F IS NOT INVERTED
}

RGBMatrix::RGBMatrix() {
  Colour display[8][16] = {{B, B, W, B, B, B, B, B, B, B, B, Y, O, R, O, Y},
                         {B, W, W, W, B, B, B, B, W, B, B, Y, Y, O, Y, Y},
                         {B, B, B, B, R, B, B, W, W, W, B, B, Y, Y, Y, B},
                         {B, B, B, R, P, R, B, B, B, B, B, B, B, B, B, B},
                         {B, B, R, P, P, P, R, C, C, C, C, C, B, C, C, C},
                         {C, C, C, P, P, P, C, C, C, C, C, C, C, C, C, C},
                         {G, G, C, G, G, G, C, G, G, G, G, C, G, G, G, G},
                         {G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G}};
  currentRow = 0;
}

void RGBMatrix::displayRed() {
  for (int i = 0; i < 8; i++) {  // Resolution
    int bitMask = 0;
    for (int j = 0; j < 16; j++) {
      bitMask |= (display[currentRow][j].getRed() >= (i + 1));
      if (j != 15) {
        bitMask <<= 1;
      }
    }
    writeRed(~bitMask);
    delayMicroseconds(timePerResolution);
  }
  writeRed(MAX_INT);
}

void RGBMatrix::displayGreen() {
  for (int i = 0; i < 8; i++) {  // Resolution
    int bitMask = 0;
    for (int j = 0; j < 16; j++) {
      bitMask |= (display[currentRow][j].getGreen() >= (i + 1));
      if (j != 15) {
        bitMask <<= 1;
      }
    }
    writeGreen(~bitMask);
    delayMicroseconds(timePerResolution);
  }
  writeGreen(MAX_INT);
}

void RGBMatrix::displayBlue() {
  for (int i = 0; i < 8; i++) {  // Resolution
    int bitMask = 0;
    for (int j = 0; j < 16; j++) {
      bitMask |= (display[currentRow][j].getBlue() >= (i + 1));
      if (j != 15) {
        bitMask <<= 1;
      }
    }
    writeBlue(~bitMask);
    delayMicroseconds(timePerResolution);
  }
  writeBlue(MAX_INT);
}

void writeDataPin(bool value) {
  if (value) {
    PORTG = PORTG | B00000010;
  } else {
    PORTG = PORTG & B11111101;
  }
}

void writeShiftClockPin(bool value) {
  if (value) {
    PORTG = PORTG | B00100000;
  } else {
    PORTG = PORTG & B11011111;
  }
}

void writeStorageClockPin(bool value) {
  if (value) {
    PORTE = PORTE | B00001000;
  } else {
    PORTE = PORTE & B11110111;
  }
}

// Idk length
void writeShiftRegister(byte value) {
  for (int i = 7; i >= 0; i--) {
    writeDataPin(value & (1 << i));
    writeShiftClockPin(HIGH);
    writeShiftClockPin(LOW);
  }
  writeStorageClockPin(HIGH);
  writeStorageClockPin(LOW);
}

// 4 - 8 microsecond length
void RGBMatrix::cyclePower() {
  currentRow++;
  if (currentRow >= 8) {
    currentRow = 0;
  }

  writeShiftClockPin(LOW);
  writeStorageClockPin(LOW);
  writeDataPin(currentRow == 0);
  writeShiftClockPin(HIGH);
  writeStorageClockPin(HIGH);
}

void RGBMatrix::init() {
  writeShiftRegister(0);
}

void RGBMatrix::draw() {
  for (int i = 0; i < 8; i++) {
    cyclePower();
    displayRed();
    displayGreen();
    displayBlue();
  }
}
