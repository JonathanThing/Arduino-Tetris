#include "RGBMatrix.h"
#include "Colour.h"

const int MAX_INT = 65535;
const int timePerFrame = 15000;
const int timePerColour = timePerFrame / 3;
const int timePerRow = timePerColour / 8;
const int timePerResolution = (timePerRow - 17 * 16) / 16;

byte currentRow = 0;

#define dataPin 40
#define shiftClockPin 4
#define storageClockPin 5

// RGB Matrix
// Power    Shift Register
// Red 1    Port K (Not inverted)
// Green 1  Port A (Inverted)
// Blue 1   Port F (Not Inverted)
// Red 2    Port L (Inverted)
// Green 2  Port C (Inverted)
// Blue 2   Port B (Inverted)


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
void writeColour(int selection, int value) {
  if (selection == 0) {  // Red
    PORTL = (byte)(value >> 8 & 255);
    PORTK = reverseByte((byte)value);  // PORT K IS NOT INVERTED
  } else if (selection == 1) {         // Blue
    PORTC = (byte)(value >> 8 & 255);
    PORTA = (byte)(value);
  } else {  // Green
    PORTB = (byte)(value >> 8 & 255);
    PORTF = reverseByte((byte)value);  // PORT F IS NOT INVERTED
  }
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

// 4 - 8 microsecond length
void cyclePower() {
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


RGBMatrix::RGBMatrix() {
  DDRA = B11111111;
  DDRB = B11111111;
  DDRC = B11111111;
  DDRF = B11111111;
  DDRK = B11111111;
  DDRL = B11111111;

  PORTA = B11111111;
  PORTB = B11111111;
  PORTC = B11111111;
  PORTF = B11111111;
  PORTK = B11111111;
  PORTL = B11111111;

  pinMode(dataPin, OUTPUT);
  pinMode(storageClockPin, OUTPUT);
  pinMode(shiftClockPin, OUTPUT);
  writeShiftRegister(0);
  currentRow = 0;
}

void drawDisplay(Colour (&display)[8][16]) {
  for (int c = 0; c < 3; c++) {
    for (int i = 0; i < 8; i++) {  // Resolution
      int bitMask = 0;
      for (int j = 0; j < 16; j++) {
        bitMask |= (display[currentRow][j].getColour(c) >= (i + 1));
        if (j != 15) {
          bitMask <<= 1;
        }
      }
      writeColour(c, ~bitMask);
      delayMicroseconds(timePerResolution);
    }
    writeColour(c, MAX_INT);
  }
}

void RGBMatrix::draw(Colour (&display)[8][16]) {
  for (int i = 0; i < 8; i++) {
    cyclePower();
    drawDisplay(display);
  }
}