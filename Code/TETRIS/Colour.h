#ifndef COLOUR_H
#define COLOUR_H
#include <Arduino.h>

extern byte MAX_VALUE;

class Colour {
private:
  byte red;
  byte green;
  byte blue;
public:
  static const Colour RED;
  static const Colour GREEN;
  static const Colour BLUE;
  static const Colour WHITE;
  static const Colour PURPLE;
  static const Colour YELLOW;
  static const Colour ORANGE;
  static const Colour CYAN;
  static const Colour BLACK;
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
#endif