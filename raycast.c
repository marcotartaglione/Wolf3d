//
// Created by Marco on 24/03/2024.
//
#include "raycast.h"

void raycast(GameObj player, float angle, Tile map[MAP_SIZE * MAP_SIZE], float *distance, float *side, float *hitPerc) {
    float rayPosX = player.x;
    float rayPosY = player.y;
    float rayDirX = cos(angle);
    float rayDirY = sin(angle);

    float mapX = (int)rayPosX;
    float mapY = (int)rayPosY;

    float sideDistX;
    float sideDistY;

    float deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
    float deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));

    int stepX;
    int stepY;

    if (rayDirX < 0) {
        stepX = -1;
        sideDistX = (rayPosX - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
    }

    if (rayDirY < 0) {
        stepY = -1;
        sideDistY = (rayPosY - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
    }

    while (map[(int)mapX + (int)mapY * MAP_SIZE].type == TILE_TYPE_NONE) {
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            *side = 0;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            *side = 1;
        }
    }

    if (*side == 0) {
        *distance = fabs((mapX - rayPosX + (1.0 - stepX) / 2.0) / rayDirX);
        *hitPerc = rayPosY + rayDirY * (*distance);
        *hitPerc = *hitPerc - (int)*hitPerc;
    } else {
        *distance = fabs((mapY - rayPosY + (1.0 - stepY) / 2.0) / rayDirY);
        *hitPerc = rayPosX + rayDirX * (*distance);
        *hitPerc = *hitPerc - (int)*hitPerc;
    }

    *distance = ABS(*distance);
}
