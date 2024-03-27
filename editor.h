//
// Created by Marco on 27/03/2024.
//

#ifndef WOLF3D_EDITOR_H
#define WOLF3D_EDITOR_H

#include "defs.h"

static u32int level;

void editorLoop();
void editorKey(u32int key);

static void editorDrawMap();

#endif //WOLF3D_EDITOR_H
