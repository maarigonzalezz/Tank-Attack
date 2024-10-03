
#include "Game.h"
Game::Game() {

}

void Game::init(const char *title, int x, int y, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        cout << "empezando jijiji" << endl;
        window = SDL_CreateWindow(title, x, y, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 242, 236, 206, 1);
        }
        isRunning = true;
    }
    else {
        isRunning = false;
    }
}

void Game::handle_events() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;

    }
}

void Game::render() {
    SDL_RenderClear(renderer);
    //tipo aqui se añaden cosas al render jaja
    SDL_RenderPresent(renderer);
}

void Game::update() {

}

bool Game::running() {

}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "se destruyo todo vv";
}
