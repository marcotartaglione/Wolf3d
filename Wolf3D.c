//
// Created by Marco on 24/03/2024.
//

#include "Wolf3D.h"

void drawBackground() {
    for (int y = 0; y < frame.height; ++y) {
        for (int x = 0; x < frame.width; ++x) {
            frame.pixels[y * frame.width + x] = y > frame.height * 0.5 ? ROOF_COLOR : FLOOR_COLOR;
        }
    }
}

void drawWalls() {
    extern Tile maps[MAP_NUMBER][MAP_SIZE * MAP_SIZE];
    static float perAngleTeta = -1;

    // TODO non si aggiorna quando cambia frame.width
    if (perAngleTeta == -1) {
        perAngleTeta = PLAYER_FOV / frame.width;
    }

    float distance, side, perc;

    for (int column = 0; column < frame.width; ++column) {
        raycast(player, perAngleTeta * (float)column - PLAYER_FOV * .5, maps[level], &distance, &side, &perc);
        drawColumn(column, distance);
    }
}

void drawColumn(int column, float distance) {
    int wallHeight = (int)((float)frame.height / distance);

    if (distance < 1) {
        for (int i = 0; i < frame.height; ++i) {
            frame.pixels[i * frame.width + column] = 0x00FF0000;
        }
    } else if (distance > 1) {
        int diff = (int)((float)(frame.height - wallHeight) * 0.5);
        for (int i = 0; i < wallHeight; ++i) {
            frame.pixels[(diff + i) * frame.width + column] = 0x00FF0000;
        }
    }
}

void gameLoop() {
    drawBackground();
    drawWalls();
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    startWindow(hInstance, gameLoop);
}