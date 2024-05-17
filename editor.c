//
// Created by Marco on 27/03/2024.
//
#include "editor.h"
#include "texture.h"

void editorLoop() {
    editorDrawMap();
    editorDrawActiveTexture();
}

void editorKey(u32int key) {
    switch (key) {
        // up arrow
        case 38: {
            activeTexture = (activeTexture + 1) % N_WALL;

            if (activeTexture < START_NO_DARK_VERIONS_WALL && activeTexture % 2) {
                activeTexture++;
            }
        } break;
        // down arrow
        case 40: {
            activeTexture = activeTexture - 1 >= 0 ? activeTexture - 1 : N_WALL;

            if (activeTexture < START_NO_DARK_VERIONS_WALL && activeTexture % 2) {
                activeTexture--;
            }
        } break;
        case 'S': {
            saveMap(maps[level], "assets\\maps\\");
        } break;
    }
}

void editorMouse(Click click, u32int x, u32int y) {
    if (gridSize == -1 || cellSize == -1)
        return;

    int mapX = x / cellSize;
    int mapY = y / cellSize;

    if (mapX >= MAP_SIZE || mapY >= MAP_SIZE)
        return;

    if (click == CLICK_RIGHT) {
        maps[level]->tiles[mapX + mapY * MAP_SIZE].type = TILE_TYPE_NONE;
        maps[level]->tiles[mapX + mapY * MAP_SIZE].wall = WALL_NULL;
        maps[level]->tiles[mapX + mapY * MAP_SIZE].state = TILE_STATE_NULL;

        return;
    }

    maps[level]->tiles[mapX + mapY * MAP_SIZE].type = IS_DOOR(activeTexture) ? TILE_TYPE_DOOR : TILE_TYPE_WALL;
    maps[level]->tiles[mapX + mapY * MAP_SIZE].wall = activeTexture;
    maps[level]->tiles[mapX + mapY * MAP_SIZE].state = TILE_STATE_NULL;
}

static void editorDrawMap() {
    if (gridSize == -1 || cellSize == 1) {
        gridSize = MIN(frame.width, frame.height);
        cellSize = (float) gridSize / MAP_SIZE;
    }

    for (int j = 0; j < MAP_SIZE; ++j) {
        for (int i = MAP_SIZE - 1; i >= 0; --i) {

            Tile tile = maps[level]->tiles[j + i * MAP_SIZE];
            Texture *texture = walls[tile.wall];

            float textureStepX = (float)texture->height / cellSize;
            float textureStepY = (float)texture->width / cellSize;

            int offsetX = cellSize * j;
            int offsetY = cellSize * (MAP_SIZE - 1 - i);

            for (int y = 0; y < cellSize; ++y) {
                for (int x = 0; x < cellSize; ++x) {
                    int textureX = (int)(y * textureStepX);
                    int textureY = (int)((cellSize - 1 - x) * textureStepY);

                    u32int textureDataIndex = (textureX + textureY * texture->width) * 3;
                    u32int r = texture->data[textureDataIndex] << 16;
                    u32int g = texture->data[textureDataIndex + 1] << 8;
                    u32int b = texture->data[textureDataIndex + 2];

                    frame.pixels[(offsetX + x) + (offsetY + y) * frame.width] = r | g | b;
                }
            }
        }
    }
}

static void editorDrawActiveTexture() {
    static int padding = 30;
    int textureSize = MAX(frame.width, frame.height) - gridSize - padding * 2;

    int offsetX = 0;
    int offsetY = 0;

    if (frame.width - gridSize != 0) {
        offsetX = gridSize;
    } else {
        offsetY = gridSize;
    }

    float textureStepX = (float)walls[activeTexture]->height / textureSize;
    float textureStepY = (float)walls[activeTexture]->width / textureSize;

    for (int y = 0; y < textureSize; ++y) {
        for (int x = 0; x < textureSize; ++x) {
            int textureX = (int)(y * textureStepX);
            int textureY = (int)(x * textureStepY);

            u32int textureDataIndex = (textureY + textureX * walls[activeTexture]->width) * 3;
            u32int r = walls[activeTexture]->data[textureDataIndex] << 16;
            u32int g = walls[activeTexture]->data[textureDataIndex + 1] << 8;
            u32int b = walls[activeTexture]->data[textureDataIndex + 2];

            frame.pixels[(offsetX + x) + (offsetY + y) * frame.width] = r | g | b;
        }
    }
}