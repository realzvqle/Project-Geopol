#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED





#include "tools.h"
#include "weapons.h"

#define PLAYER_SIZE 25

typedef struct _PLAYER_DATA {
    float x;
    float y;
    char* name;
    char* nameshort;
    bool schedulefire;
    WEAPON weapon;
} PLAYER_DATA;

void SetupPlayer();
void SetupCamera(Camera2D* camera);
void PlayerLoop();
#endif