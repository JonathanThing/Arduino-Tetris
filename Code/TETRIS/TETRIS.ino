#include <Tone.h>

#define MAX_INT 65535

/*
TODO:
1. OOP colour class?

*/


const byte numberOfBuzzers = 4;
const byte numberOfButtons = 7;

// Piezo Buzzers
const byte buzzerPins[numberOfBuzzers] = { 9, 8, 7, 6 };
Tone buzzers[numberOfBuzzers];

// Buttons
const byte buttonPins[numberOfButtons] = { 19, 3, 18, 15, 16, 17, 2 };
bool inputs[numberOfButtons] = { 0, 0, 0, 0, 0, 0, 0 };

// RGB Matrix
// Power    Shift Register
// Red 1    Port K (Not inverted)
// Green 1  Port A (Inverted)
// Blue 1   Port F (Not Inverted)
// Red 2    Port L (Inverted)
// Green 2  Port C (Inverted)
// Blue 2   Port B (Inverted)

const byte redPins[8] = { A8, A9, A10, A11, A12, A13, A14, 52 };
const byte greenPins[16] = { 2, 3, 4, 5, 6, 7, 8, 9, 14, 15, 16, 17, 18, 19, 20, 21 };
const byte bluePins[8] = { A0, A1, A2, A3, A4, A5, A6, A7 };

#define dataPin 40
#define shiftClockPin 4
#define storageClockPin 5

struct Colour {
  char symbol;
  byte red;    // 4 bit
  byte green;  // 4 bit
  byte blue;   // 4 bit
};

const Colour RED = { 'R', 16, 0, 0 };
const Colour GREEN = { 'G', 0, 16, 0 };
const Colour BLUE = { 'B', 0, 0, 16 };
const Colour WHITE = { 'W', 16, 16, 16 };
const Colour PURPLE = { 'P', 16, 0, 16 };
const Colour YELLOW = { 'Y', 16, 8, 0 };
const Colour ORANGE = { 'O', 16, 4, 0 };
const Colour CYAN = { 'C', 0, 16, 16 };

Colour colours[8] = { RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE };

byte currentRow = 0;

//Col, Row
Colour display[8][16] = {{ RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE, RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE }, { RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE, RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE }, { RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE, RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE }, { RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE, RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE }, { RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE, RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE }, { RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE, RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE }, { RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE, RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE }, { RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE, RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE }};

const int timePerFrame = 15000;
const int timePerColour = timePerFrame / 3;
const int timePerRow = timePerColour / 8;
const int timePerResolution = (timePerRow - 17 * 16) / 16;

long anchorTime = 0;
long deltaTime = 0;

void setup() {
  randomSeed(32131);
  Serial.begin(9600);
  // Buttons
  for (int i = 0; i < numberOfButtons; i++) {
    pinMode(buttonPins[i], INPUT);
  }

  // Piezo Buzzers
  for (int i = 0; i < numberOfBuzzers; i++) {
    pinMode(buzzerPins[i], OUTPUT);
    buzzers[i].begin(buzzerPins[i]);
  }

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

  digitalWrite(storageClockPin, LOW);
  digitalWrite(shiftClockPin, LOW);
  writeShiftRegister(0);

  

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++) {
      int thing = random(0,8);
      Serial.print(thing);
      Serial.print(" ");
      display[i][j] = colours[thing];
    }
    Serial.println();
  }

  // anchorTime = millis();
}

int redTime = 0;
int blueTime = 0;
int greenTime = 0;

void loop() {

  // deltaTime = millis() - anchorTime;

  for (int i = 0; i < 8; i++) {
    // Red
    displayRed();
    displayGreen();
    displayBlue();

    // writeRed(0);
    // delayMicroseconds(redTime);
    // writeRed(MAX_INT);
    // delayMicroseconds(timePerRow - redTime);

    // // Green
    // writeGreen(0);
    // delayMicroseconds(greenTime);
    // writeGreen(MAX_INT);
    // delayMicroseconds(timePerRow - greenTime);

    // // Blue
    // writeBlue(0);
    // delayMicroseconds(blueTime);
    // writeBlue(MAX_INT);
    // delayMicroseconds(timePerRow - blueTime);

    cyclePower();
  }
}

void displayRed() {
  for (int i = 0; i < 16; i++) {  //Resolution
    int bitMask = 0;
    for (int j = 0; j < 16; j++) {
      bitMask |= (display[currentRow][j].red >= (i + 1));
      if (j != 15) { 
       bitMask <<= 1;
      }
    }
    writeRed(~bitMask);
    delayMicroseconds(timePerResolution);
  }
  writeRed(MAX_INT);
}

void displayGreen() {
  for (int i = 0; i < 16; i++) {  //Resolution
    int bitMask = 0;
    for (int j = 0; j < 16; j++) {
      bitMask |= (display[currentRow][j].green >= (i + 1));
      if (j != 15) { 
       bitMask <<= 1;
      }
    }
    writeGreen(~bitMask);
    delayMicroseconds(timePerResolution);
  }
  writeGreen(MAX_INT);
}

void displayBlue() {
  for (int i = 0; i < 16; i++) {  //Resolution
    int bitMask = 0;
    for (int j = 0; j < 16; j++) {
      bitMask |= (display[currentRow][j].blue >= (i + 1));
      if (j != 15) { 
       bitMask <<= 1;
      }
    }
    writeBlue(~bitMask);
    delayMicroseconds(timePerResolution);
  }
  writeBlue(MAX_INT);
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

void cyclePower() {
  digitalWrite(shiftClockPin, LOW);
  digitalWrite(storageClockPin, LOW);

  if (currentRow == 0) {
    digitalWrite(dataPin, HIGH);
  } else {
    digitalWrite(dataPin, LOW);
  }

  digitalWrite(shiftClockPin, HIGH);
  digitalWrite(storageClockPin, HIGH);

  currentRow++;
  if (currentRow >= 8) {
    currentRow = 0;
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

void writeShiftRegister(byte value) {
  digitalWrite(storageClockPin, LOW);
  digitalWrite(shiftClockPin, LOW);
  for (int i = 7; i >= 0; i--) {
    digitalWrite(dataPin, (value & (1 << i)));
    digitalWrite(shiftClockPin, HIGH);
    digitalWrite(shiftClockPin, LOW);
  }
  digitalWrite(storageClockPin, HIGH);
  digitalWrite(storageClockPin, LOW);
}

void handleInput() {
  for (int i = 0; i < numberOfButtons; i++) {
    inputs[i] = digitalRead(buttonPins[i]);
    Serial.print(inputs[i]);
    Serial.print(" ");
  }
  Serial.println();
}