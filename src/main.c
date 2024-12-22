#include "exheaders/raylib.h"
#include "scene.h"
#include "tools.h"


Camera2D camera;
int scene = 0;

int main(){
    SetTraceLogLevel(LOG_ERROR);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1600, 900, "Project Geopol");
    GpSetup();

    while(!WindowShouldClose()){
        SceneMGR();
    }
    GpClose();
    CloseWindow();
    return 0;
}