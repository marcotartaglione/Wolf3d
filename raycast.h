//
// Created by Marco on 24/03/2024.
//

#ifndef WOLF3D_RAYCAST_H
#define WOLF3D_RAYCAST_H

#include "defs.h"
#include "tile.h"
#include <math.h>

void raycast(GameObj player, float angle, Tile map[], float *distance, float *side, float *hitPerc);

#endif //WOLF3D_RAYCAST_H