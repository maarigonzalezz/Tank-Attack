//
// Created by maarigonzalezz on 10/10/24.
//

#include "ACTank.h"


void ACTank::movement(Vector2 targetPosition, const std::vector<std::vector<int>>& adjMatrix, int cellSize) {
    // 50% de probabilidad
    int decision = probN();
    cout << "d ACTANK: " << decision << endl;
    if (decision % 2 == 0) {
        // Implementar la lógica de BFS
        cout << "BFS" << endl;

        // Aquí puedes llamar a una función que implemente el algoritmo BFS
        BFS(this->position ,targetPosition, adjMatrix, cellSize);
    } else {
        cout << "Movimiento aleatorio" << endl;
    }
}

// Asegúrate de implementar este método en la clase ACTank para el movimiento BFS
void ACTank::BFS(Vector2 start, Vector2 goal, const std::vector<std::vector<int>>& adjMatrix, int cellsize) {
    // Lógica para implementar el algoritmo BFS para mover el tanque hacia targetPosition
    // Esta lógica debería utilizar la matriz de adyacencia para determinar el camino
}
