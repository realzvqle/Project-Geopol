#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED





#include "tools.h"

#define PLAYER_SIZE 25

typedef struct _PLAYER_DATA {
    float x;
    float y;
    char* name;
    char* nameshort;
} PLAYER_DATA;

void SetupPlayer();
void SetupCamera(Camera2D* camera);
void PlayerLoop();
#endif