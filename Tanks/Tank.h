//
// Created by maarigonzalezz on 21/10/24.
//

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

using namespace std;
class Tank1 {
public:
public:
    Tank1(Vector2 pos, float rot, Texture2D img);
    virtual ~Tank1() = default; // Declaración del destructor virtual

    virtual void movement(Vector2 targetPosition, const std::vector<std::vector<int>>& adjMatrix, int cellSize) = 0; // Método virtual puro

    const float tankSpeed = 200.0f;
    const float width = 50.0f;
    const float height = 30.0f;
    Vector2 position;
    float rotation;
    Texture2D color;
    bool active = true; // Tanque activo o destruido
    void DrawTank();
    bool IsMouseOver(Vector2 mousePosition);
    //virtual void movement(Vector2 targetPosition, const std::vector<std::vector<int>>& adjMatrix, int cellSize);
    virtual int probN();
    bool IsCellFree(Vector2 position, const std::vector<std::vector<int>>& adjMatrix, int cellSize);
    Vector2 GetRandomAdjacentCell(Vector2 currentPosition, const std::vector<std::vector<int>>& adjMatrix);
};



#endif //TANK_H
