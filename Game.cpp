#include "Game.h"
#include "raylib.h"

std::vector<Obstacle> obstacles;

void Game::tGame(bool a) {
    if (a == true){
        InitWindow(screenWidth, screenHeight, "Juego de Tanques por Turnos");

    Graph mapGraph(numRows, numCols);

    mapGraph.generateRandomObstacles(numObstacles);


    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (mapGraph.isObstacle(i, j)) {
                // Crear un obstáculo en la celda actual
                Obstacle obstacle = {{j * cellSize, i * cellSize, cellSize, cellSize}, DARKGRAY};
                obstacles.push_back(obstacle); // Añadir el obstáculo a la lista
            }
        }
    }

    // Jugador 1 - Tanques de colores: 2 amarillos y 2 celestes
    Tank player1Tanks[numTanksPerPlayer] = {
            {{100, 300}, 0.0f, YELLOW},
            {{100, 350}, 0.0f, YELLOW},
            {{100, 400}, 0.0f, SKYBLUE},
            {{100, 450}, 0.0f, SKYBLUE}
    };

    // Jugador 2 - Tanques de colores: 2 rojos y 2 azules
    Tank player2Tanks[numTanksPerPlayer] = {
            {{900, 300}, 180.0f, RED},
            {{900, 350}, 180.0f, RED},
            {{900, 400}, 180.0f, BLUE},
            {{900, 450}, 180.0f, BLUE}
    };

    for (int i = 0; i < numTanksPerPlayer; i++) {
        restrictedPositions.push_back(player1Tanks[i].position);
        restrictedPositions.push_back(player2Tanks[i].position);
    }


    Tank* currentPlayerTanks = player1Tanks;
    Tank* nextPlayerTanks = player2Tanks;
    int currentPlayerIndex = 0;
    int nextPlayerIndex = 0;

    Bullet bullets[10] = {0};

    // Definir un obstáculo
    Obstacle obstacle = {{0, 0, 100, 100}, DARKGRAY};

    bool isMoving = false;
    bool turnComplete = false;
    Vector2 moveTarget = {0, 0};
    float remainingDistance = maxMoveDistance;
    float timeRemaining = matchDuration; // Inicializa el tiempo de la partida a 5 minutos

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        timeRemaining -= deltaTime;

        if (timeRemaining <= 0) {
            timeRemaining = 0; // Evitar que sea negativo
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Fin de la partida", screenWidth / 2 - 100, screenHeight / 2 - 20, 40, RED);
            EndDrawing();
            continue; // Salta al siguiente ciclo para evitar continuar el juego
        }

        Vector2 mousePosition = GetMousePosition();

        // Revisar si se hace clic sobre un tanque para seleccionarlo
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !isMoving && !turnComplete) {
            int clickedTankIndex = SelectTankByClick(currentPlayerTanks, numTanksPerPlayer, mousePosition);
            if (clickedTankIndex != -1) {
                currentPlayerIndex = clickedTankIndex; // Actualizar al tanque seleccionado
            } else {
                // Si no se selecciona un tanque, intentar mover el tanque actual
                moveTarget = mousePosition;
                remainingDistance = maxMoveDistance;
                isMoving = true;

            }
        }

        Tank& selectedTank = currentPlayerTanks[currentPlayerIndex];

        // Movimiento del tanque en su turno
        if (isMoving) {
            isMoving = MoveTankToMouse(selectedTank, moveTarget, deltaTime, obstacle);
            if (!isMoving) {
                turnComplete = true;
            }
        }

        // El jugador puede disparar si ha completado el movimiento y presiona la barra espaciadora


        if (!turnComplete && IsKeyPressed(KEY_SPACE)&&selectedTank.active) {
            for (int i = 0; i < 10; i++) {
                if (!bullets[i].active) {
                    FireBullet(bullets[i], selectedTank);
                    break;
                }
            }
            turnComplete= true;

        }
        if(turnComplete){
            turnComplete = false;
            Tank* temp = currentPlayerTanks;
            currentPlayerTanks = nextPlayerTanks;
            nextPlayerTanks = temp;
            int tempIndex = currentPlayerIndex;
            currentPlayerIndex = nextPlayerIndex;
        }


        // Actualización de balas
        for (int i = 0; i < 10; i++) {
            if (bullets[i].active) {
                bullets[i].position.x += bullets[i].velocity.x * deltaTime;
                bullets[i].position.y += bullets[i].velocity.y * deltaTime;

                // Rebotar si la bala colisiona con el obstáculo
                if (CheckCollisionBulletObstacles(bullets[i], obstacles)) {
                    for (auto& obstacle : obstacles) {
                        BounceBullet(bullets[i], obstacle);
                    }
                }

                // Verificar colisión con tanques del jugador 1
                for (int j = 0; j < numTanksPerPlayer; j++) {
                    if (CheckCollisionBulletTank(bullets[i], player1Tanks[j])) {
                        player1Tanks[j].active = false; // Desactivar el tanque
                        bullets[i].active = false; // Desactivar la bala
                        break;
                    }
                }

                // Verificar colisión con tanques del jugador 2
                for (int j = 0; j < numTanksPerPlayer; j++) {
                    if (CheckCollisionBulletTank(bullets[i], player2Tanks[j])) {
                        player2Tanks[j].active = false; // Desactivar el tanque
                        bullets[i].active = false; // Desactivar la bala
                        break;
                    }
                }

                // Desactivar balas si salen de la pantalla
                if (bullets[i].position.x < 0 || bullets[i].position.x > screenWidth || bullets[i].position.y < 0 || bullets[i].position.y > screenHeight) {
                    bullets[i].active = false;
                }
            }
        }

        // Contar tanques activos
        int yellowCount, skyBlueCount, redCount, blueCount;
        CountTanksByColor(player1Tanks, player2Tanks, yellowCount, skyBlueCount, redCount, blueCount);

        BeginDrawing();
        ClearBackground(RAYWHITE);


        for (const Obstacle& obstacle : obstacles) {
            DrawObstacle(obstacle); // Dibujar cada obstáculo
        }


        // Dibujar tanques de ambos jugadores
        for (int i = 0; i < numTanksPerPlayer; i++) {
            DrawTank(player1Tanks[i]);
            DrawTank(player2Tanks[i]);
        }

        // Dibujar obstáculo

        // Dibujar balas
        for (int i = 0; i < 10; i++) {
            if (bullets[i].active) {
                DrawCircleV(bullets[i].position, 5, BLACK);
            }
        }
        DrawText(TextFormat("Tiempo restante: %.0f segundos", timeRemaining), 10, 40, 20, DARKGREEN);

        // Mostrar de quién es el turno y el tanque seleccionado
        if (currentPlayerTanks == player1Tanks) {
            DrawText(TextFormat("Turno del Jugador 1 - Tanque %d", currentPlayerIndex + 1), 10, 10, 20, BLUE);
        } else {
            DrawText(TextFormat("Turno del Jugador 2 - Tanque %d", currentPlayerIndex + 1), 10, 10, 20, RED);
        }




        // Mostrar los contadores de tanques en la parte inferior
        DrawText(TextFormat("Tanques Amarillos: %d", yellowCount), 10, screenHeight - 60, 20, YELLOW);
        DrawText(TextFormat("Tanques Celestes: %d", skyBlueCount), 10, screenHeight - 40, 20, SKYBLUE);
        DrawText(TextFormat("Tanques Rojos: %d", redCount), screenWidth - 200, screenHeight - 60, 20, RED);
        DrawText(TextFormat("Tanques Azules: %d", blueCount), screenWidth - 200, screenHeight - 40, 20, BLUE);

        EndDrawing();
    }

    CloseWindow();
}
}

    bool Game::CheckCollisionBulletObstacles(Bullet bullet, std::vector<Obstacle> vector1) {
    for (const auto &obstacle : obstacles) {
        if (CheckCollisionCircleRec(bullet.position,BulletRadius, obstacle.rect)) {

            return true;  // Colisión detectada
        }
    }
    return false;  // No hay colisiones
}


