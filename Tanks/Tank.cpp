//
// Created by maarigonzalezz on 21/10/24.
//

#include "Tank.h"

int probN() {
    std::random_device rd;
    std::mt19937 gen(rd()); // Generador de números aleatorios
    std::uniform_int_distribution<> dis(0, 99);
    return  dis(gen);
}

void DrawTank(const Tank &tank) {
    if (!tank.active) return; // No dibujar tanques destruidos
    DrawRectanglePro({tank.position.x, tank.position.y, 50, 30}, {25, 15}, tank.rotation, tank.color);
    DrawCircleV(tank.position, 15, DARKGRAY);
    Vector2 cannonEnd = {
        tank.position.x + cos(tank.rotation * DEG2RAD) * 35,
        tank.position.y + sin(tank.rotation * DEG2RAD) * 35
};
    DrawLineEx(tank.position, cannonEnd, 5, BLACK);
}

int SelectTankByClick(Tank* tanks, int numTanks, Vector2 mousePosition) {
    for (int i = 0; i < numTanks; i++) {
        if (CheckCollisionPointCircle(mousePosition, tanks[i].position, 15)) {
            return i; // Retorna el índice del tanque seleccionado
        }
    }
    return -1; // No se seleccionó ningún tanque
}

int Restlife(Tank &tank) {  // Pasar tank por referencia
    int one = 0;
    if (ColorToInt(tank.color) == ColorToInt(RED) || ColorToInt(tank.color) == ColorToInt(YELLOW)) {
        tank.vida -= 50;
        if (tank.vida <= 0) {
            tank.active = false;
            cout << "se murio amarillo/rojo" << endl;
            one += 1;
        }
    } else {
        tank.vida -= 25;
        if (tank.vida <= 0) {
            tank.active = false;
            one += 1;
        }
    }
    return one;
}

bool RAmovement(Tank &tank, Vector2 targetPosition, float deltaTime, const vector<vector<int>>& matrizAdyacencia, const std::vector<Obstacle>& obstacles) {
    int startRow = static_cast<int>(tank.position.x)/50;
    int startCol = static_cast<int>(tank.position.y)/50;
    int targetRow = static_cast<int>(targetPosition.x)/50;
    int targetCol = static_cast<int>(targetPosition.y)/50;

    cout << startRow << "     " << startCol << "      " << targetRow <<"    " << targetCol << endl;

    int decision = probN();
    cout << decision << endl;

    vector<Vector2> path;

    if (decision < 80) {
        cout << "Dijkstra" << endl;
        path = Dijkstra(matrizAdyacencia, startRow, startCol, targetRow, targetCol);
        cout << "retorna path dijkstra" << endl;
        // Mueve el tanque a lo largo del camino
        if (!path.empty()) {
            cout << "SI HAY  path Dijkstra" << endl;
            MoveTankAlongPath(tank, path, deltaTime);
            return true;  // Movimiento completado usando Dijkstra
        }
        cout << "NO HAY PATH:(((" << endl;
        return false;  // No hay camino disponible
    }

    // Movimiento aleatorio
    cout << "Movimiento aleatorio" << endl;
    Vector2 direction = Vector2Subtract(targetPosition, tank.position);
    float distance = Vector2Length(direction);

    if (distance > 1.0f) {
        Vector2 moveDirection = Vector2Normalize(direction);
        float moveAmount = fmin(distance, 200 * deltaTime);
        Vector2 newPosition = Vector2Add(tank.position, Vector2Scale(moveDirection, moveAmount));

        // Verificar colisión con el obstáculo
        Tank tempTank = tank;
        tempTank.position = newPosition;
        if (!CheckCollisionTankObstacle(tempTank, obstacles)) {
            tank.position = newPosition;
            tank.rotation = atan2(direction.y, direction.x) * RAD2DEG;
            return true;  // Movimiento aleatorio completado
        }
    }
    return false;  // Movimiento no fue posible
}

bool ACmovement(Tank &tank, Vector2 targetPosition, float deltaTime, const vector<vector<int>>& matrizAdyacencia, const std::vector<Obstacle>& obstacles) {
    int startRow = static_cast<int>(tank.position.x)/50;
    int startCol = static_cast<int>(tank.position.y)/50;
    int targetRow = static_cast<int>(targetPosition.x)/50;
    int targetCol = static_cast<int>(targetPosition.y)/50;

    int decision = probN();
    cout << "d ACTANK: " << decision << endl;

    vector<Vector2> path;

    if (decision % 2 == 0) {
        cout << "BFS" << endl;
        path = BFS(matrizAdyacencia, startRow, startCol, targetRow, targetCol);

        cout << "retorna path BFS" << endl;
        // Mueve el tanque a lo largo del camino
        if (!path.empty()) {
            cout << "SI HAY  path BFS" << endl;
            MoveTankAlongPath(tank, path, deltaTime);
            return true;  // Movimiento completado usando BFS
        }
        return false;  // No hay camino disponible
    }

    // Movimiento aleatorio
    cout << "Movimiento aleatorio" << endl;
    Vector2 direction = Vector2Subtract(targetPosition, tank.position);
    float distance = Vector2Length(direction);

    if (distance > 1.0f) {
        Vector2 moveDirection = Vector2Normalize(direction);
        float moveAmount = fmin(distance, 200 * deltaTime);
        Vector2 newPosition = Vector2Add(tank.position, Vector2Scale(moveDirection, moveAmount));

        // Verificar colisión con el obstáculo
        Tank tempTank = tank;
        tempTank.position = newPosition;
        if (!CheckCollisionTankObstacle(tempTank, obstacles)) {
            tank.position = newPosition;
            tank.rotation = atan2(direction.y, direction.x) * RAD2DEG;
            return true;  // Movimiento aleatorio completado
        }
    }
    return false;  // Movimiento no fue posible
}

void MoveTankAlongPath(Tank &tank, const vector<Vector2>& path, float deltaTime) {
    if (path.empty()) return; // Si el camino está vacío, no hay nada que hacer

    // Recorrer el camino y mover el tanque hacia cada posición
    for (const Vector2& targetPosition : path) {
        // Calcular la dirección hacia la posición objetivo
        Vector2 direction = Vector2Subtract(targetPosition, tank.position);

        // Normalizar la dirección
        float distance = Vector2Length(direction);
        if (distance > 0) {
            direction = Vector2Scale(direction, 1.0f / distance); // Normalizar

            // Mover el tanque en la dirección del objetivo
            // Aquí puedes definir una velocidad de movimiento (puedes ajustarla según sea necesario)
            float speed = 100.0f * deltaTime; // Suponiendo que tienes un deltaTime
            tank.position = Vector2Add(tank.position, Vector2Scale(direction, speed));

            // Verificar si el tanque ha llegado a la posición objetivo
            if (Vector2Distance(tank.position, targetPosition) < speed) {
                // Si ha llegado, ajustar la posición del tanque a la posición objetivo
                tank.position = targetPosition;
            }
        }
    }
}

bool CheckCollisionTankObstacle(const Tank &tank, const std::vector<Obstacle>& obstacles) {
    for (const auto &obstacle : obstacles) {
        // Verificar colisión del círculo (tanque con radio) con cada obstáculo (rectángulo)
        if (CheckCollisionCircleRec(tank.position, 15, obstacle.rect)) {
            return true;  // Colisión detectada
        }
    }
    return false;  // No hay colisiones
}


