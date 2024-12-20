#include "player.h"
#include "exheaders/raylib.h"



PLAYER_DATA player_data;

extern Camera2D camera;

void SetupPlayer(){
    player_data.x = GetScreenWidth() / 2.0;
    player_data.y = GetScreenHeight() / 2.0;
    player_data.name = "Morkovian Republic";
    player_data.nameshort = "Morkovia";
}

static void DrawPlayer(){
    DrawCircle(player_data.x, player_data.y, PLAYER_SIZE, BLUE);
}

void PlayerLoop(){
    DrawPlayer();
    if (IsKeyDown(KEY_W)) {
        player_data.y -= 600.0 * GetFrameTime();
    }
    if (IsKeyDown(KEY_S)) {
        player_data.y += 600.0 * GetFrameTime();
    }
    if (IsKeyDown(KEY_A)) {
        player_data.x -= 600.0 * GetFrameTime();
    }
    if (IsKeyDown(KEY_D)) {
        player_data.x += 600.0 * GetFrameTime();
    }
    camera.target.x = player_data.x - GetScreenWidth() / 2.0;
    camera.target.y = player_data.y - GetScreenHeight() / 2.0;
}

void SetupCamera(Camera2D* camera){
    Vector2 offset = {0, 0};
    Vector2 target = {0, 0};

    camera->offset = offset;
    camera->target = target;
    camera->rotation = 0;
    camera->zoom = 1;
}