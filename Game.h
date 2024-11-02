#include "Development/Graph.cpp"
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <iostream>
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

    bool MoveTankToMouse(Tank &tank, Vector2 targetPosition, float deltaTime, const vector<vector<int>>& matrizAdyacencia, const Obstacle &obstacle);
    void DrawMap(const std::vector<std::vector<int>>& adjMatrix, int cellSize, Texture2D texture2, Texture2D texturebg);
    void DrawObstacle(const Obstacle& obstacle);
    bool CheckCollisionTankObstacle(const Tank &tank, const std::vector<Obstacle>& vector1);
    bool CheckCollisionBulletTank(const Bullet &bullet, const Tank &tank);
    void FireBullet(Bullet &bullet, Tank &tank);
    bool CheckCollisionBulletObstacles(Bullet bullet, const std::vector<Obstacle>& obstacles);



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
    float matchDuration = 30.0f; // Duración de la partida en segundos
    const int numRows = screenHeight/50; // Filas del mapa
    const int numCols = screenWidth/50; // Columnas del mapa
    const float cellSize = 50.0f; // Tamaño de cada celda
    const int numObstacles = 23; // Número de obstáculos aleatorios
    const int tankRadius = 15;
    const int BulletRadius = 10;
    const float tankSpeed = 200.0f;
    const float bulletSpeed = 400.0f;
    const float maxMoveDistance = 20.0f;
    std::vector<Vector2> restrictedPositions;
    Rectangle* currentplayerrect[4];
    Rectangle* nextplayerrect[4];
    Vector2 moveTarget = {0, 0}; // Destino de movimiento
};







//#endif //GAME_H
