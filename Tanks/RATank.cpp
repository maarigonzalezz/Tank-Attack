
#include "RATank.h"
void RATank::movement(Vector2 targetPosition, const std::vector<std::vector<int>>& adjMatrix, int cellSize) {
    // 80% de probabilidad de seguir un movimiento "Dijkstra"
    int decision = probN();
    cout << decision<< endl;
    if (decision < 80) {
        cout << "Dijkstra" << endl;
        // Aquí puedes llamar a una función que implemente el algoritmo Dijkstra
        Dijkstra(targetPosition, adjMatrix, cellSize);
    } else {
        cout << "Movimiento aleatorio" << endl;
    }
}

