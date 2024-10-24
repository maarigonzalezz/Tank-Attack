
#include "RATank.h"
void RATank::movement(Vector2 targetPosition, const std::vector<std::vector<int>>& adjMatrix, int cellSize) {
    // 80% de probabilidad de seguir un movimiento "Dijkstra"
    int decision = probN();
    cout << decision<< endl;
    if (decision < 80) {
        // Implementar la lógica de Dijkstra
        cout << "Dijkstra" << endl;

        // Aquí puedes llamar a una función que implemente el algoritmo Dijkstra
        // y mueva el tanque hacia targetPosition utilizando la matriz de adyacencia
        std::vector<Vector2> path = Dijkstra(this->position, targetPosition, adjMatrix, cellSize);
    } else {
        cout << "Movimiento aleatorio" << endl;
    }
}

struct Node {
    Vector2 position;  // La posición del nodo
    float cost;        // El costo para llegar a este nodo

    // Sobrecarga del operador < para usar en la cola de prioridad
    bool operator>(const Node& other) const {
        return cost > other.cost; // Comparar costos para la cola de prioridad
    }
};

const float INF = std::numeric_limits<float>::infinity();

std::vector<Vector2> RATank::Dijkstra(Vector2 start, Vector2 goal, const std::vector<std::vector<int>>& adjMatrix, int cellSize) {
    int rows = adjMatrix.size();
    int cols = adjMatrix[0].size();

    // Arreglos para almacenar costos y caminos
    std::vector<std::vector<float>> costs(rows, std::vector<float>(cols, INF));
    std::vector<std::vector<Vector2>> cameFrom(rows, std::vector<Vector2>(cols, {-1, -1}));
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;

    // Inicializar el costo de la celda de inicio
    costs[start.y][start.x] = 0;
    openSet.push({start, 0});

    // Definir los movimientos posibles (arriba, abajo, izquierda, derecha)
    std::vector<Vector2> directions = {
        {0, -1}, // Arriba
        {0, 1},  // Abajo
        {-1, 0}, // Izquierda
        {1, 0}    // Derecha
    };

    while (!openSet.empty()) {
        Vector2 current = openSet.top().position;
        openSet.pop();

        // Si hemos llegado al objetivo, reconstruir el camino
        if (current.x == goal.x && current.y == goal.y) {
            std::vector<Vector2> path;
            for (Vector2 at = goal; at.x != -1 && at.y != -1; at = cameFrom[at.y][at.x]) {
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end());
            return path; // Retorna el camino más corto
        }

        // Explorar las celdas adyacentes
        for (const Vector2& dir : directions) {
            Vector2 neighbor = {current.x + dir.x, current.y + dir.y};

            // Verifica si el vecino está dentro de los límites y es una celda libre
            if (neighbor.x >= 0 && neighbor.x < cols &&
                neighbor.y >= 0 && neighbor.y < rows &&
                adjMatrix[neighbor.y][neighbor.x] == 0) { // 0 indica celda libre

                float newCost = costs[current.y][current.x] + 1; // Suponiendo que cada movimiento tiene un costo de 1

                // Si no hemos visto este vecino o encontramos un camino más corto
                if (newCost < costs[neighbor.y][neighbor.x]) {
                    costs[neighbor.y][neighbor.x] = newCost;
                    cameFrom[neighbor.y][neighbor.x] = current;
                    openSet.push({neighbor, newCost});
                }
            }
        }
    }

    return {}; // Retorna un vector vacío si no se encuentra un camino
}