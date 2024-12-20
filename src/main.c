#include "exheaders/raylib.h"
#include "factions.h"
#include "player.h"
#include "tools.h"


Camera2D camera;

int main(){
    InitWindow(1600, 900, "Project Geopol");
    
    GpSetup();
    SetupPlayer();
    SetupFactions();
    SetupCamera(&camera);
    while(!WindowShouldClose()){
        BeginDrawing();
        BeginMode2D(camera);
        RenderFactionNPCs();

        PlayerLoop();
        ClearBackground(BLACK);
        DrawRectangle(100, 100, 100, 100, RED);
        EndMode2D();
        GpDrawFPS(10, 10);
        EndDrawing();
    }
}