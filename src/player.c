#include "player.h"
#include "exheaders/raylib.h"
#include "factions.h"
#include "npc.h"
#include "tools.h"
#include "weapons.h"
#include <stdbool.h>
#include <stdio.h>



PLAYER_DATA player_data;
extern int scene;
extern Camera2D camera;
extern FACTIONS faction[7];

void SetupPlayer(){
    player_data.x = GetScreenWidth() / 2.0;
    player_data.y = GetScreenHeight() / 2.0;
    player_data.name = "Morkovian Republic";
    player_data.nameshort = "Morkovia";
    player_data.health = 15;
    player_data.npcindex = 0;
    player_data.canshoot = false;
    player_data.weapon.init = false;
    player_data.schedulefire = false;
}

static void DrawPlayer(){
    GpDrawText(player_data.nameshort, player_data.x, player_data.y - 60, 30, BLUE);

    DrawCircle(player_data.x, player_data.y, PLAYER_SIZE, PURPLE);
    DrawCircle(player_data.x, player_data.y, PLAYER_SIZE - 1, BLUE);
}

void PlayerLoop(){
    if(player_data.health <= 0){
        scene = 2;
    }
    DrawPlayer();
    if(player_data.schedulefire == true){
        bool result = FireWeapons(&player_data.weapon, player_data.x, player_data.y, 
                                 faction[player_data.targetfacindex].npc[player_data.targetnpcindex].x, 
                                 faction[player_data.targetfacindex].npc[player_data.targetnpcindex].y, BLUE);
        if(result == true){
            if(faction[player_data.targetfacindex].isPlayer != true){
                if(faction[player_data.targetfacindex].hostile == false){
                    faction[player_data.targetfacindex].moral_stance-=50;
                    if(faction[player_data.targetfacindex].moral_stance <= 30){
                        faction[player_data.targetfacindex].hostile = true;
                    }
                }
            }  
            faction[player_data.targetfacindex].npc[player_data.targetnpcindex].health--;
            //printf("Health %d", faction[player_data.targetfacindex].npc[player_data.targetnpcindex].health);
            if(faction[player_data.targetfacindex].npc[player_data.targetnpcindex].health <= 0){
                if(faction[player_data.targetfacindex].isPlayer != true){
                    faction[player_data.targetfacindex].hostile = true;
                    if(player_data.targetfacindex == 1){
                        faction[0].money += 120;
                        printf("You've Been Rewarded for Killing a Bandit, +$120\n");
                    }
                }
                player_data.canshoot = false;
            }
            player_data.schedulefire = false;
        }
    }
    if (IsKeyDown(KEY_W)) {
        player_data.y -= 600.0 * GetFrameTime();
    }
    if (IsKeyDown(KEY_S)) {
        player_data.y += 600.0 * GetFrameTime();
    }
    if (IsKeyDown(KEY_A)) {
        player_data.x -= 600.0 * GetFrameTime();
    }
    if (IsKeyDown(KEY_D)) {
        player_data.x += 600.0 * GetFrameTime();
    }
    if(IsKeyPressed(KEY_SPACE)){
        if(player_data.targetselect != true) return;
        if(player_data.canshoot == true){
            if(GpGetDistance(player_data.x, faction[player_data.targetfacindex].npc[player_data.targetnpcindex].x) < 400 &&
               GpGetDistance(player_data.y, faction[player_data.targetfacindex].npc[player_data.targetnpcindex].y) < 400) {
                player_data.schedulefire = true;
            }
            
        }
    }
    if(IsKeyPressed(KEY_R)){
        if((faction[0].money - 50) > 0 && player_data.health < 15){
            faction[0].money -= 50;
            player_data.health += 1;
        }
    }
    if(IsKeyPressed(KEY_M)){
        SetupPlayerNPC(&faction[0].npc[player_data.npcindex], GetRGB(&faction[0]));
        faction[0].npcthere++;
        printf("made in, index = %d\n", player_data.npcindex);
        player_data.npcindex++;
    }
    if(IsKeyPressed(KEY_P)){
        camera.zoom = 1;
    }
    if(IsKeyDown(KEY_UP)) camera.zoom+=0.005;
    if(IsKeyDown(KEY_DOWN)) camera.zoom-=0.005;
    //camera.zoom = camera.zoom + GetMouseWheelMove(); 
    //printf("%f\n", GetMouseWheelMove());
    camera.target.x = player_data.x - GetScreenWidth() / 2.0;
    camera.target.y = player_data.y - GetScreenHeight() / 2.0;
}

void PlayerNPCInteractions(NPC* npc, FACTIONS* fac, int npcindex, int facindex){
    if(GpGetDistance(npc->x, GpGetMouseX()) <= 30 && GpGetDistance(npc->y, GpGetMouseY()) <= 30){
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            player_data.targetnpcindex = npcindex;
            player_data.targetfacindex = facindex;
            player_data.targetselect = true;
            player_data.canshoot = true;
        }   
    }
}

void SetupCamera(Camera2D* camera){
    Vector2 offset = {0, 0};
    Vector2 target = {0, 0};

    camera->offset = offset;
    camera->target = target;
    camera->rotation = 0;
    camera->zoom = 1;
}

