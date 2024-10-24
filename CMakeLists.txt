cmake_minimum_required(VERSION 3.29)
project(Tank_Attack)

set(CMAKE_CXX_STANDARD 20)

# Busca la librería raylib
find_package(raylib REQUIRED)
# Incluir los directorios de raylib
include_directories(${RAYLIB_INCLUDE_DIRS})


# Añadir archivos fuente al ejecutable
add_executable(Tank_Attack
        main.cpp
        Game.h
        GameLogic/Player.h
        Tanks/ACTank.h
        Tanks/RATank.h
        Development/Graph.cpp
        Game.cpp
        GameLogic/Player.cpp
        Tanks/ACTank.cpp
        Tanks/RATank.cpp
        Tanks/Tank.cpp
        Tanks/Tank.h
        Tanks/RATank.cpp
        Tanks/Bullet.cpp
        Tanks/Bullet.h
        Development/Algorithms.cpp
        Development/Algorithms.h
        GameLogic/Obstacle.h
)

# Vincular raylib a tu proyecto AAAAAAAAAh
target_link_libraries(Tank_Attack raylib)

