#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <algorithm>

#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <vector>
#include <bits/ranges_algo.h>


using namespace std;

std::vector<Vector2> BFS(const std::vector<std::vector<int>>& matrizAdyacencia, int startRow, int startCol, int targetRow, int targetCol);
std::vector<Vector2> Dijkstra(const std::vector<std::vector<int>>& matrizAdyacencia, int startRow, int startCol, int targetRow, int targetCol);




#endif //ALGORITHMS_H
