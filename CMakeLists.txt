cmake_minimum_required(VERSION 3.27)
project(Wolf3d)

set(CMAKE_CXX_STANDARD 17)

if (WOLF3D_EDITOR_MODE)
    add_definitions(-DWOLF3D_EDITOR_MODE=1)
endif (WOLF3D_EDITOR_MODE)

file(GLOB SOURCES *.c)
file(GLOB HEADERS *.h)

file(GLOB STB_IMAGE vendor/stb/*)

add_executable(Wolf3d WIN32 ${SOURCES} ${HEADERS} ${STB_IMAGE}
        tile.c
        editor.h
        editor.c
        game.h
        game.c
        gameObject.h
        gameObject.c
        map.c)