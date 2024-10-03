cmake_minimum_required(VERSION 3.29)
project(Tank_Attack)

set(CMAKE_CXX_STANDARD 20)

# Buscar el paquete SDL2
find_package(SDL2 REQUIRED)

# Añadir los directorios de las cabeceras de SDL2
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Tank_Attack
        main.cpp
        Game.cpp
        Game.h)

# Enlazar con las bibliotecas de GTK
target_link_libraries(Tank_Attack ${SDL2_LIBRARIES})