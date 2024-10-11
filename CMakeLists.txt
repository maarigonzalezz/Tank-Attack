cmake_minimum_required(VERSION 3.29)
project(Tank_Attack)

set(CMAKE_CXX_STANDARD 20)

# Encuentra el paquete de Qt5
find_package(Qt5 REQUIRED COMPONENTS Widgets Gui Core OpenGL)

# Añade directorios de include
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${OpenGL_INCLUDE_DIRS})

# Si usas señales y slots (Q_OBJECT), necesitas este bloque
set(HEADERS
        Game.h
        Player.h
        ACTank.h
        RATank.h
)

# Procesa las cabeceras para señales y slots, si usas Q_OBJECT
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})

# Añadir archivos fuente al ejecutable
add_executable(Tank_Attack
        main.cpp
        development.cpp
        Game.cpp
        Player.cpp
        ACTank.cpp
        RATank.cpp
        ${MOC_SOURCES} # Añadir los archivos generados por moc si usas Q_OBJECT
)

# Vincular las bibliotecas necesarias
target_link_libraries(Tank_Attack Qt5::Widgets Qt5::Gui Qt5::Core Qt5::OpenGL ${OPENGL_LIBRARIES})
