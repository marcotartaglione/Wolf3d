//
// Created by Marco on 25/03/2024.
//

#ifndef WOLF3D_TEXTURE_H
#define WOLF3D_TEXTURE_H

#include "defs.h"

#include "vendor/stb/stb_image.h"

typedef struct {
    u32int  width, height;
    u32int  bytesPerPixel;
    byte    *data;
} Texture;

Texture* readBMP(char* filename);

#endif //WOLF3D_TEXTURE_H