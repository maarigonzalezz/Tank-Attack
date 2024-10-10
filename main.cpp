#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <iostream>
#include "development.cpp"

int main(int argc, char* argv[]) {

    bool obstacles[] = {false, false, false, // Fila 0
                        false, true,  false, // Fila 1
                        false, false, false}; // Fila 2

    Graph g(3, 3, obstacles); // Crear el grafo

    // Imprimir la matriz de adyacencia
    g.toString();

    // Verificar si todos los nodos accesibles están conectados
    if (g.areAllAccessibleNodesConnected()) {
        cout << "Todos los nodos accesibles están conectados." << endl;
    } else {
        cout << "No todos los nodos accesibles están conectados." << endl;
    }



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