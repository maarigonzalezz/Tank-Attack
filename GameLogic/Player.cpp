//
// Created by fabiana on 10/10/24.
//

#include "Player.h"

bool Player::IsCellFree(Vector2 position, const std::vector<std::vector<int>>& adjMatrix, int cellSize) {
    int col = position.x / cellSize;
    int row = position.y / cellSize;

    // Verificar que esté dentro del rango de la matriz y si es una celda libre
    if (row >= 0 && row < adjMatrix.size() &&
        col >= 0 && col < adjMatrix[0].size() &&
        adjMatrix[row][col] == 0) {
        return true;
        }

    return false;
}

Vector2 Player::FindNearestFreeCell(Vector2 position, const std::vector<std::vector<int>>& adjMatrix, int cellSize) {
    int col = position.x / cellSize; // Columna en la que se encuentra
    int row = position.y / cellSize; // Fila en la que se encuentra

    // Buscar una celda libre en un radio creciente desde la posición actual
    for (int radius = 1; radius < std::max(adjMatrix.size(), adjMatrix[0].size()); radius++) {
        for (int dx = -radius; dx <= radius; dx++) {
            for (int dy = -radius; dy <= radius; dy++) {
                int newCol = col + dx;
                int newRow = row + dy;

                // Verificar si la nueva posición está dentro de los límites y es una celda libre
                if (newRow >= 0 && newRow < adjMatrix.size() &&
                    newCol >= 0 && newCol < adjMatrix[0].size() &&
                    adjMatrix[newRow][newCol] == 0) {

                    // Calcular el centro de la celda encontrada
                    float centerX = newCol * cellSize + cellSize / 2.0f;
                    float centerY = newRow * cellSize + cellSize / 2.0f;

                    // Devolver la posición en el centro de la celda libre
                    return Vector2{centerX, centerY};
                    }
            }
        }
    }

    // Si no se encuentra una celda libre, devolver la posición original
    return position;
}



