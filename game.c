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
            gameObjRotate(&player, ROT_SPEED);
            break;
        case 'W':
            gameObjMove(&player, MOV_SPEED, level);
            break;
        case 'S':
            gameObjMove(&player, -MOV_SPEED, level);
            break;
        case 'F':
            mapInteract(level, player.x, player.y);
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

    static float frameStep = -1;
    if (frameStep == -1) {
        frameStep = MOVE_ANIMATION_SEC / TARGET_FPS;
    }

    for (int i = 0; i < MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_SIZE; ++j) {
            Tile *tile = &maps[level]->tiles[j * MAP_SIZE + i];

            if (tile->type != TILE_TYPE_DOOR || tile->state == TILE_STATE_IDLE)
                continue;

            switch (tile->state) {
                case TILE_STATE_OPENING:
                    if (tile->movedPerc < 1) {
                        tile->movedPerc = MIN(1, tile->movedPerc + frameStep);
                        break;
                    }
                    tile->state = TILE_STATE_CLOSING;
                    break;
                case TILE_STATE_CLOSING:
                    if (tile->movedPerc > 0) {
                        tile->movedPerc = MAX(0, tile->movedPerc - frameStep);
                        break;
                    }
                    tile->state = TILE_STATE_IDLE;
                    break;
            }
        }
    }
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

        if ((tile->state == TILE_STATE_OPENING || tile->state == TILE_STATE_CLOSING) && tile->movedPerc != 0) {

            // TODO l'offset non tiene conto del fatto che la distanza influenza la grandezza delle texture
            // se una texture è lunga 50px e la porta è aperta al 50%, quest'ultima non si deve muovere di 25px ma di una quantità che varia con la distanza
            int offset = (int)((float) walls[tile->wall]->width * tile->movedPerc);

            if (perc <= 1.0000001 - tile->movedPerc)
                gameDrawColumn(column + offset, perc, distance, walls[tile->wall]);
        } else {
            gameDrawColumn(column, perc, distance, walls[tile->wall]);
        }

        free(tile);
    }
}

static void gameDrawColumn(int column, float normalizedWidthPerc, float distance, Texture *texture) {
    int wallHeight = (int) ((float) frame.height / distance);
    int offset = (wallHeight != frame.height) ? (int) ((frame.height - wallHeight) * 0.5) : 0;

    float heightStep = (float) wallHeight / (float) texture->height;

    float widthOffset = (float) texture->width * normalizedWidthPerc;

    for (int i = -MIN(0, offset); i < frame.height - offset; ++i) {
        int textureIndex = (int) ((float) i / heightStep);
        if (textureIndex >= texture->height - 2)
            break;

        int textureDataIndex = ((int) widthOffset + textureIndex * texture->width) * 3;
        u32int r = texture->data[textureDataIndex] << 16;
        u32int g = texture->data[textureDataIndex + 1] << 8;
        u32int b = texture->data[textureDataIndex + 2];

        int index = (offset + i) * frame.width + column;

        frame.pixels[(offset + i) * frame.width + column] = r | g | b;
    }
}
