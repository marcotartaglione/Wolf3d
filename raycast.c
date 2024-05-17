//
// Created by Marco on 24/03/2024.
//
#include "raycast.h"
#include <math.h>

Tile* filteredRaycast(GameObj *player, float angle, Map* map, TileType filter, float maxDistance, float *distance, int *side, float *hitPerc) {
    float rayPosX = player->x;
    float rayPosY = player->y;
    float rayDirX = cos(angle);
    float rayDirY = sin(angle);

    float mapX = (int)rayPosX;
    float mapY = (int)rayPosY;

    float sideDistX;
    float sideDistY;

    float deltaDistX = sqrtf(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
    float deltaDistY = sqrtf(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));

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

    bool wasDoor = false;
    TileType tileType;
    while (wasDoor == false && mapX >= 0 && mapX < MAP_SIZE && mapY >= 0 && mapY < MAP_SIZE) {
        tileType = map->tiles[(int)mapX + (int)mapY * MAP_SIZE].type;

        if (tileType == filter || (tileType != TILE_TYPE_NONE && tileType != TILE_TYPE_DOOR)) {
            break;
        }

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

    if (mapX < 0 || mapX >= MAP_SIZE || mapY < 0 || mapY >= MAP_SIZE || *distance >= maxDistance || (tileType != filter && tileType != TILE_TYPE_NONE))
        return NULL;

    if (*side == 0) {
        *distance = fabs((mapX - rayPosX + (1.0 - stepX) / 2.0) / rayDirX);
        *hitPerc = rayPosY + rayDirY * (*distance);
        *hitPerc = *hitPerc - (int)*hitPerc;
    } else {
        *distance = fabs((mapY - rayPosY + (1.0 - stepY) / 2.0) / rayDirY);
        *hitPerc = rayPosX + rayDirX * (*distance);
        *hitPerc = *hitPerc - (int)*hitPerc;
    }

    // TODO la porta deve essere più dentro rispetto ai muri quindi capire quando bisogna disegnare la parte laterale oppure a porta stessa

    // deve essere una copia
    // potrebbe essere necessario modificare la Tile senza modificare l'originale nella mappa
    Tile *result = cloneTile(&map->tiles[(int)mapX + (int)mapY * MAP_SIZE]);

    // se un muro è adiacente a una porta allora la texture di contatto deve cambiare
    if (*side == 0) {
        if (mapX > 0 && IS_DOOR(map->tiles[(int)(mapX - 1) + (int)mapY * MAP_SIZE].wall)) {
            result->wall = WALL_DOORSLOT1;
        }
        if (mapX < MAP_SIZE - 1 && IS_DOOR(map->tiles[(int)(mapX + 1) + (int)mapY * MAP_SIZE].wall)) {
            result->wall = WALL_DOORSLOT1;
        }
    } else {
        if (mapY > 0 && IS_DOOR(map->tiles[(int)mapX + (int)(mapY - 1) * MAP_SIZE].wall)) {
            result->wall = WALL_DOORSLOT1;
        }
        if (mapY < MAP_SIZE - 1 && IS_DOOR(map->tiles[(int)mapX + (int)(mapY + 1) * MAP_SIZE].wall)) {
            result->wall = WALL_DOORSLOT1;
        }
    }

    *distance = ABS(*distance) * cosf(angle - player->angle);

    return result;
}
