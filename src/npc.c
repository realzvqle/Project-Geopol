#include "npc.h"
#include "exheaders/raylib.h"
#include "factions.h"
#include "player.h"
#include "tools.h"
#include <stdint.h>
#include <stdio.h>

extern PLAYER_DATA player_data;


void SetupNPC(NPC* npc, Color color){
    npc->x = (float)GetRandomValue(0, GetScreenWidth());
    npc->y = (float)GetRandomValue(0, GetScreenHeight());
    npc->speeddebuf = GetRandomValue(100, 200);
    npc->color = color;
}

void NPCLogic(NPC* npc, FACTIONS* fac){
    if(fac->hostile == true){
        if(GpGetDistance(npc->x, player_data.x) < 400 && GpGetDistance(npc->y, player_data.y) < 400){
            if(GpGetDistance(npc->x, player_data.x) <= 10 && GpGetDistance(npc->y, player_data.y) <= 10){
                printf("Range!\n");
            }
            else GpFollow(player_data.x, player_data.y, &npc->x, &npc->y, 300 + npc->speeddebuf);
        }
    }

}