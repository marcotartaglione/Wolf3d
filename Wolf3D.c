//
// Created by Marco on 24/03/2024.
//

#include "Wolf3D.h"

// TODO convertire tutte le texture in tiles

static void init() {
    walls = loadTexturesFolder("assets\\textures\\walls\\");
    maps = loadMapsFolder("assets\\maps\\");
}

int ENTRY_POINT(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    init();

#ifndef WOLF3D_EDITOR_MODE
    startWindow(hInstance, gameLoop, gameKey, NULL);
#else
    startWindow(hInstance, editorLoop, editorKey, editorMouse);
#endif

}