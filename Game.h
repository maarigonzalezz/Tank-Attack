#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <iostream>

using  namespace std;
class Game {
public:
    Game();
    //Destructor (no se como se pone ese guion raro)

    void init(const char* title, int x, int y, int width, int height, bool fullscreen);

    void handle_events();
    void update();
    void render();
    void clean();

    bool running();
private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
};



#endif //GAME_H
