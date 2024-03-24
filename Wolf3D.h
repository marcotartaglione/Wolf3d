//
// Created by Marco on 24/03/2024.
//

#ifndef WOLF3D_WOLF3D_H
#define WOLF3D_WOLF3D_H

#include "window.h"
#include "raycast.h"

#include "map.h"
//
// Game definitions
//
static GameObj player = { 1.5f, 1.5f, 0.0f, STATE_IDLE, DIRECTION_EAST };

static u32int level = 0;

void drawBackground();
void drawWalls();
void drawColumn(int column, float distance);

#endif //WOLF3D_WOLF3D_H
