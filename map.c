//
// Created by Marco on 27/03/2024.
//
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *episodeToString(Episode episode) {
    switch (episode) {
        case EPISODE_1:
            return "EPISODE_1";
        case EPISODE_2:
            return "EPISODE_2";
        case EPISODE_3:
            return "EPISODE_3";
        case EPISODE_4:
            return "EPISODE_4";
        case EPISODE_5:
            return "EPISODE_5";
        case EPISODE_6:
            return "EPISODE_6";
        default:
            return NULL;
    }
}

const char *floorToString(Floor floor) {
    switch (floor) {
        case FLOOR_1:
            return "FLOOR_1";
        case FLOOR_2:
            return "FLOOR_2";
        case FLOOR_3:
            return "FLOOR_3";
        case FLOOR_4:
            return "FLOOR_4";
        case FLOOR_5:
            return "FLOOR_5";
        case FLOOR_6:
            return "FLOOR_6";
        case FLOOR_7:
            return "FLOOR_7";
        case FLOOR_8:
            return "FLOOR_8";
        case FLOOR_9:
            return "FLOOR_9";
        case FLOOR_10:
            return "FLOOR_10";
        default:
            return NULL;
    }
}

Map *loadMap(char *filename) {
    if (filename == NULL)
        WOLF3D_ERROR(-1, "Filename is null");

    FILE *fp;
    fopen_s(&fp, filename, "rb");

    if (fp == NULL)
        WOLF3D_ERROR(-1, "File was not found");

    Map *map = (Map *) malloc(sizeof(Map));

    if (fread(&map->floor, sizeof(Floor), 1, fp) != 1) {
        WOLF3D_ERROR(-1, "Error reading map's floor");
    }
    if (fread(&map->episode, sizeof(Episode), 1, fp) != 1) {
        WOLF3D_ERROR(-1, "Error reading map's episode");
    }

    map->tiles = (Tile *) malloc(sizeof(Tile) * MAP_SIZE * MAP_SIZE);
    if (map->tiles == NULL) {
        WOLF3D_ERROR(-1, "Memory alloc error");
    }

    if (fread(map->tiles, sizeof(Tile), MAP_SIZE * MAP_SIZE, fp) != MAP_SIZE * MAP_SIZE) {
        WOLF3D_ERROR(-1, "Error reading map tiles");
    }

    return map;
}

Map **loadMapsFolder(char *directory) {
    Map **maps = (Map **) malloc(sizeof(Map *) * N_WALL);
    if (maps == NULL) {
        WOLF3D_ERROR(-1, "Memory alloc failed");
    }

    char *copy = _strdup(directory);
    if (copy == NULL) {
        free(maps);
        WOLF3D_ERROR(-1, "Directory string copy error");
    }

    // TODO cambiare controlli a N_EPISODES e N_FLOORS
    for (int episode = 0; episode < EPISODE_2; ++episode) {
        for (int floor = 0; floor < FLOOR_2; ++floor) {
            char *filePath = generateFilePath(episode, floor, directory);
            if (filePath == NULL) {
                free(copy);
                for (int i = 0; i < episode * N_EPISODES + floor; ++i) {
                    free(maps[i]);
                }
                free(maps);
                WOLF3D_ERROR(-1, "File path generation fail");
            }

            maps[episode * N_EPISODES + floor] = loadMap(filePath);
            free(filePath);
        }
    }
    free(copy);

    return maps;
}

void saveMap(Map *map, char* directory) {
    if (map == NULL) {
        WOLF3D_ERROR(-1, "Map was null");
    }

    char* filePath = generateFilePath(map->episode, map->floor, directory);
    if (filePath == NULL) {
        WOLF3D_ERROR(-1, "File path generation fail");
    }

    FILE *fp;
    fopen_s(&fp, filePath, "wb");
    if (fp == NULL) {
        WOLF3D_ERROR(-1, "Error opening file for writing");
    }

    if (fwrite(&map->floor, sizeof(Floor), 1, fp) != 1) {
        fclose(fp);
        WOLF3D_ERROR(-1, "Error writing map's floor");
    }

    if (fwrite(&map->episode, sizeof(Episode), 1, fp) != 1) {
        fclose(fp);
        WOLF3D_ERROR(-1, "Error writing map's episode");
    }

    if (fwrite(map->tiles, sizeof(Tile), MAP_SIZE * MAP_SIZE, fp) != MAP_SIZE * MAP_SIZE) {
        fclose(fp);
        WOLF3D_ERROR(-1, "Error writing map tiles");
    }

    fclose(fp);
}

static char *generateFilePath(Episode episode, Floor floor, char *parentDirectory) {
    const char *episodeString = episodeToString(episode);
    const char *floorString = floorToString(floor);

    size_t filePathLen = strlen(parentDirectory) + strlen(episodeString) + 1 + strlen(floorString) + 5;
    char *filePath = (char *) malloc(filePathLen * sizeof(char));
    if (filePath == NULL) {
        if (parentDirectory != NULL) {
            free(parentDirectory);
        }
        for (int i = 0; i < episode * N_EPISODES + floor; ++i) {
            free(maps[i]);
        }
        free(maps);
        WOLF3D_ERROR(-1, "Memory alloc failed");
    }

    if (parentDirectory) {
        strcpy_s(filePath, filePathLen, parentDirectory);
        strcat_s(filePath, filePathLen, episodeString);
    } else {
        strcpy_s(filePath, filePathLen, episodeString);
    }
    strcat_s(filePath, filePathLen, ".");
    strcat_s(filePath, filePathLen, floorString);
    strcat_s(filePath, filePathLen, ".map");

    return filePath;
}

int mapValidatePosition(u32int level, float x, float y) {
    return maps[level]->tiles[(int) y * MAP_SIZE + (int) x].type != TILE_TYPE_WALL;
}