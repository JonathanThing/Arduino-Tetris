#include "RGBMatrix.h"
#include "Tetris.h"
#include "MusicPlayer.h"
#include <Tone.h>

static RGBMatrix screen;
static Tetris game;
static MusicPlayer music;

void setup()
{
  Serial.begin(9600);
  screen = RGBMatrix();
  game = Tetris();
  music = MusicPlayer();
}

void loop()
{
  game.update();
  music.update();
  screen.draw(game.getDisplay());
  delay(2); // About the time delay of game logic (Hopefully)
}
