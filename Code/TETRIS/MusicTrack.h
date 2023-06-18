#ifndef MUSICTRACK_H
#define MUSICTRACK_H
#include "Arduino.h"

struct MusicTrack {
byte pin;
const uint16_t *freq;
const uint32_t *time;
int trackLength;
};

#endif