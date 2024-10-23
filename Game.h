#include "development.cpp"
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <iostream>
#include "Player.h"
#include "Tanks/Tank.h"
#include "Player.h"

using namespace std;

// Definir función para comparar colores

struct Tank {
    Vector2 position;
    float rotation;
    Color color;
    bool active = true; // Tanque activo o destruido
};

struct Bullet {
    Vector2 position;
    Vector2 velocity;
    bool active;
    Tank* shooter; // Referencia al tanque que disparó la bala
};

struct Obstacle {
    Rectangle rect;
    Color color;
    Texture2D obs;
};


class Game {
public:

    Game(bool s): start(false) {
        s = start;
        cout << "aqui?" << endl;
    }
    void tGame(bool a);
    void sGame(bool a);
    void Pmenu();
    bool ColorsAreEqual(Color c1, Color c2);
    void FireBullet(Bullet &bullet, Tank &tank);
    bool MoveTankToMouse(Tank &tank, Vector2 targetPosition, float deltaTime, const Obstacle &obstacle);

    void DrawMap(const std::vector<std::vector<int>>& adjMatrix, int cellSize, Texture2D texture2, Texture2D texturebg);
    void DrawTank(Tank tank);
    void DrawObstacle(const Obstacle& obstacle);
    bool CheckCollisionTankObstacle(const Tank &tank, std::vector<Obstacle> vector1);
    bool CheckCollisionBulletObstacle(const Bullet &bullet, const Obstacle &obstacle);
    void BounceBullet(Bullet &bullet, const Obstacle &obstacle);
    int SelectTankByClick(Player* player, int numTanks, Vector2 mousePosition);

    bool CheckCollisionBulletObstacles(Bullet bullet, std::vector<Obstacle> vector1);
    bool CheckCollisionBulletTank(const Bullet &bullet, const Tank &tank);
    void CountTanksByColor(Tank* player1Tanks, Tank* player2Tanks, int& yellowCount, int& skyBlueCount, int& redCount, int& blueCount);


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
    const float tankSpeed = 200.0f;
    const float bulletSpeed = 400.0f;
    const float maxMoveDistance = 200.0f;
    const int numTanksPerPlayer = 4;
    float matchDuration = 300.0f; // Duración de la partida en segundos
    const int numRows = screenHeight/50; // Filas del mapa
    const int numCols = screenWidth/50; // Columnas del mapa
    const float cellSize = 50.0f; // Tamaño de cada celda
    const int numObstacles = 23; // Número de obstáculos aleatorios
    const int tankRadius = 15;
    const int BulletRadius = 15;
    std::vector<Vector2> restrictedPositions;
};







//#endif //GAME_H
