//
// Created by Marco on 24/03/2024.
//

#ifndef WOLF3D_MAP_H
#define WOLF3D_MAP_H

#include "defs.h"
#include "tile.h"

typedef enum {
    EPISODE_1,
    EPISODE_2,
    EPISODE_3,
    EPISODE_4,
    EPISODE_5,
    EPISODE_6
} Episode;
#define N_EPISODES (EPISODE_6 + 1)

const char* episodeToString(Episode episode);

typedef enum {
    FLOOR_1,
    FLOOR_2,
    FLOOR_3,
    FLOOR_4,
    FLOOR_5,
    FLOOR_6,
    FLOOR_7,
    FLOOR_8,
    FLOOR_9,
    FLOOR_10,
} Floor;
#define N_FLOORS (FLOOR_10 + 1)

const char* floorToString(Floor floor);

typedef struct {
    Episode episode;
    Floor   floor;
    Tile    *tiles;
} Map;

Map* loadMap(char* filename);
Map** loadMapsFolder(char* directory);
void saveMap(Map *map, char* directory);

static char *generateMapFilePath(Episode episode, Floor floor, char *parentDirectory);

int mapValidatePosition(u32int level, float x, float y);

Map** maps;

// 53 31

#endif //WOLF3D_MAP_H
