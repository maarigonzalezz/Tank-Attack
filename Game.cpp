#include "Game.h"
#include "raylib.h"

std::vector<Obstacle> obstacles;

void Game::tGame(bool a) {
    if (a == true){
        InitWindow(screenWidth, screenHeight, "Juego de Tanques por Turnos");
        cout << "alo" << endl;


        //creando el grafo
        Graph mapGraph(numRows, numCols);
        mapGraph.generateRandomObstacles(numObstacles);
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (mapGraph.isObstacle(i, j)) {
                    // Crear un obstáculo en la celda actual
                    Obstacle obstacle = {{j * cellSize, i * cellSize, cellSize, cellSize}, DARKGRAY};
                    obstacles.push_back(obstacle); // Añadir el obstáculo a la lista
                }
            }
        }

        // Definir un obstáculo
        Obstacle obstacle = {{0, 0, 100, 100}, DARKGRAY};

        SetTargetFPS(60);

        while (!WindowShouldClose()) {
            float deltaTime = GetFrameTime();
            matchDuration -= deltaTime;

            if (matchDuration <= 0) {
                matchDuration = 0; // Evitar que sea negativo
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("Fin de la partida", screenWidth / 2 - 100, screenHeight / 2 - 20, 40, RED);
                EndDrawing();
                continue; // Salta al siguiente ciclo para evitar continuar el juego
            }
        }








    }
}