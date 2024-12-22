#include "ui.h"
#include "exheaders/raylib.h"
#include "player.h"
#include "tools.h"
#include <stdio.h>


extern PLAYER_DATA player_data;
extern FACTIONS faction[7];
extern int scene;
extern bool init;
extern Camera2D camera;

void RenderGamePlayerUI(){
    GpDrawFPS(10, 10);
    GpDrawVersion(GetScreenWidth() - 400, GetScreenHeight() - 50, 25);
    char buffer[512];
    sprintf(buffer, "Health: %d", player_data.health);
    GpDrawText(buffer, GetScreenWidth() - 150, 10, 25, PINK);
    sprintf(buffer, "Money: %d", faction[0].money);
    GpDrawText(buffer, GetScreenWidth() - 150, 30, 25, PINK);
    // if(IsKeyPressed(KEY_F)){
    //     if(!IsWindowFullscreen()) ToggleFullscreen();
    //     else MinimizeWindow();
        
    // }
}

void RenderMainMenu(){
    ClearBackground(BLACK);
    GpDrawText("Project Geopol", 10, GetScreenHeight() / 2.0, 60, GOLD);
    // GpDrawText("Press Space to Start", 10, GetScreenHeight() / 2.0 + 90, 30, RED);
    ButtonState button = DrawButton("Start", 10, GetScreenHeight() / 2.0 + 90, 200, 50, LIGHTGRAY, RED, GRAY, NULL);
    if(button == BUTTON_CLICK_LEFT){
        scene = 1;
    }
}

void RenderLooseMenu(){
    ClearBackground(BLACK);
    GpDrawText("YOU LOST", 10, GetScreenHeight() / 2.0, 60, RED);
    ButtonState button = DrawButton("Restart", 10, GetScreenHeight() / 2.0 + 90, 400, 50, LIGHTGRAY, RED, GRAY, NULL);
    if(button == BUTTON_CLICK_LEFT){
        init = false;
        scene = 1;
    }
}

ButtonState DrawButton(const char* text, int x, int y, int sizeX, int sizeY, Color baseColor, Color textColor, Color hoverColor, int textSize) {
    if (!textSize) {
        textSize = sizeY / 1.5;
    }
    Rectangle recc =  { (float)x, (float)y, (float)sizeX, (float)sizeY };
    bool isMouseOver = CheckCollisionPointRec(GetMousePosition(), recc);
    Color buttonColor = isMouseOver ? hoverColor : baseColor;

    DrawRectangle(x, y, sizeX, sizeY, buttonColor);

    int textWidth = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        textWidth += MeasureText(&text[i], textSize);
    }

    int textX = x + (sizeX - MeasureTextEx(GpGetFont(), text, textSize, 4).x) / 2;
    int textY = y + (sizeY - textSize) / 2;

    GpDrawText(text, textX, textY, textSize, textColor);

    if (isMouseOver && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        Rectangle rec =  { (float)x, (float)y, (float)sizeX, (float)sizeY };
        DrawRectangleLinesEx(rec, 2, textColor);
        return BUTTON_DOWN_LEFT;
    }

    if (isMouseOver && IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
        Rectangle rec =  { (float)x, (float)y, (float)sizeX, (float)sizeY };
        DrawRectangleLinesEx(rec, 2, textColor);
        return BUTTON_DOWN_RIGHT;
    }
    if (isMouseOver && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        Rectangle rec =  { (float)x, (float)y, (float)sizeX, (float)sizeY };
        DrawRectangleLinesEx(rec, 2, textColor);
        return BUTTON_CLICK_LEFT;
    }

    if (isMouseOver && IsMouseButtonReleased(MOUSE_RIGHT_BUTTON)) {
        Rectangle rec =  { (float)x, (float)y, (float)sizeX, (float)sizeY };
        DrawRectangleLinesEx(rec, 2, textColor);
        return BUTTON_CLICK_RIGHT;
    }
    
    if (isMouseOver) {
        Rectangle rec =  { (float)x, (float)y, (float)sizeX, (float)sizeY };
        DrawRectangleLinesEx(rec, 2, textColor);
        return BUTTON_HOVER;
    }

    return BUTTON_NOT_INTERACTED;
}