#ifndef FACTIONS_H_INCLUDED
#define FACTIONS_H_INCLUDED




#include "bases.h"
#include "tools.h"
#include "npc.h"
#include <stdint.h>

typedef struct _FACTIONS{
    char* name;
    char* nameshort;
    int moral_stance;
    bool hostile;
    bool isPlayer;
    int money;
    bool lostaplayer;
    uint16_t npcthere;
    NPC npc[512];
    uint16_t basethere;
    BASE base[30];
} FACTIONS;

void SetupFactions();
void RenderFactionNPCs();
Color GetRGB(FACTIONS* fac);
int GetFreeNPCSport(FACTIONS* fac);

#endif