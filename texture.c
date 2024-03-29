//
// Created by Marco on 25/03/2024.
//
#include "texture.h"
#include "string.h"
#include <stdlib.h>

Texture* loadTexture(char* filename) {
    // BMP file
    Texture *texture = malloc(sizeof(Texture));

    stbi_set_flip_vertically_on_load(1);
    texture->data = stbi_load(filename, &texture->width, &texture->height, &texture->bytesPerPixel, 3);
    return texture;
}

Texture** loadTexturesFolder(char* directory) {
    Texture** textures = (Texture**) malloc(sizeof(Texture*) * N_WALL);

    for (int i = 0; i <= N_WALL; ++i) {
        char *copy = strdup(directory);
        const char *fileName = wallToString(i);
        char *filePath = malloc(strlen(copy) + strlen(fileName) + 5);

        strcpy(filePath, copy);
        strcat(filePath, fileName);
        strcat(filePath, ".png");

        textures[i] = loadTexture(filePath);

        free(copy);
        free(filePath);
    }

    return textures;
}