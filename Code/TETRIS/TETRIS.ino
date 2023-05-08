#include <Tone.h>

const byte numberOfBuzzers = 4;
const byte numberOfButtons = 7;

// Piezo Buzzers
const byte buzzerPins[numberOfBuzzers] = {13,12,11,10};
Tone buzzers[numberOfBuzzers];

// Buttons
const byte buttonPins[numberOfButtons] = {23,27,31,41,33,37,25};
bool inputs[numberOfButtons] = {0,0,0,0,0,0,0};

// RGB Matrix 
// Power    34,32,30,28,36,38,40,42    
// Red 1    A8,A9,A10,A11,A12,A13,A14,52  
// Green 1  21,20,19,18,17,16,15,14
// Blue 1   A0,A1,A2,A3,A4,A5,A6,A7
// Red 2 & Blue 2   Shift Register
// Green 2  9,8,7,6,5,4,3,2

// Temporary RED 53,35,39,43,45,47,49,51

const byte powerPins[8] = {28,26,24,22,30,32,34,36}; // Col (From user's POV)

const byte redPins[8] = {A8,A9,A10,A11,A12,A13,A14,52};
const byte greenPins[16] = {2,3,4,5,6,7,8,9,14,15,16,17,18,19,20,21};
const byte bluePins[8] = {A0,A1,A2,A3,A4,A5,A6,A7};

#define blueDataPin 44
#define blueShiftClockPin 42
#define blueStorageClockPin 40

#define redDataPin 50
#define redShiftClockPin 46
#define redStorageClockPin 48

struct Colour {
  byte red;
  byte green;
  byte blue;
};

const Colour RED =  {255,0,0};
const Colour GREEN = {255,0,0};
const Colour BLUE = {0,0,255};
const Colour WHITE = {255,255,255};
const Colour PURPLE = {255,0,255};
const Colour YELLOW = {255,100,0};
const Colour ORANGE = {255,25,0};
const Colour CYAN = {0,255,255};

//Col, Row 
Colour display [8][16];

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A15));

  // Buttons
  for (int i = 0; i < 7; i++) {
    pinMode(buttonPins[i],INPUT);
  }

  // Piezo Buzzers
  for (int i = 0; i < 4; i++) {
    pinMode(buzzerPins[i],OUTPUT);
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

  writeShiftRegister(pow(2,8), blueDataPin, blueShiftClockPin, blueStorageClockPin);

}

void loop() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(powerPins[i],HIGH);
    drawRed();
  }
}

void writeShiftRegister(byte value, byte dataPin, byte shiftClockPin, byte storageClockPin) {
  digitalWrite(storageClockPin, LOW);
  digitalWrite(shiftClockPin, LOW);  
  for (int i = 7; i >= 0; i--) {
    digitalWrite(dataPin, value & (1<<i));  
    digitalWrite(shiftClockPin, HIGH);  
    digitalWrite(shiftClockPin, LOW);
  }
  digitalWrite(storageClockPin, HIGH);
  digitalWrite(storageClockPin, LOW);
}


void drawRed(int ledStates) {
  writeShiftRegister(ledStates>>7, redDataPin, redShiftClockPin, redStorageClockPin);
  for(int i = 8; i < 16; i++) {
    if(i == 0) {
      digitalWrite(redPins[15],HIGH);
    } else {
      digitalWrite(redPins[i-1],HIGH);
    }
    digitalWrite(redPins[i],LOW);
    delay(100);
  }
}

void drawBlue(int ledStates) {
  for (int i = 0; i < 8; i++) {
    writeShiftRegister(ledStates>>7, blueDataPin, blueShiftClockPin, blueStorageClockPin);
  }
  for(int i = 8; i < 16; i++) {
   s // digitalWrite(bluePins[i],~(ledStates & ()));
  }

}

void drawGreen(int ledStates) {
  for(int i = 0; i < 16; i++) {
    digitalWrite(greenPin[i], ~(ledStates & 1<<i));
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

