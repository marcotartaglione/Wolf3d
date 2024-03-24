//
// Created by Marco on 24/03/2024.
//

#ifndef WOLF3D_TILE_H
#define WOLF3D_TILE_H

typedef enum {
    TILE_WALL,
    TILE_ENEMY,
    TILE_DROP,
    TILE_NONE
} TileType;

typedef enum {
    TILE_IDLE,
    TILE_MOVING
} TileState;

typedef struct {
    TileType    type;
    TileState   state;
    float       movedPerc;
} Tile;

#define TILE_EMPTY      { TILE_NONE, TILE_IDLE, 0 }
#define TILE_WALL_BRICK { TILE_WALL, TILE_IDLE, 0 }

#endif //WOLF3D_TILE_H
