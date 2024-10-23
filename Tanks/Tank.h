//
// Created by maarigonzalezz on 21/10/24.
//

#ifndef TANK_H
#define TANK_H
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <iostream>
#include <random>
#include <string>

using namespace std;
class Tank1 {
public:
    Tank1(Vector2 pos, float rot, Color col) : position(pos), rotation(rot), color(col) {}

    const float tankSpeed = 200.0f;
    const float width =50.0f;
    const float height = 30.0f;
    Vector2 position;
    float rotation;
    Color color;
    bool active = true; // Tanque activo o destruido
    void DrawTank();
    bool IsMouseOver(Vector2 mousePosition);
};



#endif //TANK_H
