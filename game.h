//
// Created by Marco on 27/03/2024.
//

#ifndef WOLF3D_GAME_H
#define WOLF3D_GAME_H

#include "texture.h"
#include "gameObject.h"
#include "window.h"
#include "raycast.h"
#include "map.h"

static GameObj player = { 29.5f, 53.5f, 0, STATE_IDLE, DIRECTION_EAST };

extern Texture** walls;

static u32int level;

//
// External function
//
void gameLoop();
void gameKey(u32int key);

//
// Internal functions
//
static void gameDrawBackground();

static void gameDrawMap();
static void gameDrawAndUpdateWalls();
static void gameDrawAndUpdateDoors();

static void gameDrawMapFiltered(TileType filter);
static void gameDrawColumn(int column, float normalizedWidthPerc, float distance, Texture* texture);

#endif //WOLF3D_GAME_H
