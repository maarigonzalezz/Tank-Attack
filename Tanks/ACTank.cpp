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
        BFS(targetPosition, adjMatrix, cellSize);
    } else {
        cout << "Movimiento aleatorio" << endl;
        LineaVista(targetPosition, adjMatrix);
    }
}

