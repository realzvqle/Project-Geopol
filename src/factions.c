#include "factions.h"
#include "exheaders/raylib.h"
#include "player.h"
#include "tools.h"
# 
char* namechoice[] = {"Consolan Republic", "Kingdom of Najidert", "Sovienian Union", 
                        "Murri Revolutionary Forces", "Murican Empire", "Brotian State"};
char* namechoiceshort[] = {"Consola", "Najidert", "Sovienia", 
                            "Murri", "Murica", "Brotia"};


extern void NPCLogic(NPC* npc, FACTIONS* fac);
FACTIONS faction[7];

extern PLAYER_DATA player_data;

static Color GetRGB(FACTIONS* fac){
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
        if(i == 0){
            faction[i].name = player_data.name;
            faction[i].nameshort = player_data.nameshort;
            faction[i].moral_stance = 255;
            faction[i].isPlayer = true;
        }
        if(i == 1){
            faction[i].name = "The Bandits";
            faction[i].nameshort = "Bandits";
            faction[i].moral_stance = 0;
            faction[i].hostile = true;

        }
        else {
            faction[i].name = namechoice[i - 2];
            faction[i].nameshort = namechoiceshort[i - 2];
            faction[i].moral_stance = GetRandomValue(0, 255);
        }

        if(faction[i].moral_stance <= 30){
            faction[i].hostile = true;
        }
        for(int j = 0; j < 10; j++){
            SetupNPC(&faction[i].npc[j], GetRGB(&faction[i]));
            faction[i].npcthere++;
        }
    }
}


void RenderFactionNPCs(){
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < faction[i].npcthere; j++){
            DrawCircle(faction[i].npc[j].x, faction[i].npc[j].y, 25, faction[i].npc[j].color);
            GpDrawText(faction[i].nameshort, faction[i].npc[j].x, faction[i].npc[j].y - 60, 30, faction[i].npc[j].color);
            NPCLogic(&faction[i].npc[j], &faction[i]);
        }
    }
}