cmake_minimum_required(VERSION 3.29)
project(Tank_Attack)

set(CMAKE_CXX_STANDARD 20)

# Buscar el paquete SDL2
find_package(SDL2 REQUIRED)

# Buscar la biblioteca OpenGL
find_package(OpenGL REQUIRED)

# Añadir los directorios de las cabeceras de SDL2
include_directories(${SDL2_INCLUDE_DIRS})

# Añadir los directorios de las cabeceras de OpenGL
include_directories(${OPENGL_INCLUDE_DIR})

add_executable(Tank_Attack
        main.cpp
        development.cpp
        Game.cpp
        Game.h
        Player.cpp
        Player.h
        ACTank.cpp
        ACTank.h
        RATank.cpp
        RATank.h
)

# Enlazar con las bibliotecas de SDL2 y OpenGL
target_link_libraries(Tank_Attack ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})