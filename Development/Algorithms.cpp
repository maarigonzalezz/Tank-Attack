//
// Created by maarigonzalezz on 23/10/24.
//

#include "Algorithms.h"
#include "../Tanks/ACTank.h"
#include "../Tanks/RATank.h"

void RATank::Dijkstra(Vector2 targetPosition, const std::vector<std::vector<int>>& matrizAdyacencia, int cellSize) {
    int rows = matrizAdyacencia.size();
    int cols = matrizAdyacencia[0].size();
    int startRow = static_cast<int>(position.y) / cellSize;
    int startCol = static_cast<int>(position.x) / cellSize;
    int targetRow = static_cast<int>(targetPosition.y) / cellSize;
    int targetCol = static_cast<int>(targetPosition.x) / cellSize;

    // Vector para distancias y nodos previos
    std::vector<std::vector<int>> dist(rows, std::vector<int>(cols, std::numeric_limits<int>::max()));
    std::vector<std::vector<Vector2>> previous(rows, std::vector<Vector2>(cols, {-1, -1}));
    dist[startRow][startCol] = 0;

    // Cola de prioridad para distancias mínimas
    auto comp = [](const std::pair<int, int>& a, const std::pair<int, int>& b) { return a.second > b.second; };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(comp)> pq(comp);
    pq.push({startRow * cols + startCol, 0}); // Nodo de inicio

    std::vector<Vector2> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // Direcciones (arriba, abajo, derecha, izquierda)

    while (!pq.empty()) {
        auto current = pq.top();
        pq.pop();

        int currentRow = current.first / cols;
        int currentCol = current.first % cols;

        if (currentRow == targetRow && currentCol == targetCol) break;

        for (auto& dir : directions) {
            int newRow = currentRow + dir.y;
            int newCol = currentCol + dir.x;

            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && matrizAdyacencia[newRow][newCol] != 1) {
                int newDist = dist[currentRow][currentCol] + 1;
                if (newDist < dist[newRow][newCol]) {
                    dist[newRow][newCol] = newDist;
                    previous[newRow][newCol] = {static_cast<float>(currentRow), static_cast<float>(currentCol)};
                    pq.push({newRow * cols + newCol, newDist});
                }
            }
        }
    }

    // Reconstruir la ruta desde `previous`
    Vector2 pathNode = {static_cast<float>(targetRow), static_cast<float>(targetCol)};
    std::vector<Vector2> path;
    while (pathNode.x != -1 && pathNode.y != -1) {
        path.insert(path.begin(), {pathNode.y * cellSize + cellSize / 2, pathNode.x * cellSize + cellSize / 2});
        pathNode = previous[static_cast<int>(pathNode.x)][static_cast<int>(pathNode.y)];
    }

    // Si la ruta existe, moverse a la primera posición de la ruta
    if (path.size() > 1) {
        position = path[1];  // Mover a la siguiente posición en el camino
    }
}

// Definición del operador para comparar Vector2
bool operator!=(const Vector2& a, const Vector2& b) {
    return (a.x != b.x) || (a.y != b.y);
}

bool operator==(const Vector2& a, const Vector2& b) {
    return (a.x == b.x) && (a.y == b.y);
}

void ACTank::BFS(Vector2 targetPosition, const std::vector<std::vector<int>>& matrizAdyacencia, int cellSize) {
    int rows = matrizAdyacencia.size();
    int cols = matrizAdyacencia[0].size();
    int startRow = static_cast<int>(position.y) / cellSize;
    int startCol = static_cast<int>(position.x) / cellSize;
    int targetRow = static_cast<int>(targetPosition.y) / cellSize;
    int targetCol = static_cast<int>(targetPosition.x) / cellSize;

    // Matrices para el estado de visitado y los nodos previos
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::vector<std::vector<Vector2>> previous(rows, std::vector<Vector2>(cols, {-1, -1}));

    std::queue<std::pair<int, int>> queue; // Cola para el BFS
    queue.push({startRow, startCol});
    visited[startRow][startCol] = true;

    std::vector<Vector2> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // Direcciones (arriba, abajo, derecha, izquierda)

    bool pathFound = false;

    while (!queue.empty() && !pathFound) {
        auto current = queue.front();
        queue.pop();

        int currentRow = current.first;
        int currentCol = current.second;

        if (currentRow == targetRow && currentCol == targetCol) {
            pathFound = true;
            break;
        }

        for (auto& dir : directions) {
            int newRow = currentRow + dir.y;
            int newCol = currentCol + dir.x;

            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                matrizAdyacencia[newRow][newCol] != 1 && !visited[newRow][newCol]) {
                visited[newRow][newCol] = true;
                previous[newRow][newCol] = Vector2{static_cast<float>(currentRow), static_cast<float>(currentCol)};
                queue.push({newRow, newCol});
            }
        }
    }

    // Reconstruir la ruta desde `previous`
    std::vector<Vector2> path;
    Vector2 pathNode = {static_cast<float>(targetRow), static_cast<float>(targetCol)};

    while (pathNode.x != -1 && pathNode.y != -1 && pathNode != Vector2{static_cast<float>(startRow), static_cast<float>(startCol)}) {
        path.insert(path.begin(), {pathNode.y * cellSize + cellSize / 2, pathNode.x * cellSize + cellSize / 2});
        pathNode = previous[static_cast<int>(pathNode.x)][static_cast<int>(pathNode.y)];
    }

    // Si la ruta existe, moverse a la primera posición de la ruta
    if (!path.empty()) {
        position = path[0];  // Mover a la siguiente posición en el camino
    }
}
