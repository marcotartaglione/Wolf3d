#ifndef WOLF3D_DEFS_H
#define WOLF3D_DEFS_H

//
// Constants
//
#define ENTRY_POINT (WINAPI wWinMain)

#define PI                  3.14159265359   // PI           -> 180deg
#define PI_times_2          6.28318530718   // PI * 2       ->   0deg / 360deg
#define PI_div_2            1.57079632679   // PI / 2       ->  90deg
#define PI_times_3_div_2    4.71238898038   // PI * 3 / 2   -> 270deg

#define MAP_SIZE    64
#define MAP_NUMBER  1

#define PLAYER_FOV PI_div_2

#define ROOF_COLOR  0x00262626
#define FLOOR_COLOR 0x00474747

#define ROT_SPEED (PI / 20)
#define MOV_SPEED 0.25f

//
// Types
//
typedef unsigned int    u32int;
typedef unsigned char   byte;

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

//
// Functions
//
#define SIGN(x)     (x >= 0 ? 1 : -1)
#define ABS(x)      (x >= 0 ? x : -x)
#define MIN(x, y)   (x < y ? x : y)
#define MAX(x, y)   (x > y ? x : y)

#endif //WOLF3D_DEFS_H