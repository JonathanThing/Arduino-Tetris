#include <Tone.h>
#include <LiquidCrystal.h>

// Piezo Buzzers (1-4 Passive, 5 Active)
#define buzzerOne 7 
#define buzzerTwo 6
#define buzzerThree 5
#define buzzerFour 4
#define buzzerFive 3 

Tone buzzers[4];

// LCD
LiquidCrystal lcd(8,9,10,11,12,13);

// Button Input
#define inputChannelOne A1
#define inputChannelTwo A2

// RGB Matrix Ports
// Power      Port L  42-49
// Red    2/2 Port K  A8-A15
// Green  2/2 Port A  22-29
// Blue   2/2 Port C  37-30

// RGB Non Ports
// Red    1/2 21-14
// Green  1/2 38-41 ,50-53
// Blue   1/2 21-20 ,2 ,A3-A7 

// DDRB = B111111111 (1-output, 0-input)
// PORTB = B111111111 

int powerPins[8] = {42,43,44,45,46,47,48,49}; // Not needed, just for completion
// int redPins[16] = {21,20,19,18,17,16,15,14,A8,A9,A10,A11,A12,A13,A14,A15};
// int greenPins[16] = {38,39,40,41,50,51,52,53,22,23,24,25,26,27,28,29};
// int bluePins[16] = {21,20,2,A3,A4,A5,A6,A7,37,36,35,34,33,32,31,30};

int RGBpins[3][16] = {
  {21,20,19,18,17,16,15,14,A8,A9,A10,A11,A12,A13,A14,A15},
  {38,39,40,41,50,51,52,53,22,23,24,25,26,27,28,29},
  {0,1,2,A3,A4,A5,A6,A7,37,36,35,34,33,32,31,30}
};

// Variables
int counter = 0;

void setup() {
  lcd.begin(16,2);

  DDRL = B11111111;
  DDRK = B11111111;
  DDRA = B11111111;
  DDRC = B11111111;

  PORTL = 0;
  PORTK = B11111111;
  PORTA = B11111111;
  PORTC = B11111111;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 8; j++) {
      pinMode(RGBpins[i][j],OUTPUT);
      digitalWrite(RGBpins[i][j], HIGH);
    }
  }
  // Piezo Buzzers
  pinMode(buzzerOne, OUTPUT);
  pinMode(buzzerTwo, OUTPUT);
  pinMode(buzzerThree, OUTPUT);
  pinMode(buzzerFour, OUTPUT);
  pinMode(buzzerFive, OUTPUT);

  buzzers[0].begin(buzzerOne);
  buzzers[1].begin(buzzerTwo);
  buzzers[2].begin(buzzerThree);
  buzzers[3].begin(buzzerFour);

  pinMode(inputChannelOne, INPUT);
  pinMode(inputChannelTwo, INPUT);

}

int red = 255;
int green = 0;
int blue = 255;

const long time = 3333;

void loop() {

  /*

  long redTime = (red*(time)/255.0);

  //Draw Red
  for (int row = 0; row < 8; row++) {
    PORTL = 1 << row;
    for (int col = 0; col < 16; col++) {
      digitalWrite(RGBpins[0][col],LOW);
    }
    delayMicroseconds(redTime/8);
    for (int col = 0; col < 16; col++) {
      digitalWrite(RGBpins[0][col],HIGH);
    }
  }
  delayMicroseconds(time-redTime);

  long greenTime = (green*(time)/255.0);

  //Draw Red
  for (int row = 0; row < 8; row++) {
    PORTL = 1 << row;
    for (int col = 0; col < 16; col++) {
      digitalWrite(RGBpins[1][col],LOW);
    }
    delayMicroseconds(greenTime/8);
    for (int col = 0; col < 16; col++) {
      digitalWrite(RGBpins[1][col],HIGH);
    }
  }
  delayMicroseconds(time-greenTime);

  long blueTime = (blue*(time)/255.0);

  //Draw Red
  for (int row = 0; row < 8; row++) {
    PORTL = 1 << row;
    for (int col = 0; col < 16; col++) {
      digitalWrite(RGBpins[2][col],LOW);
    }
    delayMicroseconds(blueTime/8);
    for (int col = 0; col < 16; col++) {
      digitalWrite(RGBpins[2][col],HIGH);
    }
  }
  delayMicroseconds(time-blueTime);

  */

  // /* Scanning RGB
  for (int colour = 0; colour < 3; colour++) {
    for (int rows = 0; rows < 8; rows++) {
      PORTL = 1 << rows;
      for (int col = 0; col < 16; col++) {
        digitalWrite(RGBpins[colour][col], LOW);
        delay(20);
        digitalWrite(RGBpins[colour][col], HIGH);
      }
    }
  }
  // */

  /* Solid Colour
  for (int colour = 0; colour < 3; colour++) {
    for (int rows = 0; rows < 8; rows++) {
      PORTL = 1 << rows;
      for (int col = 0; col < 16; col++) {
        digitalWrite(RGBpins[colour][col], LOW);
      }
      delay(1);
      for (int col = 0; col < 16; col++) {
        digitalWrite(RGBpins[colour][col], HIGH);
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
}

void handleInput() {
  int channelOne = analogRead(inputChannelOne);
  int channelTwo = analogRead(inputChannelTwo);

  if (channelOne > 900) {
    if (channelOne > 1000) {
      Serial.println("Right");
    } else {
      Serial.println("Left");
    }
  }

  if (channelTwo > 400) {
    if (channelTwo > 1000) {
      Serial.println("Clockwise");
    } else if (channelTwo > 900) {
      Serial.println("CounterClockwise");
    } else if (channelTwo > 700) {
      Serial.println("Soft Drop");
    } else if (channelTwo > 600) {
      Serial.println("Hard Drop");
    } else {
      Serial.println("Hold");
    }
  }
}
