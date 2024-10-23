#include "Game.h"
#include <iostream>
#include "raylib.h"

using namespace std;

int main() {
    // Crear la instancia de Game
    Game game(true);
    cout << "trying" << endl;
    //game.Pmenu();
    game.sGame(true);
    return 0;
}