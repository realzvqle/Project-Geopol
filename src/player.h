#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED





#include "factions.h"
#include "tools.h"
#include "weapons.h"

#define PLAYER_SIZE 25

typedef struct _PLAYER_DATA {
    float x;
    float y;
    char* name;
    char* nameshort;
    bool schedulefire;
    int health;
    bool canshoot;
    int targetnpcindex;
    int targetfacindex;
    WEAPON weapon;
} PLAYER_DATA;

void SetupPlayer();
void SetupCamera(Camera2D* camera);
void PlayerLoop();
void PlayerNPCInteractions(NPC* npc, FACTIONS* fac, int npcindex, int facindex);
#endif