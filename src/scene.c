#include "scene.h"
#include "exheaders/raylib.h"
#include "factions.h"
#include "player.h"
#include "tools.h"
#include "ui.h"

extern int scene;
extern Camera2D camera;
static bool init = false;

void SceneMGR(){
    switch(scene){
        case 0:{
            BeginDrawing();
            ClearBackground(BLACK);
            GpDrawText("Project Geopol", 10, GetScreenHeight() / 2.0, 60, GOLD);
            // GpDrawText("Press Space to Start", 10, GetScreenHeight() / 2.0 + 90, 30, RED);
            ButtonState button = DrawButton("Start", 10, GetScreenHeight() / 2.0 + 90, 200, 50, LIGHTGRAY, RED, GRAY, NULL);
            if(button == BUTTON_CLICK_LEFT){
                scene = 1;
            }
            EndDrawing();   
            break;     
        }
        case 1:{
            if(init == false){
                GpSetup();
                SetupPlayer();
                SetupFactions();
                SetupCamera(&camera);
                init = true;
            }
            BeginDrawing();
            BeginMode2D(camera);
            RenderFactionNPCs();

            PlayerLoop();
            ClearBackground(BLACK);
            DrawRectangle(100, 100, 100, 100, RED);
            EndMode2D();
            RenderGamePlayerUI();
            EndDrawing();
            break;
        }
        case 2:{
            BeginDrawing();
            ClearBackground(BLACK);
            GpDrawText("YOU LOST", 10, GetScreenHeight() / 2.0, 60, RED);
            ButtonState button = DrawButton("Restart", 10, GetScreenHeight() / 2.0 + 90, 400, 50, LIGHTGRAY, RED, GRAY, NULL);
            if(button == BUTTON_CLICK_LEFT){
                init = false;
                scene = 1;
            }
            EndDrawing();   
            break; 
        }
        default:{
            
            BeginDrawing();
            ClearBackground(BLACK);
            GpDrawText("Project Geopol", 10, GetScreenHeight() / 2.0, 60, GOLD);
            GpDrawText("ERROR: INCORRECT SCENE", 10, GetScreenHeight() / 2.0 + 90, 30, RED);
            EndDrawing();   
            break;     
        
        }
    }
}