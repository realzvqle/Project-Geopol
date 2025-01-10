#include "tools.h"
#include "exheaders/raylib.h"
#include "player.h"
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

static Font font;

extern Camera2D camera;
extern PLAYER_DATA player_data;

void GpSetup(){
    font = LoadFontEx("resources/fonts/PixelifySans/PixelifySans-Regular.ttf", 200, NULL, 0);
}

void GpClose(){
    UnloadFont(font);
}

void GpDrawText(const char* text, float posX, float posY, float size, Color color){
    Vector2 vec = {posX, posY};
    DrawTextEx(font, text, vec, size, 2, color);
}

void GpDrawFPS(float posX, float posY){
    char buffer[512];
    sprintf(buffer, "%d FPS", GetFPS());
    GpDrawText(buffer, posX, posY, 25,  GREEN);
}

void GpFollow(float targetx, float targety, float* curx, float* cury, float speed){
    if (targetx < *curx) {
        *curx -= speed * GetFrameTime();
    } else if (targetx > *curx) {
        *curx += speed * GetFrameTime();
    }
    if (targety < *cury) {
        *cury -= speed * GetFrameTime();
    } else if (targety > *cury) {
        *cury += speed * GetFrameTime();
    }
}

bool GpFollowStatus(float targetx, float targety, float* curx, float* cury, float speed){
    static bool finished = false;
    if (targetx < *curx) {
        *curx -= speed * GetFrameTime();
    } else if (targetx > *curx) {
        *curx += speed * GetFrameTime();
    }
    if (targety < *cury) {
        *cury -= speed * GetFrameTime();
    } else if (targety > *cury) {
        *cury += speed * GetFrameTime();
    }
    if(GpGetDistance(targetx, *curx) <= 30 && GpGetDistance(targety, *cury) <= 30) return true;
    else return false;
}
void GpRunAway(float targetx, float targety, float* curx, float* cury, float speed){
    if (targetx > *curx) {
        *curx -= speed * GetFrameTime();
    } else if (targetx < *curx) {
        *curx += speed * GetFrameTime();
    }
    if (targety > *cury) {
        *cury -= speed * GetFrameTime();
    } else if (targety < *cury) {
        *cury += speed * GetFrameTime();
    }
}

float GpGetDistance(float first, float second){
    return fabsf(first - second);
}



float GpGetMouseX(){
    Vector2 mouse = {GetMouseX(), GetMouseY()};
    Vector2 mousepos = GetScreenToWorld2D(mouse, camera);
    return mousepos.x;
}

float GpGetMouseY(){
    Vector2 mouse = {GetMouseX(), GetMouseY()};
    Vector2 mousepos = GetScreenToWorld2D(mouse, camera);
    return mousepos.y;
}
float GpGetVersion(){
    return 0.0f;
}

void GpDrawVersion(float posx, float posy, float size){
    char buffer[512];
    sprintf(buffer, "Version %0.1f\nBuilt On %s at %s", GpGetVersion(), __DATE__, __TIME__);
    GpDrawText(buffer, posx, posy, size, GOLD);
}

Font GpGetFont(){
    return font;
}

bool GpNPCIsInScreen(float npcx, float npcy){ 
    if(GpGetDistance(player_data.x, npcx) >= 400 && GpGetDistance(player_data.y, npcy) >= 300) return false;
    else return true;
}