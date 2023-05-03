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

// RGB
byte red = 0;
byte green = 8;
byte blue = 0;

const long timeBetweenFrames = 15000;
const long timePerRow = timeBetweenFrames/8; 
const long timePerCycle = timePerRow/15; 
const long timePerColour = timePerCycle/3; 
  
void loop() {

  for (int row = 0; row < 8; row++) {
    PORTL = 1 << row;

  }

  /* Scanning RGB
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
  */

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
  // lcd.clear();
  // lcd.setCursor(0, 0);
  // lcd.print("I die now");
  // lcd.setCursor(0, 1);
  // for (int i = 0; i < 4; i++) {
  //   if (buzzers[i].isPlaying()) {
  //     lcd.print("Y  ");
  //   } else {
  //     lcd.print("N  ");
  //   }
  // }

  switch(counter/100){
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
  if (counter > 400) {
    counter = 0;
    lcd.clear();
  }
  */

  // delay(50);

  // handleInput();

  //Buttons Input
}

void handleInput() {
  int channelOne = analogRead(inputChannelOne);
  int channelTwo = analogRead(inputChannelTwo);

  lcd.clear();

  if (channelOne > 900) {
    lcd.setCursor(0, 0);
    if (channelOne > 1000) {
      lcd.print("Right");
      digitalWrite(buzzerFive, HIGH);
      delay(100);
      digitalWrite(buzzerFive, LOW);
    } else {
      lcd.print("Left");
    }
  }

  if (channelTwo > 400) {
    lcd.setCursor(0, 0);
    if (channelTwo > 1000) {
      lcd.print("Clockwise");
    } else if (channelTwo > 900) {
      lcd.print("CounterClockwise");
    } else if (channelTwo > 700) {
      lcd.print("Soft Drop");
    } else if (channelTwo > 600) {
      lcd.print("Hard Drop");
    } else {
      lcd.print("Hold");
    }
  }
}
