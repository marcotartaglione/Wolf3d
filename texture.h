//
// Created by Marco on 25/03/2024.
//

#ifndef WOLF3D_TEXTURE_H
#define WOLF3D_TEXTURE_H

#include "defs.h"

#include "vendor/stb/stb_image.h"
#include "tile.h"

typedef struct {
    u32int  width, height;
    u32int  bytesPerPixel;
    byte    *data;
} Texture;

Texture* loadTexture(char* filename);
Texture** loadTexturesFolder(char* directory);

#endif //WOLF3D_TEXTURE_H
