#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED



#include "tools.h"
#include "weapons.h"

#define NPC_SIZE 25

typedef struct _NPC {
    float x;
    float y;
    float speeddebuf;
    Color color;
    bool isAlive;
    bool canshoot;
    bool waitschedule;
    double prevtime;
    WEAPON weapon;
    int health;
} NPC;



//void SetupNPC(NPC* npc, Color color);
void SetupPlayerNPC(NPC* npc, Color color);
void AllocateMemoryforNPC(NPC** npc);
void FreeMemoryforNPC(NPC** npc);
#endif