//
// Created by Marco on 24/03/2024.
//

#ifndef WOLF3D_RAYCAST_H
#define WOLF3D_RAYCAST_H

#include "defs.h"
#include "tile.h"
#include "gameObject.h"

Tile* filteredRaycast(GameObj *player, float angle, Map* map, TileType filter, float maxDistance, float *distance, int *side, float *hitPerc);

#endif //WOLF3D_RAYCAST_H
