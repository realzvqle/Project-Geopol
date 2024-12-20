#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED



#include "tools.h"

#define NPC_SIZE 25

typedef struct _NPC {
    float x;
    float y;
    float speeddebuf;
    Color color;
    bool isAlive;
    bool health;
} NPC;

void SetupNPC(NPC* npc, Color color);
#endif