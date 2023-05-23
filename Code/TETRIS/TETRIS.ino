#include "RGBMatrix.h"
#include "Tetris.h"

static RGBMatrix screen;
static Tetris tetris;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  tetris.update();
  screen.draw(tetris.getDisplay());
}