bool Game::CheckCollisionTankObstacle(const Tank &tank, std::vector<Obstacle> vector1) {
    for (const auto &obstacle : obstacles) {
        // Verificar colisión del círculo (tanque con radio) con cada obstáculo (rectángulo)
        if (CheckCollisionCircleRec(tank.position, tankRadius, obstacle.rect)) {
            return true;  // Colisión detectada
        }
    }
    return false;  // No hay colisiones
}




bool Game::MoveTankToMouse(Tank &tank, Vector2 targetPosition, float deltaTime, const Obstacle &obstacle) {
    Vector2 direction = Vector2Subtract(targetPosition, tank.position);
    float distance = Vector2Length(direction);

    if (distance > 1.0f) {
        Vector2 moveDirection = Vector2Normalize(direction);
        float moveAmount = fmin(distance, tankSpeed * deltaTime);
        Vector2 newPosition = Vector2Add(tank.position, Vector2Scale(moveDirection, moveAmount));

        // Verificar colisión con el obstáculo
        Tank tempTank = tank;
        tempTank.position = newPosition;
        if (!CheckCollisionTankObstacle(tempTank, obstacles)) {
            tank.position = newPosition;
        }
        else{
            return false;
        }

        tank.rotation = atan2(direction.y, direction.x) * RAD2DEG;
        return true;
    }
    return false;
}

