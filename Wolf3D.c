//
// Created by Marco on 24/03/2024.
//

#include "Wolf3D.h"

static void init() {
    walls = loadWalls("w3d_textures_fix\\walls\\");
}

int ENTRY_POINT(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    init();

#ifndef WOLF3D_EDITOR_MODE
    startWindow(hInstance, gameLoop, gameKey);
#else
    startWindow(hInstance, editorLoop, editorKey);
#endif

}