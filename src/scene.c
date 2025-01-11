#include "scene.h"
#include "exheaders/raylib.h"
#include "factions.h"
#include "player.h"
#include "tools.h"
#include "ui.h"
extern int scene;
extern Camera2D camera;
// extern PLAYER_DATA player_data;
bool init = false;

void SceneMGR(){
    switch(scene){
        case 0:{
            BeginDrawing();
            RenderMainMenu();
            EndDrawing();   
            break;     
        }
        case 1:{
            if(init == false){  
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
            //DrawRectangle(100, 100, 100, 100, RED);
            EndMode2D();
            RenderGamePlayerUI();
            EndDrawing();
            break;
        }
        case 2:{
            BeginDrawing();
            RenderLooseMenu();
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