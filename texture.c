//
// Created by Marco on 25/03/2024.
//
#include "texture.h"

Texture* readBMP(char* filename) {
    Texture *texture = malloc(sizeof(Texture));

    stbi_set_flip_vertically_on_load(1);
    texture->data = stbi_load(filename, &texture->width, &texture->height, &texture->bytesPerPixel, 3);
    return texture;
}