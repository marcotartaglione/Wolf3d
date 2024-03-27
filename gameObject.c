//
// Created by Marco on 27/03/2024.
//
#include "gameObject.h"
#include "math.h"

void gameObjRotate(GameObj *gameObj, float rotation) {
    rotation += gameObj->angle;

    if (rotation < 0) {
        rotation += PI_times_2;
    } else if (rotation > PI_times_2) {
        rotation -= PI_times_2;
    }

    gameObj->angle = rotation;
}

void gameObjMove(GameObj *gameObj, float movement, u32int level) {
    float dX = cos(gameObj->angle);
    float dY = sin(gameObj->angle);

    float newX = gameObj->x + dX * (movement + 0.3 * SIGN(movement));
    float newY = gameObj->y + dY * (movement + 0.3 * SIGN(movement));

    if (mapValidatePosition(level , newX, newY)) {
        gameObj->x += dX * movement;
        gameObj->y += dY * movement;
    }
}