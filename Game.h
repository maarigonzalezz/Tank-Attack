#include "Development/Graph.cpp"
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <iostream>
#include "GameLogic/Player.h"
#include "Tanks/Tank.h"
#include "Tanks/Bullet.h"
#include "GameLogic/Obstacle.h"

using namespace std;


class Game {
public:

    Game(bool s): start(false) {
        s = start;
    }

    void sGame(bool a);
    void Pmenu();

    bool MoveTankToMouse(Tank1 &tank, Vector2 targetPosition, float deltaTime, const Obstacle &obstacle);
    void DrawMap(const std::vector<std::vector<int>>& adjMatrix, int cellSize, Texture2D texture2, Texture2D texturebg);
    void DrawObstacle(const Obstacle& obstacle);
    bool CheckCollisionTankObstacle(const Tank1 &tank, std::vector<Obstacle> vector1);
    int SelectTankByClick(Player* player, int numTanks, Vector2 mousePosition);
    bool CheckCollisionBulletTank(const Bullet &bullet, const Tank1 &tank);


private:
    bool start;
    bool isMoving = false;
    bool turnComplete;
    const int screenWidthP = 1200;
    const int screenHeightP = 600;
    float newWidth = 1000; // Ancho deseado
    float newHeight = 600; // Alto deseado
    const int screenWidth = 800;
    const int screenHeight = 800;
    const int numTanksPerPlayer = 4;
    float matchDuration = 300.0f; // Duración de la partida en segundos
    const int numRows = screenHeight/50; // Filas del mapa
    const int numCols = screenWidth/50; // Columnas del mapa
    const float cellSize = 50.0f; // Tamaño de cada celda
    const int numObstacles = 23; // Número de obstáculos aleatorios
    const int tankRadius = 15;
    const int BulletRadius = 15;
    const float tankSpeed = 200.0f;
    const float maxMoveDistance = 20.0f;
    std::vector<Vector2> restrictedPositions;
};







//#endif //GAME_H
