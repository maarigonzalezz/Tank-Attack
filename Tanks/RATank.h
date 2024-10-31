#ifndef RATANK_H
#define RATANK_H
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include "Tank.h"

using namespace std;
class RATank : public Tank1 { // Usa "public" para herencia pública

public:
    // Constructor de ACTank que llama al constructor de Tank1
    RATank(Vector2 pos, float rot, Texture2D img) : Tank1(pos, rot, img) {}

    void movement(Vector2 targetPosition, const std::vector<std::vector<int>>& adjMatrix, int cellSize) override;
private:
    void Dijkstra(Vector2 targetPosition, const std::vector<std::vector<int>>& matrizAdyacencia, int cellSize);
};




#endif //RATANK_H