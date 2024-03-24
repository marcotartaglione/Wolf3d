cmake_minimum_required(VERSION 3.27)
project(Wolf3d)

set(WIN32 True)
set(CMAKE_CXX_STANDARD 17)

add_executable(Wolf3d WIN32
        window.h
        window.c
        Wolf3D.c
        defs.h
        Wolf3D.h
        raycast.h
        raycast.c
        map.h
        tile.h)
