#include "RGBMatrix.h"

#define MAX_INT 65535
#define dataPin 40
#define shiftClockPin 4
#define storageClockPin 5

byte currentRow;

// Local Functions
void cyclePower();
void drawRow();
void writeColour(int colour, int value);
void writeShiftRegister(byte value);
// Helper Functions
void writeDataPin(bool value);
void writeShiftClockPin(bool value);
void writeStorageClockPin(bool value);
byte reverseByte(byte input);

void drawDisplay() {
  for (int i = 0; i < 8; i++) {
    cyclePower();
    drawRow();
  }
}

void setupRGBMatrix() {
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

// RGB Matrix
// Power    Shift Register
// Red 1    Port K (Not inverted) MSB
// Green 1  Port A (Inverted) LSB
// Blue 1   Port F (Not Inverted) MSB
// Red 2    Port L (Inverted) LSB
// Green 2  Port C (Inverted) LSB
// Blue 2   Port B (Inverted) LSB
void writeColour(int colour, int value) {
  if (colour == 0) {  // Red
    PORTL = (byte)(value >> 8 & 255);
    PORTK = reverseByte((byte)value);  // PORT K IS NOT INVERTED
  } else if (colour == 1) {            // Green
    PORTC = (byte)(value >> 8 & 255);
    PORTA = (byte)(value);
  } else {  // Blue
    PORTB = (byte)(value >> 8 & 255);
    PORTF = reverseByte((byte)value);  // PORT F IS NOT INVERTED
  }
}

void writeShiftRegister(byte value) {
  for (int i = 7; i >= 0; i--) {
    writeDataPin(value & (1 << i));
    writeShiftClockPin(LOW);
    writeShiftClockPin(HIGH);
  }
  writeStorageClockPin(LOW);
  writeStorageClockPin(HIGH);
}

void drawRow() {
  for (int colour = 0; colour < 3; colour++) {
    for (int i = 0; i < COLOUR_MAX_VALUE; i++) {  // Resolution
      int bitMask = 0;
      for (int j = 0; j < 16; j++) {
        bitMask |= (display[currentRow][j]->getColour(colour) >= (i + 1));
        if (j != 15) {
          bitMask <<= 1;
        }
      }
      writeColour(colour, ~bitMask);
      // if(colour == 0) {
      //   delayMicroseconds(50);
      // }
    }
    writeColour(colour, MAX_INT);
  }
}

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

byte reverseByte(byte input) {
  byte output = input;
  for (int i = 0; i < 8; i++) {
    output <<= 1;
    output |= input & 1;
    input >>= 1;
  }
  return output;
}
