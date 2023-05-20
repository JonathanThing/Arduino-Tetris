#include <Tone.h>
#include "Colour.h"
#include "RGBMatrix.h"

const byte numberOfBuzzers = 4;
const byte numberOfButtons = 7;

// Piezo Buzzers
const byte buzzerPins[numberOfBuzzers] = {9, 8, 7, 6};
Tone buzzers[numberOfBuzzers];

// Buttons
const byte buttonPins[numberOfButtons] = {19, 3, 18, 15, 16, 17, 2};
bool inputs[numberOfButtons] = {0, 0, 0, 0, 0, 0, 0};

// RGB Matrix
// Power    Shift Register
// Red 1    Port K (Not inverted)
// Green 1  Port A (Inverted)
// Blue 1   Port F (Not Inverted)
// Red 2    Port L (Inverted)
// Green 2  Port C (Inverted)
// Blue 2   Port B (Inverted)

#define dataPin 40
#define shiftClockPin 4
#define storageClockPin 5

// const Colour RED = { 'R', 16, 0, 0 };
// const Colour GREEN = { 'G', 0, 16, 0 };
// const Colour BLUE = { 'B', 0, 0, 16 };
// const Colour WHITE = { 'W', 16, 16, 16 };
// const Colour PURPLE = { 'P', 16, 0, 16 };
// const Colour YELLOW = { 'Y', 16, 8, 0 };
// const Colour ORANGE = { 'O', 16, 4, 0 };
// const Colour CYAN = { 'C', 0, 16, 16 };
// const Colour NONE = {'N', 0, 0, 0}

Colour colours[8] = {R, O, Y, G, C, B, P, W};

long anchorTime = 0;
long deltaTime = 0;

static RGBMatrix screen;

void setup()
{
  randomSeed(1);
  Serial.begin(9600);
  // Buttons
  for (int i = 0; i < numberOfButtons; i++)
  {
    pinMode(buttonPins[i], INPUT);
  }

  // Piezo Buzzers
  for (int i = 0; i < numberOfBuzzers; i++)
  {
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

  screen.init();

  anchorTime = millis();

  for (int i = 0; i < 8; i++)
  {
    colours[i].printOut();
    Serial.println();
  }
}

void loop()
{
  deltaTime = millis() - anchorTime;
  screen.draw();
  delay(2); // About the time delay of game logic (Hopefully)
}

void handleInput()
{
  for (int i = 0; i < numberOfButtons; i++)
  {
    inputs[i] = digitalRead(buttonPins[i]);
  }
}