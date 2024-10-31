#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

class Algorithms {
    Algorithms() = default;
    void BFS(Vector2 start, Vector2 goal, const std::vector<std::vector<int>>& adjMatrix, int cellsize);
    std::vector<Vector2> Dijkstra(Vector2 start, Vector2 goal, const std::vector<std::vector<int>>& adjMatrix, int cellsize);
};



#endif //ALGORITHMS_H
