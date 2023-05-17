#include "Colour.h"

// Constants
byte MAX_VALUE = 8;

Colour::Colour() {
  red = 0;
  green = 0;
  blue = 0;
}

Colour::Colour(byte red, byte green, byte blue) {
  this->red = red;
  this->green = green;
  this->blue = blue;
}

// Getter
byte Colour::getRed() {
  return red;
}

byte Colour::getGreen() {
  return green;
}

byte Colour::getBlue() {
  return blue;
}

// Setter
void Colour::setRed(byte red) {
  this->red = red;
}

void Colour::setGreen(byte green) {
  this->green = green;
}

void Colour::setBlue(byte blue) {
  this->blue = blue;
}

void Colour::setColour(byte red, byte green, byte blue) {
  this->red = red;
  this->green = green;
  this->blue = blue;
}

void Colour::changeRed(byte delta) {
  red += delta;
  if (red < 0) {
    red = 0;
  } else if (red > MAX_VALUE) {
    red = MAX_VALUE;
  }
}

void Colour::changeGreen(byte delta) {
  green += delta;
  if (green < 0) {
    green = 0;
  } else if (green > MAX_VALUE) {
    green = MAX_VALUE;
  }
}

void Colour::changeBlue(byte delta) {
  blue += blue;
  if (blue < 0) {
    blue = 0;
  } else if (blue > MAX_VALUE) {
    blue = MAX_VALUE;
  }
}

void Colour::changeColour(byte redDelta, byte greenDelta, byte blueDelta) {
  red += redDelta;
  green += greenDelta;
  blue += blueDelta;
  if (red < 0) {
    red = 0;
  } else if (red > MAX_VALUE) {
    red = MAX_VALUE;
  }
  if (green < 0) {
    green = 0;
  } else if (green > MAX_VALUE) {
    green = MAX_VALUE;
  }
  if (blue < 0) {
    blue = 0;
  } else if (blue > MAX_VALUE) {
    blue = MAX_VALUE;
  }
}

void Colour::printOut() {
  Serial.print("(");
  Serial.print(red);
  Serial.print(",");
  Serial.print(green);
  Serial.print(",");
  Serial.print(blue);
  Serial.print(")");
}