void Game::FireBullet(Bullet &bullet, Tank &tank) {
    if(tank.active){
        bullet.active = true;
        bullet.position = tank.position;
        bullet.velocity = {cos(tank.rotation * DEG2RAD) * bulletSpeed, sin(tank.rotation * DEG2RAD) * bulletSpeed};
        bullet.shooter = &tank; // Asignar el tanque que dispara la bala
    }


}

void Game::DrawTank(Tank tank) {
    if (!tank.active) return; // No dibujar tanques destruidos
    DrawRectanglePro({tank.position.x, tank.position.y, 50, 30}, {25, 15}, tank.rotation, tank.color);
    DrawCircleV(tank.position, 15, DARKGRAY);
    Vector2 cannonEnd = {
            tank.position.x + cos(tank.rotation * DEG2RAD) * 35,
            tank.position.y + sin(tank.rotation * DEG2RAD) * 35
    };
    DrawLineEx(tank.position, cannonEnd, 5, BLACK);
}




void Game::BounceBullet(Bullet &bullet, const Obstacle &obstacle) {
    // Revisar si la bala colisiona en el lado horizontal (superior/inferior) del obstáculo
    if ((bullet.position.x > obstacle.rect.x && bullet.position.x < obstacle.rect.x + obstacle.rect.width) &&
        (bullet.position.y <= obstacle.rect.y || bullet.position.y >= obstacle.rect.y + obstacle.rect.height)) {
        bullet.velocity.y *= -1;  // Invertir la dirección en el eje Y
    }
    // Revisar si la bala colisiona en el lado vertical (izquierda/derecha) del obstáculo
    if ((bullet.position.y > obstacle.rect.y && bullet.position.y < obstacle.rect.y + obstacle.rect.height) &&
        (bullet.position.x <= obstacle.rect.x || bullet.position.x >= obstacle.rect.x + obstacle.rect.width)) {
        bullet.velocity.x *= -1;  // Invertir la dirección en el eje X
    }
}

int Game::SelectTankByClick(Tank* tanks, int numTanks, Vector2 mousePosition) {
    for (int i = 0; i < numTanks; i++) {
        if (CheckCollisionPointCircle(mousePosition, tanks[i].position, 15)) {
            return i; // Retorna el índice del tanque seleccionado
        }
    }
    return -1; // No se seleccionó ningún tanque
}

bool Game::ColorsAreEqual(Color c1, Color c2) {
    return (c1.r == c2.r) && (c1.g == c2.g) && (c1.b == c2.b) && (c1.a == c2.a);
}

// Nueva función para contar tanques por color
void Game::CountTanksByColor(Tank* player1Tanks, Tank* player2Tanks, int& yellowCount, int& skyBlueCount, int& redCount, int& blueCount) {
    yellowCount = skyBlueCount = redCount = blueCount = 0;

    // Contar tanques activos de cada color en el Jugador 1
    for (int i = 0; i < numTanksPerPlayer; i++) {
        if (player1Tanks[i].active) {
            if (ColorsAreEqual(player1Tanks[i].color, YELLOW)) yellowCount++;
            else if (ColorsAreEqual(player1Tanks[i].color, SKYBLUE)) skyBlueCount++;
        }
    }
}