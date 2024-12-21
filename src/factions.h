#ifndef FACTIONS_H_INCLUDED
#define FACTIONS_H_INCLUDED




#include "tools.h"
#include "npc.h"
#include <stdint.h>

typedef struct _FACTIONS{
    char* name;
    char* nameshort;
    uint8_t moral_stance;
    bool hostile;
    bool isPlayer;
    int money;
    bool lostaplayer;
    uint16_t npcthere;
    NPC npc[512];
} FACTIONS;

void SetupFactions();
void RenderFactionNPCs();
Color GetRGB(FACTIONS* fac);

#endif