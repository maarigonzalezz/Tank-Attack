#include "development.cpp"
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <iostream>

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
};


class Game {
public:
    Game(bool s): start(false) {
        s = start;
        cout << "aqui?" << endl;
    }
    void tGame(bool a);
    void FireBullet(Bullet &bullet, Tank &tank);
    bool MoveTankToMouse(Tank &tank, Vector2 targetPosition, float deltaTime, const Obstacle &obstacle);
    void DrawTank(Tank tank);
    void DrawObstacle(const Obstacle& obstacle) {
        DrawRectangleRec(obstacle.rect, obstacle.color);
    }
    bool CheckCollisionTankObstacle(const Tank &tank, const Obstacle &obstacle);
    bool CheckCollisionBulletObstacle(const Bullet &bullet, const Obstacle &obstacle);
    void BounceBullet(Bullet &bullet, const Obstacle &obstacle);
    int SelectTankByClick(Tank* tanks, int numTanks, Vector2 mousePosition);

    bool CheckCollisionBulletObstacles(Bullet bullet, std::vector<Obstacle> vector1);

    // Nueva función para verificrar colisión entre bala y tanque
    bool CheckCollisionBulletTank(const Bullet &bullet, const Tank &tank) {
        if (!tank.active || bullet.shooter == &tank) return false; // No colisionar con tanques inactivos o el tanque que disparó
        return CheckCollisionPointCircle(bullet.position, tank.position, 15); // Asumimos un radio de 15 para el tanque
    }


private:
    bool start;
    bool isMoving;
    bool turnComplete;
    const int screenWidth = 1000;
    const int screenHeight = 800;
    const float tankSpeed = 200.0f;
    const float bulletSpeed = 400.0f;
    const float maxMoveDistance = 200.0f;
    const int numTanksPerPlayer = 4;
    float matchDuration = 300.0f; // Duración de la partida en segundos
    const int numRows = 15; // Filas del mapa
    const int numCols = 15; // Columnas del mapa
    const float cellSize = 50.0f; // Tamaño de cada celda
    const int numObstacles = 20; // Número de obstáculos aleatorios
    const int tankRadius = 15;
    const int BulletRadius = 15;
    std::vector<Vector2> restrictedPositions;
};







//#endif //GAME_H
