cmake_minimum_required(VERSION 3.29)
project(Tank_Attack)

set(CMAKE_CXX_STANDARD 20)

# Busca la librería raylib AAAAAAAAAA
find_package(raylib REQUIRED)
# Incluir los directorios de raylib
include_directories(${RAYLIB_INCLUDE_DIRS})




# Encuentra el paquete de Qt5
find_package(Qt5 REQUIRED COMPONENTS Widgets Gui Core OpenGL)

# Añade directorios de include
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${OpenGL_INCLUDE_DIRS})

# Añadir archivos fuente al ejecutable
add_executable(Tank_Attack
        main.cpp
        Game.h
        Player.h
        Tanks/ACTank.h
        Tanks/RATank.h
        development.cpp
        Game.cpp
        Player.cpp
        Tanks/ACTank.cpp
        Tanks/RATank.cpp
        Tanks/Tank.cpp
        Tanks/Tank.h
        Tanks/RATank.cpp
)

qt_add_resources(TARGET Tank_Attack FILES images.qrc)

# Vincular raylib a tu proyecto AAAAAAAAAh
target_link_libraries(Tank_Attack raylib)

# Vincular las bibliotecas necesarias
target_link_libraries(Tank_Attack Qt5::Widgets Qt5::Gui Qt5::Core Qt5::OpenGL ${OPENGL_LIBRARIES})
