#include <Tone.h>

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
  byte red;
  byte green;
  byte blue;
};

const Colour RED = { 255, 0, 0 };
const Colour GREEN = { 255, 0, 0 };
const Colour BLUE = { 0, 0, 255 };
const Colour WHITE = { 255, 255, 255 };
const Colour PURPLE = { 255, 0, 255 };
const Colour YELLOW = { 255, 128, 0 };
const Colour ORANGE = { 255, 30, 0 };
const Colour CYAN = { 0, 255, 255 };

byte currentRow = 0;

//Col, Row
Colour display[8][16];

const int timePerFrame = 15000;
const int timePerColour = timePerFrame / 3;
const int timePerRow = timePerColour / 8;

long anchorTime = 0;
long deltaTime = 0;

void setup() {
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

  // anchorTime = millis();
}

void loop() {
  // deltaTime = millis() - anchorTime;

  cyclePower();
  handleInput();
  delay(50);
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

void writeShiftRegister(byte value) {
  digitalWrite(storageClockPin, LOW);
  digitalWrite(shiftClockPin, LOW);
  for (int i = 7; i >= 0; i--) {
    digitalWrite(dataPin, (value & (1<<i)));
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