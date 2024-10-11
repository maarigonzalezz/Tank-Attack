#include <SDL2/SDL.h>
#include <iostream>
#include "development.cpp"

bool running = true;
bool startScreen = true;

void renderStartScreen(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Color de fondo
    SDL_RenderClear(renderer);

    SDL_Rect playButton;
    playButton.x = 220;
    playButton.y = 400;
    playButton.w = 200;
    playButton.h = 50;

    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255); // Color del botón "Jugar"
    SDL_RenderFillRect(renderer, &playButton);

    // Renderiza el botón sin texto (puedes agregar gráficos o colores aquí)
    SDL_RenderPresent(renderer);
}

void handleStartScreenEvents(SDL_Event& event) {
    if (event.type == SDL_QUIT) {
        running = false;
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if (x >= 200 && x <= 400 && y >= 150 && y <= 500) {
            startScreen = false;
        }
    }
}

int main(int argc, char* argv[]) {
    int rows = 12, cols = 16;  // Definir el tamaño del mapa
    Graph graph(rows, cols);

    std::cout << "Mapa generado con obstáculos (X):\n";
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
        std::cerr << "No se pudo crear el renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (startScreen) {
                handleStartScreenEvents(event); // Maneja eventos en la pantalla de inicio
            } else {
                // Maneja eventos del juego (aquí podrías agregar más lógica más tarde)
                if (event.type == SDL_QUIT) {
                    running = false;
                }
            }
        }

        if (startScreen) {
            renderStartScreen(renderer); // Renderiza la pantalla de inicio sin texto
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            graph.render(renderer); // Renderiza el mapa
            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
