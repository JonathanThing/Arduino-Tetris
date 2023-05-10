#include <Tone.h>
#include <SPI.h>

#define writeHigh(port, bit) (port) |= (1<<(bit))
#define writeLow(port, bit) (port) &= ~(1<<bit))

const byte numberOfBuzzers = 4;
const byte numberOfButtons = 7;

// Piezo Buzzers
const byte buzzerPins[numberOfBuzzers] = { 13, 12, 11, 10 };
Tone buzzers[numberOfBuzzers];

// Buttons
const byte buttonPins[numberOfButtons] = { 23, 27, 31, 41, 33, 37, 25 };
bool inputs[numberOfButtons] = { 0, 0, 0, 0, 0, 0, 0 };

// RGB Matrix
// Power    34,32,30,28,36,38,40,42
// Red 1    A8,A9,A10,A11,A12,A13,A14,52
// Green 1  21,20,19,18,17,16,15,14
// Blue 1   A0,A1,A2,A3,A4,A5,A6,A7
// Red 2 & Blue 2   Shift Register
// Green 2  9,8,7,6,5,4,3,2

// Temporary RED 53,35,39,43,45,47,49,51

const byte powerPins[8] = { 30, 28, 26, 24, 32, 34, 36, 38 };  // Col (From user's POV)

const byte redPins[8] = { A8, A9, A10, A11, A12, A13, A14, 52 };
const byte greenPins[16] = { 2, 3, 4, 5, 6, 7, 8, 9, 14, 15, 16, 17, 18, 19, 20, 21 };
const byte bluePins[8] = { A0, A1, A2, A3, A4, A5, A6, A7 };

#define blueDataPin 44
#define blueShiftClockPin 42
#define blueStorageClockPin 40

#define redDataPin 50
#define redShiftClockPin 48
#define redStorageClockPin 46

struct Colour {
  byte red;
  byte green;
  byte blue;
};

const Colour RED = { 8, 0, 0 };
const Colour GREEN = { 8, 0, 0 };
const Colour BLUE = { 0, 0, 8 };
const Colour WHITE = { 8, 8, 8 };
const Colour PURPLE = { 8, 0, 8 };
const Colour YELLOW = { 8, 3, 0 };
const Colour ORANGE = { 8, 1, 0 };
const Colour CYAN = { 0, 8, 8 };

//Col, Row
Colour display[8][16];

const int timePerFrame = 15000;
const int timePerColour = timePerFrame / 3;
const int timePerRow = timePerColour / 8;
const int timePerResolution = timePerRow / 8;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A15));

  // Buttons
  for (int i = 0; i < numberOfButtons; i++) {
    pinMode(buttonPins[i], INPUT);
  }

  // Piezo Buzzers
  for (int i = 0; i < numberOfBuzzers; i++) {
    pinMode(buzzerPins[i], OUTPUT);
    buzzers[i].begin(buzzerPins[i]);
  }

  //RGB Matrix
  pinMode(redDataPin, OUTPUT);
  pinMode(redShiftClockPin, OUTPUT);
  pinMode(redStorageClockPin, OUTPUT);

  pinMode(blueDataPin, OUTPUT);
  pinMode(blueShiftClockPin, OUTPUT);
  pinMode(blueStorageClockPin, OUTPUT);

  for (int i = 0; i < 8; i++) {
    pinMode(powerPins[i], OUTPUT);
    digitalWrite(powerPins[i], LOW);
    pinMode(redPins[i], OUTPUT);
    digitalWrite(redPins[i], HIGH);
    pinMode(greenPins[i], OUTPUT);
    digitalWrite(greenPins[i], HIGH);
    pinMode(bluePins[i], OUTPUT);
    digitalWrite(bluePins[i], HIGH);
  }

  for (int i = 8; i < 16; i++) {
    pinMode(greenPins[i], OUTPUT);
    digitalWrite(greenPins[i], HIGH);
  }

  writeShiftRegister(0, redDataPin, redShiftClockPin, redStorageClockPin);
  writeShiftRegister(0, blueDataPin, blueShiftClockPin, blueStorageClockPin);
}


void loop() {
  // long start = micros();
  //2,3,4,5,6,7,8,9,14,15,16,17,18,19,20,21
  // for (int i = 0; i< 16; i++) {
  //   overhead();
  // }
  // Serial.println(micros()-start);
  delay(500);
  // drawGraphics();
}

void drawGraphics() {
  for (int i = 0; i < 8; i++) {
    if (i == 0) {
      digitalWrite(powerPins[7], LOW);
    } else {
      digitalWrite(powerPins[i - 1], LOW);
    }
    digitalWrite(powerPins[i], HIGH);
    drawGreen(i * 8);
    // drawGreen(i);
    // drawBlue(i);
  }
}

