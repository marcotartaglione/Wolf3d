//
// Created by Marco on 24/03/2024.
//

#include "Wolf3D.h"

static void init() {
    brick = readBMP("w3d_textures_fix\\stone1.png");
}

void drawBackground() {
    for (int y = 0; y < frame.height; ++y) {
        for (int x = 0; x < frame.width; ++x) {
            frame.pixels[y * frame.width + x] = y > frame.height * 0.5 ? ROOF_COLOR : FLOOR_COLOR;
        }
    }
}

void drawWalls() {
    static float perAngleTeta = -1;

    // TODO non si aggiorna quando cambia frame.width
    if (perAngleTeta == -1) {
        perAngleTeta = PLAYER_FOV / frame.width;
    }

    float distance, side, perc;


    for (int column = 0; column < frame.width; ++column) {
        raycast(player, perAngleTeta * (float)column - PLAYER_FOV * .5 + player.angle, maps[level], &distance, &side, &perc);
        printf("%f\n", perc);
        drawColumn(column, perc, distance, brick);
    }
}

void drawColumn(int column, float normalizedWidthPerc, float distance, Texture* texture) {
    int wallHeight = (int)((float)frame.height / distance);
    int offset = wallHeight != frame.height ? (int)((frame.height - wallHeight) * 0.5) : 0;

    int pixelInHeight = MIN(wallHeight, frame.height);
    float heightStep = (float)pixelInHeight / (float)texture->height;
    float currentStep = heightStep;

    float widthOffset = (float)texture->width * normalizedWidthPerc;
    int textureIndex = 0;
    for (int i = 0; i < pixelInHeight; ++i) {
        if (i > currentStep) {
            currentStep += heightStep;
            textureIndex++;
        }

        u32int textureDataIndex = ((int)widthOffset + textureIndex * texture->width) * 3;
        u32int r = texture->data[textureDataIndex] << 16;
        u32int g = texture->data[textureDataIndex + 1] << 8;
        u32int b = texture->data[textureDataIndex + 2];

        frame.pixels[(MAX(0, offset) + i) * frame.width + column] = r | g | b;
    }
}


void gameLoop() {
    drawBackground();
    drawWalls();
}

void gameKey(u32int key) {
    /**
     * https://learn.microsoft.com/it-it/windows/win32/inputdev/virtual-key-codes
     */

    switch (key) {
        case 'A':
            objRotation(&player, -ROT_SPEED);
            break;
        case 'D':
            objRotation(&player,  ROT_SPEED);
            break;
        case 'W':
            objMove(&player,  MOV_SPEED);
            break;
        case 'S':
            objMove(&player, -MOV_SPEED);
            break;
        default:
            break;
    }
}

static void objRotation(GameObj *gameObj, float rotation) {
    rotation += gameObj->angle;

    if (rotation < 0) {
        rotation += PI_times_2;
    } else if (rotation > PI_times_2) {
        rotation -= PI_times_2;
    }

    gameObj->angle = rotation;
}

static void objMove(GameObj *gameObj, float movement) {
    float dX = cos(gameObj->angle);
    float dY = sin(gameObj->angle);

    float newX = gameObj->x + dX * (movement + 0.3 * SIGN(movement));
    float newY = gameObj->y + dY * (movement + 0.3 * SIGN(movement));

    if (validEntityPosition(newX, newY)) {
        gameObj->x += dX * movement;
        gameObj->y += dY * movement;
    }

}

static int validEntityPosition(float x, float y) {
    return maps[level][(int)y * MAP_SIZE + (int)x].type != TILE_TYPE_WALL;
}

int ENTRY_POINT(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    init();
    startWindow(hInstance, gameLoop, gameKey);
}