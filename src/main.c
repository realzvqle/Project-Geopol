#include "exheaders/raylib.h"
#include "scene.h"


Camera2D camera;
int scene = 0;

int main(){
    SetTraceLogLevel(LOG_ERROR);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1600, 900, "Project Geopol");
    

    while(!WindowShouldClose()){
        SceneMGR();
    }
}