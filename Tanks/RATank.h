#ifndef RATANK_H
#define RATANK_H
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include "Tank.h"

using namespace std;
class RATank : public Tank1 { // Usa "public" para herencia pública
private:
    int probN(); // Método privado

public:
    // Constructor de ACTank que llama al constructor de Tank1
    RATank(Vector2 pos, float rot, Color col) : Tank1(pos, rot, col) {}

    void movement();

};




#endif //RATANK_H