#ifndef ACTANK_H
#define ACTANK_H
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include "Tank.h"

using namespace std;
class ACTank : public Tank1 { // Usa "public" para herencia pública
private:
    void BFS(Vector2 start, Vector2 goal, const std::vector<std::vector<int>>& adjMatrix, int cellsize);

public:
    // Constructor de ACTank que llama al constructor de Tank1
    ACTank(Vector2 pos, float rot, Texture2D img) : Tank1(pos, rot, img) {}

    void movement(Vector2 targetPosition, const std::vector<std::vector<int>>& adjMatrix, int cellSize) override;

};



#endif //ACTANK_H