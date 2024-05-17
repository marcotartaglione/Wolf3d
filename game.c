//
// Created by Marco on 27/03/2024.
//
#include "game.h"

void gameLoop() {
    gameDrawBackground();
    gameDrawMap();
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

static void gameDrawMap() {
    gameDrawAndUpdateWalls();
    gameDrawAndUpdateDoors();
}

static void gameDrawAndUpdateWalls() {
    gameDrawMapFiltered(TILE_TYPE_WALL);
}

static void gameDrawAndUpdateDoors() {
    gameDrawMapFiltered(TILE_TYPE_DOOR);
}

static void gameDrawMapFiltered(TileType filter) {
    static float perAngleTeta = -1;

    if (perAngleTeta == -1) {
        perAngleTeta = PLAYER_FOV / frame.width;
    }

    float distance, perc;
    int side;
    for (int column = 0; column < frame.width; ++column) {
        Tile *tile = filteredRaycast(&player, perAngleTeta * (float) column - PLAYER_FOV * .5f + player.angle,
                                     maps[level], filter, 100, &distance, &side, &perc);

        if (tile == NULL)
            continue;

        gameDrawColumn(column, perc, distance, walls[tile->wall]);
        free(tile);
    }
}

static void gameDrawColumn(int column, float normalizedWidthPerc, float distance, Texture* texture) {
    int wallHeight = (int)((float)frame.height / distance);
    int offset = (wallHeight != frame.height) ? (int)((frame.height - wallHeight) * 0.5) : 0;

    float heightStep = (float)wallHeight / (float)texture->height;

    float widthOffset = (float)texture->width * normalizedWidthPerc;

    for (int i = -MIN(0, offset); i < frame.height - offset; ++i) {
        int textureIndex = (int)((float)i / heightStep);
        if (textureIndex >= texture->height - 2)
            break;

        int textureDataIndex = ((int)widthOffset + textureIndex * texture->width) * 3;
        u32int r = texture->data[textureDataIndex] << 16;
        u32int g = texture->data[textureDataIndex + 1] << 8;
        u32int b = texture->data[textureDataIndex + 2];

        frame.pixels[(offset + i) * frame.width + column] = r | g | b;
    }
}
