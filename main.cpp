#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <iostream>
#include "development.cpp"


int main(int argc, char* argv[]) {
    int rows = 12, cols = 16;  // Definir el tamaño del mapa
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


    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "No se pudo crear el renderer:" << SDL_GetError() << std:: endl;
        SDL_DestroyWindow(window);
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

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    graph.render(renderer);
    SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();



    return 0;

}