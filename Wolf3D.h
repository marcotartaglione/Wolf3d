//
// Created by Marco on 24/03/2024.
//

#ifndef WOLF3D_WOLF3D_H
#define WOLF3D_WOLF3D_H

#include "texture.h"
#include "window.h"
#include "game.h"
#include "editor.h"

Texture** walls;
Map** maps;

static void init();
int ENTRY_POINT(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow);

#endif //WOLF3D_WOLF3D_H