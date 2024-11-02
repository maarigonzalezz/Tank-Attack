//
// Created by maarigonzalezz on 23/10/24.
//

#include "Algorithms.h"

std::vector<Vector2> BFS(const std::vector<std::vector<int>>& MatrizAdy, int startRow, int startCol, int targetRow, int targetCol) {
    if (startRow < 0 || startCol < 0 || targetRow < 0 || targetCol < 0 ||
        startRow >= MatrizAdy.size() || targetRow >= MatrizAdy.size() || startCol >= MatrizAdy[0].size() || targetCol >= MatrizAdy[0].size()) {
        return {}; // Verificación de índices válidos
        }

    int numRows = MatrizAdy.size();
    int numCols = MatrizAdy[0].size();
    std::vector<std::vector<bool>> visited(numRows, std::vector<bool>(numCols, false));
    std::vector<std::vector<Vector2>> previous(numRows, std::vector<Vector2>(numCols, {-1, -1}));
    std::queue<Vector2> queue;

    queue.push({(float)startRow, (float)startCol});
    visited[startRow][startCol] = true;

    std::vector<Vector2> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Arriba, Derecha, Abajo, Izquierda

    while (!queue.empty()) {
        Vector2 current = queue.front();
        queue.pop();

        if ((int)current.x == targetRow && (int)current.y == targetCol) {
            std::vector<Vector2> path;
            for (Vector2 at = {(float)targetRow, (float)targetCol}; at.x != -1; at = previous[(int)at.x][(int)at.y]) {
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const Vector2& dir : directions) {
            int newRow = (int)current.x + (int)dir.x;
            int newCol = (int)current.y + (int)dir.y;
            if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols &&
                !visited[newRow][newCol] && MatrizAdy[newRow][newCol] == 0) { // 0 indica camino libre
                queue.push({(float)newRow, (float)newCol});
                visited[newRow][newCol] = true;
                previous[newRow][newCol] = current;
                }
        }
    }

    return {}; // No se encontró camino
}

struct DijkstraNode {
    Vector2 position;
    int distance;

    bool operator<(const DijkstraNode& other) const {
        return distance > other.distance; // Menor distancia tiene prioridad
    }
};

std::vector<Vector2> Dijkstra(const std::vector<std::vector<int>>& MatrizAdy, int startRow, int startCol, int targetRow, int targetCol) {
    // Verificar límites de entrada
    if (startRow < 0 || startCol < 0 || targetRow < 0 || targetCol < 0 ||
        startRow >= MatrizAdy.size() || targetRow >= MatrizAdy.size() || startCol >= MatrizAdy[0].size() || targetCol >= MatrizAdy[0].size()) {
        return {};
    }

    int numRows = MatrizAdy.size();
    int numCols = MatrizAdy[0].size();

    // Inicialización de matrices de distancia y predecesores
    std::vector<std::vector<int>> distance(numRows, std::vector<int>(numCols, std::numeric_limits<int>::max()));
    std::vector<std::vector<Vector2>> previous(numRows, std::vector<Vector2>(numCols, {-1, -1}));
    std::vector<std::vector<bool>> visited(numRows, std::vector<bool>(numCols, false));
    std::priority_queue<DijkstraNode> queue;

    // Punto inicial
    distance[startRow][startCol] = 0;
    queue.push({{(float)startRow, (float)startCol}, 0});

    // Direcciones de movimiento: Arriba, Derecha, Abajo, Izquierda
    std::vector<Vector2> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    // Algoritmo principal
    while (!queue.empty()) {
        DijkstraNode current = queue.top();
        queue.pop();

        int currRow = (int)current.position.x;
        int currCol = (int)current.position.y;

        // Si llegamos al destino, reconstruir el camino
        if (currRow == targetRow && currCol == targetCol) {
            std::vector<Vector2> path;
            for (Vector2 at = {(float)targetRow, (float)targetCol}; at.x != -1 && at.y != -1; at = previous[(int)at.x][(int)at.y]) {
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        // Evitar re-expansión de nodos ya visitados
        if (visited[currRow][currCol]) continue;
        visited[currRow][currCol] = true;

        // Expandir vecinos
        for (const Vector2& dir : directions) {
            int newRow = currRow + (int)dir.x;
            int newCol = currCol + (int)dir.y;

            // Validar límites y accesibilidad de la celda
            if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols && MatrizAdy[newRow][newCol] == 0) {
                int newDist = distance[currRow][currCol] + 1; // Suponiendo costo de 1 para cada paso
                if (newDist < distance[newRow][newCol]) {
                    distance[newRow][newCol] = newDist;
                    previous[newRow][newCol] = { (float)currRow, (float)currCol };
                    queue.push({{(float)newRow, (float)newCol}, newDist});
                }
            }
        }
    }

    return {}; // No se encontró camino
}

