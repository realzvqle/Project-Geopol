#include "factions.h"
#include "bases.h"
#include "exheaders/raylib.h"
#include "npc.h"
#include "player.h"
#include <stdio.h>


extern PLAYER_DATA player_data;
char* namechoiceshort[] = {"Consola", "Najidert", "Sovienia", 
                            "Murri", "Murica", "Brotia"};
char* namechoice[] = {"Consolan Republic", "Kingdom of Najidert", "Sovienian Union", 
                        "Murri Revolutionary Forces", "Murican Empire", "Brotian State"};

extern void NPCLogic(NPC* npc, FACTIONS* fac, int i, int j);
extern void BaseLogic(BASE* base, FACTIONS* faction);
extern void SetupNPC(NPC* npc, FACTIONS* faction, Color color);
FACTIONS faction[7];


Color GetRGB(FACTIONS* fac){
    if(fac->hostile == true){
        return RED;
    } else if(fac->isPlayer == true){
        return BLUE;
    } else {
        if(fac->moral_stance <= 30){
            return RED;
        }
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
            faction[i].moral_stance = 126;
            faction[i].money = 1200;
            faction[i].isPlayer = true;
            faction[i].npcthere = 0;
            faction[i].hostile = false;
        }
        else if(i == 1){
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

        if(faction[i].moral_stance - faction[0].moral_stance >= 120){
            if(i != 0){
                faction[i].hostile = true;
                //if(faction[i].isPlayer) faction[i].hostile = false;
            } 
        }
        for(int j = 0; j < 1; j++){
            if(faction[i].isPlayer == true){
                if(j >= 1){
                    continue;
                }
                SetupBases(&faction[0].base[j], GetRGB(&faction[i]));
                player_data.x = faction[0].base[j].x + 400;
                player_data.y = faction[0].base[j].y + 400;
            } 
            else SetupBases(&faction[i].base[j], GetRGB(&faction[i]));
            faction[i].base[j].isAlive = true;
            faction[i].basethere++;
        }

        for(int j = 0; j < 10; j++){
            if(faction[i].isPlayer == true){
                if(j >= 0){
                    continue;
                }
                SetupPlayerNPC(&faction[0].npc[j], GetRGB(&faction[i]));
            } 
            else SetupNPC(&faction[i].npc[j], &faction[i], GetRGB(&faction[i]));
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
                SetupNPC(&faction[i].npc[GetFreeNPCSport(&faction[i])], &faction[i], GetRGB(&faction[i]));
                printf("%s added a new buddy into their squadron, they have $%d left\n", faction[i].nameshort, faction[i].money);

            }
            faction[i].lostaplayer = false;
        }

        for(int j = 0; j < faction[i].npcthere; j++){
            if(faction[i].npc[j].isAlive == false) continue;
            NPCLogic(&faction[i].npc[j], &faction[i], i, j);
            PlayerNPCInteractions(&faction[i].npc[j], &faction[i], j, i);         
        }
        for(int j = 0; j < faction[i].basethere; j++){
            faction[i].base[j].color = GetRGB(&faction[i]);
            if(faction[i].base[j].isAlive == false) continue;
            BaseLogic(&faction[i].base[j], &faction[i]);
        }
    }
}