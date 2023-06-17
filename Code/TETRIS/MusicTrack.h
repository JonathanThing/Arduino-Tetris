#ifndef MUSICTRACK_H
#define MUSICTRACK_H

struct Track {
byte pin;
const uint16_t *freq;
const uint32_t *time;
int trackLength;
};

#endif