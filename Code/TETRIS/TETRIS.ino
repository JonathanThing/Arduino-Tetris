#include <Tone.h>
#include <LiquidCrystal.h>

// Passive Piezo Buzzers 
#define buzzerOne 6 
#define buzzerTwo 5
#define buzzerThree 4
#define buzzerFour 3

Tone buzzers[4];

int buttonPins[7] = {13,12,11,10,9,8,7};

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
  {2,A1,A2,A3,A4,A5,A6,A7,37,36,35,34,33,32,31,30}
};

void setup() {
  Serial.begin(9600);

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

  buzzers[0].begin(buzzerOne);
  buzzers[1].begin(buzzerTwo);
  buzzers[2].begin(buzzerThree);
  buzzers[3].begin(buzzerFour);

  for (int i = 0; i < 7; i++) {
    pinMode(buttonPins[i],INPUT);
  }
}

const long timeBetweenFrames = 15000;
const long timePerRow = timeBetweenFrames/8; 
const long timePerColour = timePerRow/3; 
  
int rgb[8][3] = {{255,255,255},{255,0,0},{0,255,0},{0,0,255},{255,0,255},{255,25,0},{255,100,0},{0,255,255}};

void loop() {

  // for (int z = 0; z < 170; z++) {
  //   for (int row = 0; row < 8; row++) {
  //     PORTL = 1 << row;
  //     for (int colour = 0; colour < 3; colour++) {
  //       long time = rgb[row][colour]/255.0*timePerColour;
  //       if (time > 0) {
  //         for (int i = 0; i < z/10; i++) {
  //           digitalWrite(RGBpins[colour][i], LOW);
  //         }
  //         delayMicroseconds(time);
  //         for (int i = 0; i < z/10; i++) {
  //           digitalWrite(RGBpins[colour][i], HIGH);
  //         }
  //       }
  //       delayMicroseconds(timePerColour-time);
  //     }
  //   }
  // }

  delay(100);
  handleInput();
}

void handleInput() {
  for (int i = 0; i < 7; i++) {
    Serial.print(digitalRead(buttonPins[i]));
    Serial.print(" ");
  }
  Serial.println();
}


