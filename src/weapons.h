#ifndef WEAPONS_H_INCLUDED
#define WEAPONS_H_INCLUDED



#include "tools.h"



typedef struct _WEAPON{
    float x;
    float y;
    Color color;
    bool init;
} WEAPON;

bool FireWeapons(WEAPON* weapon, float startx, float starty, float targetx, float targety, Color color);

#endif