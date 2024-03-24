#ifndef WOLF3D_DEFS_H
#define WOLF3D_DEFS_H

//
// Constants
//
#define PI                  3.14159265359   // PI           -> 180deg
#define PI_times_2          6.28318530718   // PI * 2       ->   0deg / 360deg
#define PI_div_2            1.57079632679   // PI / 2       ->  90deg
#define PI_times_3_div_2    4.71238898038   // PI * 3 / 2   -> 270deg

#define MAP_SIZE    8
#define MAP_NUMBER  1

#define PLAYER_FOV PI

#define ROOF_COLOR  0x00262626
#define FLOOR_COLOR 0x00474747

//
// Types
//
#define u32int unsigned int

#define true 1
#define false 0

typedef enum {
    STATE_IDLE,
    STATE_WALKING,
    STATE_RUNNING,
    STATE_SHOOTING
} State;

typedef enum {
    DIRECTION_NORTH,
    DIRECTION_SOUTH,
    DIRECTION_WEST,
    DIRECTION_EAST
} Direction;

typedef struct {
    float       x, y;
    float       angle;
    State       state;
    Direction   direction;
} GameObj;

//
// Functions
//
/*float fixangle(float angle) {
    if (angle < 0)
        return angle += PI_times_2;
    else if (angle > PI_times_2)
        return angle -= PI_times_2;
    else
        return angle;
}*/

#endif //WOLF3D_DEFS_H