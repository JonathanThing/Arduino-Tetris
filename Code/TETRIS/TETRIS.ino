#include <Tone.h>
#include <LiquidCrystal.h>

// Passive Piezo Buzzers 
#define buzzerOne 6 
#define buzzerTwo 5
#define buzzerThree 4
#define buzzerFour 3

Tone buzzers[4];

int sevenSegGround[4] = {7,8,9,10};

#define sevenSegData 11
#define sevenSegClock 13
#define sevenSegShift 12

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

  for (int i = 0; i < 4; i++) {
    pinMode(sevenSegGround[i], OUTPUT);
    digitalWrite(sevenSegGround[i], HIGH);
  }
  pinMode(sevenSegData, OUTPUT);  
  pinMode(sevenSegClock, OUTPUT);
  pinMode(sevenSegShift, OUTPUT);

  // Piezo Buzzers
  pinMode(buzzerOne, OUTPUT);
  pinMode(buzzerTwo, OUTPUT);
  pinMode(buzzerThree, OUTPUT);
  pinMode(buzzerFour, OUTPUT);

  buzzers[0].begin(buzzerOne);
  buzzers[1].begin(buzzerTwo);
  buzzers[2].begin(buzzerThree);
  buzzers[3].begin(buzzerFour);

  pinMode(inputChannelOne, INPUT);
  pinMode(inputChannelTwo, INPUT);

  for (int i = 0; i < 4; i++) {
    digitalWrite(sevenSegGround[i], LOW);
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


  writeSevenSeg(8, 0);


  handleInput();

}

void handleInput() {
  int channelOne = analogRead(inputChannelOne);
  int channelTwo = analogRead(inputChannelTwo);

  if (channelOne > 850) {
    Serial.println(channelOne);
    if (channelOne > 950) {

    } else {
    }
  }

  if (channelTwo > 300) {
    Serial.println(channelTwo);
    if (channelTwo > 1000) {

    } else if (channelTwo > 900) {

    } else if (channelTwo > 700) {

    } else if (channelTwo > 600) {

    } else {

    }
  }
}

// 0 1 2 3 4 5 6 7 8 9 I O T S Z J L
const int SevenSegSymbols[17] = {B1111110,B0110000,B1101101,B1111001,B0110011,B1011011,B1011111,B1110000,B1111111,B1111011,B0000110,B0011101,B0000111,B1011011,B1101101,B0001110,B0111000};

void writeSevenSeg(int value, bool includeDecimal) {
  for(int i = 0; i < 8; i++) {
    digitalWrite(sevenSegData, LOW);
    pulsePin(sevenSegClock);
  }
  pulsePin(sevenSegShift);

  digitalWrite(sevenSegData, includeDecimal); 
  pulsePin(sevenSegClock);
  for(int i = 0; i < 7; i++) {
    digitalWrite(sevenSegData, SevenSegSymbols[value] & (1<<i));
    pulsePin(sevenSegClock);
  }
  pulsePin(sevenSegShift);
}

void pulsePin(int pin) {
  digitalWrite(pin, HIGH);
  digitalWrite(pin, LOW);
}

