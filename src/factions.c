#include "factions.h"
#include "exheaders/raylib.h"
#include "npc.h"
#include "player.h"
#include <stdio.h>

char* namechoice[] = {"Consolan Republic", "Kingdom of Najidert", "Sovienian Union", 
                        "Murri Revolutionary Forces", "Murican Empire", "Brotian State"};
char* namechoiceshort[] = {"Consola", "Najidert", "Sovienia", 
                            "Murri", "Murica", "Brotia"};


extern void NPCLogic(NPC* npc, FACTIONS* fac, int i, int j);
FACTIONS faction[7];

extern PLAYER_DATA player_data;

Color GetRGB(FACTIONS* fac){
    if(fac->hostile == true){
        return RED;
    } else if(fac->isPlayer == true){
        return BLUE;
    } else {
        uint8_t red = 255 - fac->moral_stance;
        uint8_t green = fac->moral_stance; 
        uint8_t blue = 0;
        Color color = {red, green, blue, 255};
        return color;
    }
}

void SetupFactions(){
    for(int i = 0; i < 7; i++){
        faction[i].lostaplayer = false;
        if(i == 0){
            faction[i].name = player_data.name;
            faction[i].nameshort = player_data.nameshort;
            faction[i].moral_stance = 255;
            faction[i].money = 1200;
            faction[i].isPlayer = true;
        }
        if(i == 1){
            faction[i].name = "The Bandits";
            faction[i].nameshort = "Bandits";
            faction[i].moral_stance = 0;
            faction[i].money = 1200;
            faction[i].hostile = true;

        }
        else {
            faction[i].name = namechoice[i - 2];
            faction[i].nameshort = namechoiceshort[i - 2];
            faction[i].moral_stance = GetRandomValue(0, 255);
            faction[i].money = 1200;
        }

        if(faction[i].moral_stance <= 30){
            faction[i].hostile = true;
        }
        for(int j = 0; j < 10; j++){
            if(faction[i].isPlayer == true) continue;
            SetupNPC(&faction[i].npc[j], GetRGB(&faction[i]));
            faction[i].npc[j].isAlive = true;
            faction[i].npcthere++;
        }
    }
}


int GetFreeNPCSport(FACTIONS* fac){
    for(int i = 0; i < fac->npcthere; i++){
        if(fac->npc[i].isAlive == false){
            return i;
        }
    }
    fac->npcthere++;
    return fac->npcthere;
}

void RenderFactionNPCs(){
    for(int i = 0; i < 7; i++){
        if(faction[i].lostaplayer == true){
            if((faction[i].money - 120) > 0){
                faction[i].money -= 120;
                SetupNPC(&faction[i].npc[GetFreeNPCSport(&faction[i])], GetRGB(&faction[i]));
                printf("%s added a new buddy into their squadron, they have $%d left\n", faction[i].nameshort, faction[i].money);

            }
            faction[i].lostaplayer = false;
        }
        for(int j = 0; j < faction[i].npcthere; j++){
            if(faction[i].npc[j].isAlive == false) continue;
            NPCLogic(&faction[i].npc[j], &faction[i], i, j);
            PlayerNPCInteractions(&faction[i].npc[j], &faction[i], j, i);         
        }
    }
}