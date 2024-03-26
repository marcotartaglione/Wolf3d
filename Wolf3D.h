//
// Created by Marco on 24/03/2024.
//

#ifndef WOLF3D_WOLF3D_H
#define WOLF3D_WOLF3D_H

#include <math.h>

#include "window.h"
#include "raycast.h"

#include "map.h"
#include "texture.h"

//
// Game definitions
//
static GameObj player = { 2.5f, 5.5f, 0, STATE_IDLE, DIRECTION_EAST };
static u32int level = 0;

static Texture* brick;

//
// Game functions & procedures
//
static void init();

void drawBackground();
void drawWalls();
void drawColumn(int column, float normalizedWidthPerc, float distance, Texture* texture);

void gameLoop();
void gameKey(u32int key);

static void objRotation(GameObj *gameObj, float rotation);
static void objMove(GameObj *gameObj, float movement);

static int validEntityPosition(float x, float y);

// entry point
int ENTRY_POINT(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow);

#endif //WOLF3D_WOLF3D_H