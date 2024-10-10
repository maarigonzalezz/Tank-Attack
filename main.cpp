#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <iostream>
#include "development.cpp"

int main(int argc, char* argv[]) {
    int rows = 5, cols = 5;  // Definir el tamaño del mapa
    Graph graph(rows, cols);

    cout << "Mapa generado con obstáculos (X):\n";
    graph.mapaobstacles();


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Tank Attack!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Error al crear la ventana: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Aquí podrías dibujar en la ventana...
    }

    SDL_DestroyWindow(window);
    SDL_Quit();



    return 0;

}