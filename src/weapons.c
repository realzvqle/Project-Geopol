#include "weapons.h"
#include <stdbool.h>







bool FireWeapons(WEAPON* weapon, float startx, float starty, float targetx, float targety, Color color){
    if(weapon->init != true){
        weapon->x = startx;
        weapon->y = starty;
        weapon->init = true;
    }
    DrawRectangle(weapon->x, weapon->y, 20, 20, color);
    bool result = GpFollowStatus(targetx, targety, &weapon->x, &weapon->y, 900);
    if(result == true){
        weapon->init = false;
        return true;
    } else return false;
}