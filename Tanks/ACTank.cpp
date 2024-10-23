//
// Created by maarigonzalezz on 10/10/24.
//

#include "ACTank.h"


void ACTank::movement(Vector2 targetPosition, const std::vector<std::vector<int>>& adjMatrix, int cellSize) {
    // 50% de probabilidad
    int decision = probN();
    cout << "d: " << decision << endl;
    if (decision % 2 == 0) {
        // Implementar la lógica de BFS
        cout << "BFS" << endl;

        // Aquí puedes llamar a una función que implemente el algoritmo BFS
        BFS(this->position ,targetPosition, adjMatrix, cellSize);
    } else {
        cout << "Movimiento aleatorio" << endl;

        // Usar el método de la clase padre para movimiento aleatorio
        Vector2 nextCell = GetRandomAdjacentCell(position, adjMatrix);

        // Mover el tanque a la nueva celda
        if (nextCell.x != -1 && nextCell.y != -1) { // Verifica si hay una celda válida
            position = nextCell; // Actualizar la posición del tanque
        }
    }
}

// Asegúrate de implementar este método en la clase ACTank para el movimiento BFS
void ACTank::BFS(Vector2 start, Vector2 goal, const std::vector<std::vector<int>>& adjMatrix, int cellsize) {
    // Lógica para implementar el algoritmo BFS para mover el tanque hacia targetPosition
    // Esta lógica debería utilizar la matriz de adyacencia para determinar el camino
}
