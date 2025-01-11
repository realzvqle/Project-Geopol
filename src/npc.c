#include "npc.h"
#include "exheaders/raylib.h"
#include "factions.h"
#include "player.h"
#include "tools.h"
#include "weapons.h"
#include <math.h>
#include <stdint.h>

extern PLAYER_DATA player_data;


void SetupNPC(NPC* npc, FACTIONS* faction, Color color){
    npc->x = faction->base[0].x + (float)GetRandomValue(-800, 800);
    npc->y = faction->base[0].y + (float)GetRandomValue(-800, 800);
    npc->speeddebuf = GetRandomValue(100, 200);
    npc->color = color;
    npc->health = 15;
    npc->isAlive = true;
    player_data.targetselect = false;
}

void SetupPlayerNPC(NPC* npc, Color color){
    npc->x = player_data.x + (float)GetRandomValue(-50, 50);
    npc->y = player_data.y + (float)GetRandomValue(-50, 50);
    npc->speeddebuf = GetRandomValue(100, 200);
    npc->color = color;
    npc->health = 2;
    npc->isAlive = true;
    player_data.targetselect = false;
}



void NPCLogic(NPC* npc, FACTIONS* fac, int i, int j){
    if(npc->health <= 0){
        npc->isAlive = false;
        fac->lostaplayer = true;
    }
    if(npc->canshoot == true){
        if(npc->waitschedule == true){
            if(fabs(npc->prevtime - GetTime()) >= 0.3){
                npc->waitschedule = false;
            }
            //printf("%f\n", fabs(npc->prevtime - GetTime()));
            goto SKIPWEAPONS;
        }
        //printf("Faoled\n");
        bool result = FireWeapons(&npc->weapon, npc->x, npc->y, player_data.x, player_data.y, GetRGB(fac));
        if(result == true){
            npc->waitschedule = true;
            npc->prevtime = GetTime();
            player_data.health--;
            //printf("player health: %d\n", player_data.health);
        }
    }
SKIPWEAPONS:
    if(GpNPCIsInScreen(npc->x, npc->y)){
        DrawCircle(npc->x, npc->y, NPC_SIZE, GetRGB(fac));
        if(fac->isPlayer == true) GpDrawText(player_data.nameshort, npc->x, npc->y - 60, 30, GetRGB(fac));
        else GpDrawText(fac->nameshort, npc->x, npc->y - 60, 30, GetRGB(fac));  
    }
    
    if(fac->hostile == true){
        if(GpGetDistance(npc->x, player_data.x) < 400 && GpGetDistance(npc->y, player_data.y) < 400){
            if(GpGetDistance(npc->x, player_data.x) <= 40 && GpGetDistance(npc->y, player_data.y) <= 40){
                //printf("Range!\n");
                npc->canshoot = true;
            }

            else{
                if(player_data.schedulefire == true) GpRunAway(player_data.x, player_data.y, &npc->x, &npc->y, 300 + npc->speeddebuf);
                else GpFollow(player_data.x, player_data.y, &npc->x, &npc->y, 300 + npc->speeddebuf);

            } 
            npc->canshoot = true;
        }
        else npc->canshoot = false;
    }
    if(player_data.targetselect != true) return;
    if(GpNPCIsInScreen(npc->x, npc->y) == false) return;
    if(i == player_data.targetfacindex){
        if(j == player_data.targetnpcindex){
            DrawRectangleLines(npc->x - (NPC_SIZE + 10), 
                               npc->y - (NPC_SIZE + 10), 
                               (NPC_SIZE * 2) + 20,
                               (NPC_SIZE * 2) + 20, 
                               GetRGB(fac));
        }
    }
    
}