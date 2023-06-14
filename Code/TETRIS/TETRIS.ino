#include "RGBMatrix.h"
#include "Tetris.h"
#include "MusicPlayer.h"

void setup() {
  Serial.begin(9600);
  setupRGBMatrix();
  setupTetris();
}

void loop() {
  updateTetris();
  drawDisplay();
}