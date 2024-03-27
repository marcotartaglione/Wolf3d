//
// Created by Marco on 27/03/2024.
//
#include "editor.h"
#include "texture.h"

void editorLoop() {
    editorDrawMap();
}

void editorKey(u32int key) {

}

static void editorDrawMap() {
    int gridSize = (MIN(frame.width, frame.height) - (MAP_SIZE - 1)) / MAP_SIZE;

    for (int i = 0; i < MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_SIZE; ++j) {

            Tile tile = maps[level][i * MAP_SIZE + j];
            if (tile.type != TILE_TYPE_WALL || tile.wall == WALL_NULL)
                continue;

            Texture *texture = walls[tile.wall];

            float textureStepX = (float)texture->width / gridSize;
            float textureStepY = (float)texture->height / gridSize;

            int offsetX = (gridSize + 1) * i;
            int offsetY = (gridSize + 1) * j;

            for (int y = 0; y < gridSize; ++y) {
                for (int x = 0; x < gridSize; ++x) {
                    int textureX = (int)(x * textureStepX);
                    int textureY = (int)(y * textureStepY);

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
