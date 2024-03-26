//
// Created by Marco on 24/03/2024.
//

#ifndef WOLF3D_TILE_H
#define WOLF3D_TILE_H

typedef enum {
    TILE_TYPE_WALL,
    TILE_TYPE_ENEMY,
    TILE_TYPE_DROP,
    TILE_TYPE_NONE
} TileType;

typedef enum {
    TILE_STATE_IDLE,
    TILE_STATE_MOVING,
    TILE_STATE_SHOOTING,
    TILE_STATE_DEAD,
} TileState;

typedef struct {
    TileType    type;
    TileState   state;
    float       movedPerc;
} Tile;

#define TILE_EMPTY      { TILE_TYPE_NONE, TILE_STATE_IDLE, 0 }
#define TILE_WALL_BRICK { TILE_TYPE_WALL, TILE_STATE_IDLE, 0 }

#endif //WOLF3D_TILE_H
