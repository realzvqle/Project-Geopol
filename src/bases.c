#include "bases.h"
#include "exheaders/raylib.h"
#include "factions.h"
#include "player.h"
#include "tools.h"
#include <stdio.h>


extern PLAYER_DATA player_data;
extern FACTIONS faction[7];
double currenttime;
void SetupBases(BASE* base, Color color){
CONTINUE:
    base->x = (float)GetRandomValue(-2000, 2000);
    base->y = (float)GetRandomValue(-3000, 3000);
    
    base->color = color;
    base->health = 15;
    base->isAlive = true;
    //base->spindebuf = (float)GetRandomValue(30, 40);
}

static inline void DrawBaseStructure(BASE* base, FACTIONS* faction){
    static float rotation = 0;
    currenttime = GetTime();
    if(rotation == 360) rotation = 0;

    if((currenttime - GetTime()) * GetFrameTime() <= 30){
        currenttime = GetTime();
        rotation+=(50)*GetFrameTime();
    }
    //printf("current time = %0.1f, GetTime() is %0.1f\n", currenttime, GetTime());
    
    Rectangle rec = {base->x, base->y, 200, 200};
    Vector2 origin = { rec.width / 2, rec.height / 2 };
    DrawRectanglePro(rec, origin, rotation, base->color);
    DrawCircleLines(base->x, base->y, 400, base->color);
    GpDrawText(faction->nameshort, base->x, base->y - 200, 40, base->color);
}

void BaseLogic(BASE* base, FACTIONS* faction){
    for(int i = 0; i < faction->npcthere; i++){
        if(GpGetDistanceAll(faction->npc[i].x, faction->npc[i].y, base->x, base->y) <= 400){
            faction->npc[i].health = 15;
        }
    }
    if(faction->isPlayer){
        if(GpGetDistanceAll(player_data.x, player_data.y, base->x, base->y) <= 400){
            player_data.health = 15;
        }
    }
    if(faction->hostile){
        if(GpGetDistanceAll(player_data.x, player_data.y, base->x, base->y) <= 400){
            player_data.health -= 0.1;
        }
    }
    if(GpNPCIsInScreen(base->x, base->y)){
        DrawBaseStructure(base, faction);
    }
}
