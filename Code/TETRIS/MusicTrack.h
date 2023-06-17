#ifndef MUSICTRACK_H
#define MUSICTRACK_H

struct Track {
byte pin;
const int *freq;
const int *time;
int trackLength;
};

#endif