//
// Created by Marco on 27/03/2024.
//

#ifndef WOLF3D_GAMEOBJECT_H
#define WOLF3D_GAMEOBJECT_H

#include "defs.h"
#include "map.h"

typedef struct {
    float   x, y;
    float   angle;
    State   state;
    Direction direction;
} GameObj;

void gameObjRotate(GameObj *gameObj, float rotation);
void gameObjMove(GameObj *gameObj, float movement, u32int level);

#endif //WOLF3D_GAMEOBJECT_H
