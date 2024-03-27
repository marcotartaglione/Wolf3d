//
// Created by Marco on 27/03/2024.
//
#include "game.h"

void gameLoop() {
    gameDrawBackground();
    gameDrawWalls();
}

void gameKey(u32int key) {
    /**
     * https://learn.microsoft.com/it-it/windows/win32/inputdev/virtual-key-codes
     */

    switch (key) {
        case 'A':
            gameObjRotate(&player, -ROT_SPEED);
            break;
        case 'D':
            gameObjRotate(&player,  ROT_SPEED);
            break;
        case 'W':
            gameObjMove(&player,  MOV_SPEED, level);
            break;
        case 'S':
            gameObjMove(&player, -MOV_SPEED, level);
            break;
        case 27:
            closeWindow();
            break;
        default:
            break;
    }
}

static void gameDrawBackground() {
    for (int y = 0; y < frame.height; ++y) {
        for (int x = 0; x < frame.width; ++x) {
            frame.pixels[y * frame.width + x] = y > frame.height * 0.5 ? ROOF_COLOR : FLOOR_COLOR;
        }
    }
}

static void gameDrawWalls() {
    static float perAngleTeta = -1;

    if (perAngleTeta == -1) {
        perAngleTeta = PLAYER_FOV / frame.width;
    }

    float distance, side, perc;
    for (int column = 0; column < frame.width; ++column) {
        Tile *tile = raycast(player, perAngleTeta * (float)column - PLAYER_FOV * .5 + player.angle, maps[level], &distance, &side, &perc);
        printf("%f\n", perc);

        if (tile->type == TILE_TYPE_WALL)
            gameDrawColumn(column, perc, distance, walls[tile->wall]);
    }
}

static void gameDrawColumn(int column, float normalizedWidthPerc, float distance, Texture* texture) {
    int wallHeight = (int)((float)frame.height / distance);
    int offset = wallHeight != frame.height ? (int)((frame.height - wallHeight) * 0.5) : 0;

    float heightStep = (float)wallHeight / (float)texture->height;
    float currentStep = heightStep;

    float widthOffset = (float)texture->width * normalizedWidthPerc;
    int textureIndex = 0;

    for (int i = -MIN(0, offset); i < frame.height - offset && textureIndex < texture->height - 2; ++i) {
        if (i > currentStep) {
            currentStep += heightStep;
            textureIndex++;
        }

        u32int textureDataIndex = ((int)widthOffset + textureIndex * texture->width) * 3;
        u32int r = texture->data[textureDataIndex] << 16;
        u32int g = texture->data[textureDataIndex + 1] << 8;
        u32int b = texture->data[textureDataIndex + 2];

        frame.pixels[(offset + i) * frame.width + column] = r | g | b;
    }
}