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
extern Texture** walls;

void editorLoop();
void editorKey(u32int key);

static void editorDrawMap();

#endif //WOLF3D_EDITOR_H
