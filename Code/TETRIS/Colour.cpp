#include "Colour.h"

// Constants
byte COLOUR_MAX_VALUE = 8;

const Colour RED = Colour(COLOUR_MAX_VALUE, 0, 0);
const Colour GREEN = Colour(0, COLOUR_MAX_VALUE, 0);
const Colour BLUE = Colour(0, 0, COLOUR_MAX_VALUE);
const Colour WHITE = Colour(COLOUR_MAX_VALUE, COLOUR_MAX_VALUE, COLOUR_MAX_VALUE);
const Colour PURPLE = Colour(COLOUR_MAX_VALUE, 0, COLOUR_MAX_VALUE);
const Colour YELLOW = Colour(COLOUR_MAX_VALUE, COLOUR_MAX_VALUE / 4, 0);
const Colour ORANGE = Colour(COLOUR_MAX_VALUE, COLOUR_MAX_VALUE / 8, 0);
const Colour CYAN = Colour(0, COLOUR_MAX_VALUE, COLOUR_MAX_VALUE);
const Colour BLACK = Colour(0, 0, 0);

const Colour ALL_COLOURS[9] = {RED, ORANGE, YELLOW, GREEN, BLUE, CYAN, PURPLE, WHITE, BLACK};

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
  } else if (red > COLOUR_MAX_VALUE) {
    red = COLOUR_MAX_VALUE;
  }
}

void Colour::changeGreen(byte delta) {
  green += delta;
  if (green < 0) {
    green = 0;
  } else if (green > COLOUR_MAX_VALUE) {
    green = COLOUR_MAX_VALUE;
  }
}

void Colour::changeBlue(byte delta) {
  blue += blue;
  if (blue < 0) {
    blue = 0;
  } else if (blue > COLOUR_MAX_VALUE) {
    blue = COLOUR_MAX_VALUE;
  }
}

void Colour::changeColour(byte redDelta, byte greenDelta, byte blueDelta) {
  red += redDelta;
  green += greenDelta;
  blue += blueDelta;
  if (red < 0) {
    red = 0;
  } else if (red > COLOUR_MAX_VALUE) {
    red = COLOUR_MAX_VALUE;
  }
  if (green < 0) {
    green = 0;
  } else if (green > COLOUR_MAX_VALUE) {
    green = COLOUR_MAX_VALUE;
  }
  if (blue < 0) {
    blue = 0;
  } else if (blue > COLOUR_MAX_VALUE) {
    blue = COLOUR_MAX_VALUE;
  }
}

byte Colour::getColour(byte selection) {
  if (selection == 0) {
    return red;
  } else if (selection == 1) {
    return green;
  } else {
    return blue;
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

