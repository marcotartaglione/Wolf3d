#ifndef WOLF3D_DEFS_H
#define WOLF3D_DEFS_H

//
// Constants
//
#define ENTRY_POINT (WINAPI wWinMain)
//#define WOLF3D_EDITOR_MODE

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

#define DOOR_RECESS 0.2f

//
// Types
//
typedef unsigned int u32int;
typedef unsigned char byte;
typedef byte bool;

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
#define SIGN(x)     ((x) >= 0  ?  1  :  -1)
#define ABS(x)      ((x) >= 0  ? (x) : -(x))
#define MIN(x, y)   ((x) < (y) ? (x) :  (y))
#define MAX(x, y)   ((x) > (y) ? (x) :  (y))

#ifndef WOLF3D_ERROR
#include <stdio.h>
#include <stdlib.h>

static void Wolf3D_exit(int code, int line, char *file, char *error) {
    fprintf(stderr, "%d error at:\n\t%s:%d -> %s", code, file, line, error);
    exit(code);
}

#define WOLF3D_ERROR(string) do { \
                            __debugbreak(); \
                            Wolf3D_exit(-1, __LINE__, __FILE__, string); \
                            } while(0)
#endif //WOLF3D_ERROR


#endif //WOLF3D_DEFS_H