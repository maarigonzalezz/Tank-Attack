#include <SDL2/SDL.h>
#include <iostream>
#include "Game.h"

Game *game = nullptr;

int main(int argc, const char * argv[]) {

    /*SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Tank Attack!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 242, 236, 206, 0.8);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);*/

    game = new Game();
    game->init("Tank Attack!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    while (game->running()) {
        game->handle_events();
        game->update();
        game->render();
    }
    game->clean();
    return 0;
}