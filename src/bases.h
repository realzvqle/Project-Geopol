#ifndef BASES_H_INCLUDED
#define BASES_H_INCLUDED




#include "tools.h"

typedef struct _BASE {
    float x;
    float y;
    Color color;
    bool isAlive;
    int health;
    float spindebuf;
} BASE;

void SetupBases(BASE* base, Color color);
#endif