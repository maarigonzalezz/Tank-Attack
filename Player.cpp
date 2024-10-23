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
    int col = position.x / cellSize;
    int row = position.y / cellSize;

    // Empezar desde la celda actual y buscar hacia afuera en un radio creciente
    for (int radius = 1; radius < std::max(adjMatrix.size(), adjMatrix[0].size()); radius++) {
        for (int dx = -radius; dx <= radius; dx++) {
            for (int dy = -radius; dy <= radius; dy++) {
                int newCol = col + dx;
                int newRow = row + dy;

                if (newRow >= 0 && newRow < adjMatrix.size() &&
                    newCol >= 0 && newCol < adjMatrix[0].size() &&
                    adjMatrix[newRow][newCol] == 0) {
                    // Si encontramos una celda libre, devolvemos la nueva posición
                    return Vector2{static_cast<float>(newCol * cellSize), static_cast<float>(newRow * cellSize)};
                    }
            }
        }
    }

    return position;  // Si no se encuentra una celda libre, devolver la posición original
}

bool Player::MoveTank(int index, Vector2 target) {

}
