#include "exheaders/raylib.h"
#include "factions.h"
#include "player.h"
#include "scene.h"
#include "tools.h"


Camera2D camera;
int scene = 0;

int main(){
    SetTraceLogLevel(LOG_ERROR);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1600, 900, "Project Geopol");
    
    GpSetup();
    SetupPlayer();
    SetupFactions();
    SetupCamera(&camera);
    while(!WindowShouldClose()){
        SceneMGR();
    }
}