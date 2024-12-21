#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED



#include "exheaders/raylib.h"



void GpSetup();
void GpDrawText(const char* text, float posX, float posY, float size, Color color);
void GpDrawFPS(float posX, float posY);
void GpFollow(float targetx, float targety, float* curx, float* cury, float speed);
void GpRunAway(float targetx, float targety, float* curx, float* cury, float speed);
void GpClose();
float GpGetDistance(float first, float second);
bool GpFollowStatus(float targetx, float targety, float* curx, float* cury, float speed);
float GpGetMouseX();
float GpGetMouseY();
void GpDrawVersion(float posx, float posy, float size);
float GpGetVersion();
Font GpGetFont();
#endif