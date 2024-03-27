//
// Created by Marco on 27/03/2024.
//
#include "map.h"

int mapValidatePosition(u32int level, float x, float y) {
    return maps[level][(int)y * MAP_SIZE + (int)x].type != TILE_TYPE_WALL;
}