void writeShiftRegister(byte value, byte dataPin, byte shiftClockPin, byte storageClockPin) {
  // digitalWrite(storageClockPin, LOW);
  // digitalWrite(shiftClockPin, LOW);
  Serial.println(value, BIN);
  for (int i = 0; i < 8; i++) {
    digitalWrite(dataPin, !(value & 1 << (7 - i)));
    digitalWrite(shiftClockPin, HIGH);
    digitalWrite(shiftClockPin, LOW);
  }
  digitalWrite(storageClockPin, HIGH);
  digitalWrite(storageClockPin, LOW);
}

// void drawGreen(long value) {
//   long timeValue = (value*timePerRow/56.0);
//   if (timeValue != 0) {
//     for (int j = 0; j < 16; j++) {
//       digitalWrite(greenPins[j], LOW);
//     }
//   }
//   delayMicroseconds(timeValue);
//     for (int j = 0; j < 16; j++) {
//     digitalWrite(greenPins[j], HIGH);
//   }
//   delayMicroseconds(timePerRow-timeValue);
// }


void drawRed(int ledStates) {
  writeShiftRegister(ledStates, redDataPin, redShiftClockPin, redStorageClockPin);
  for (int i = 0; i < 8; i++) {
    digitalWrite(redPins[i], !(ledStates & 1 << (i + 8)));
  }
}

// void drawBlue(int ledStates) {
//   writeShiftRegister(ledStates, blueDataPin, blueShiftClockPin, blueStorageClockPin);
//   for (int i = 0; i < 8; i++) {
//     digitalWrite(bluePins[i],!(ledStates & 1<<(i+8)));
//   }
// }

void drawGreen(int ledStates) {
  for (int i = 0; i < 16; i++) {
    digitalWrite(greenPins[i], !(ledStates & (1 << i)));
  }
}

void handleInput() {
  for (int i = 0; i < numberOfButtons; i++) {
    inputs[i] = digitalRead(buttonPins[i]);
  }
}

// long redTime = (red*(time)/255.0);

// //Draw Red
// for (int row = 0; row < 8; row++) {
//   PORTL = 1 << row;
//   for (int col = 0; col < 16; col++) {
//     digitalWrite(RGBpins[0][col],LOW);
//   }
//   delayMicroseconds(redTime/8);
//   for (int col = 0; col < 16; col++) {
//     digitalWrite(RGBpins[0][col],HIGH);
//   }
// }
// delayMicroseconds(time-redTime);

// long greenTime = (green*(time)/255.0);

// //Draw Red
// for (int row = 0; row < 8; row++) {
//   PORTL = 1 << row;
//   for (int col = 0; col < 16; col++) {
//     digitalWrite(RGBpins[1][col],LOW);
//   }
//   delayMicroseconds(greenTime/8);
//   for (int col = 0; col < 16; col++) {
//     digitalWrite(RGBpins[1][col],HIGH);
//   }
// }
// delayMicroseconds(time-greenTime);

// long blueTime = (blue*(time)/255.0);

// //Draw Red
// for (int row = 0; row < 8; row++) {
//   PORTL = 1 << row;
//   for (int col = 0; col < 16; col++) {
//     digitalWrite(RGBpins[2][col],LOW);
//   }
//   delayMicroseconds(blueTime/8);
//   for (int col = 0; col < 16; col++) {
//     digitalWrite(RGBpins[2][col],HIGH);
//   }
// }
// delayMicroseconds(time-blueTime);

/*  Changing screen 
  for (int colour = 0; colour < 300; colour++) {
    for (int rows = 0; rows < 8; rows++) {
      PORTL = 1 << rows;
      for (int col = 0; col < 16; col++) {
        digitalWrite(RGBpins[colour/100][col], LOW);
      }
      delay(2);
      for (int col = 0; col < 16; col++) {
        digitalWrite(RGBpins[colour/100][col], HIGH);
      }
    }
  }
  */

/* LCD and Piezo
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("I die now");
  lcd.setCursor(0, 1);
  for (int i = 0; i < 4; i++) {
    if (buzzers[i].isPlaying()) {
      lcd.print("Y  ");
    } else {
      lcd.print("N  ");
    }
  }

  switch(counter/10){
    case 0:
      digitalWrite(buzzerFive,LOW);
      buzzers[0].play(NOTE_C4, 1000);
      break;
    case 1:
      buzzers[1].play(NOTE_D4, 1000);
      break;
    case 2:
      buzzers[2].play(NOTE_E4, 1000);
      break;
    case 3:
      buzzers[3].play(NOTE_F4, 1000);
      break;
    case 4:
      digitalWrite(buzzerFive,HIGH);
      break;
  }

  counter++;
  if (counter > 40) {
    counter = 0;
  }
  */

// delay(100);
// handleInput();

//Buttons Input