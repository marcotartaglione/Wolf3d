//
// Created by Marco on 27/03/2024.
//

#ifndef WOLF3D_EDITOR_H
#define WOLF3D_EDITOR_H

#include "defs.h"
#include "window.h"
#include "texture.h"
#include "tile.h"
#include "map.h"

static u32int level;
static u32int textureIndex;

static int gridSize = -1;
static float cellSize = -1;

extern Texture** walls;
static int activeTexture = 0;

void editorLoop();
void editorKey(u32int key);
void editorMouse(u32int x, u32int y);

static void editorDrawMap();
static void editorDrawActiveTexture();

#endif //WOLF3D_EDITOR_H
