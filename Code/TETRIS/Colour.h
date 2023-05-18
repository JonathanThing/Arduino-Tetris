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
};


extern Colour R;
extern Colour G;
extern Colour B;
extern Colour W;
extern Colour P;
extern Colour Y;
extern Colour O;
extern Colour C;
extern Colour N;

#endif