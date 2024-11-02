#ifndef TANK_H
#define TANK_H
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <random>
#include <string>
#include "../Development/Algorithms.h"
#include "../GameLogic/Obstacle.h"

using namespace std;
struct Tank {
    Vector2 position;
    float rotation;
    Color color;
    bool active = true; // Tanque activo o destruido
    int vida = 100;
};

void DrawTank(const Tank &tank);
int SelectTankByClick(Tank* tanks, int numTanks, Vector2 mousePosition);
int Restlife(Tank &tank);
void MoveTankAlongPath(Tank &tank, const vector<Vector2>& path, float deltaTime, float cellSize);
bool RAmovement(Tank &tank, Vector2 targetPosition, float deltaTime, const vector<vector<int>>& matrizAdyacencia, const std::vector<Obstacle>& obstacles);
bool ACmovement(Tank &tank, Vector2 targetPosition, float deltaTime, const vector<vector<int>>& matrizAdyacencia, const std::vector<Obstacle>& obstacles);
bool CheckCollisionTankObstacle(const Tank &tank, const std::vector<Obstacle>& obstacles);



#endif //TANK_H
