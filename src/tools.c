#include "tools.h"
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

static Font font;


void GpSetup(){
    font = LoadFontEx("resources/fonts/static/PixelifySans-Regular.ttf", 200, NULL, 0);
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