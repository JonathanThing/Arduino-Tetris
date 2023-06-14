#ifndef COLOUR_H
#define COLOUR_H
#include <Arduino.h>

extern byte COLOUR_MAX_VALUE;

struct Colour {
  byte red;
  byte green;
  byte blue;

  Colour();
  Colour(byte red, byte green, byte blue);
  byte getRed();
  byte getGreen();
  byte getBlue();
  void setRed(byte red);
  void setGreen(byte green);
  void setBlue(byte blue);
  void setColour(byte red, byte green, byte blue);
  void printOut();
  void changeRed(byte delta);
  void changeGreen(byte delta);
  void changeBlue(byte delta);
  void changeColour(byte redDelta, byte greenDelta, byte blueDelta);
  byte getColour(byte selection);
};

extern const Colour RED;
extern const Colour GREEN;
extern const Colour BLUE;
extern const Colour WHITE;
extern const Colour PURPLE;
extern const Colour YELLOW;
extern const Colour ORANGE;
extern const Colour CYAN;
extern const Colour BLACK;
extern const Colour GREY;

extern const Colour ALL_COLOURS[9];


#endif