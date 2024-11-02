#include "Game.h"
#include <array>
#include "raylib.h"

std::vector<Obstacle> obstacles;


void Game::sGame(bool a) {
    InitWindow(screenWidth, screenHeight, "Tank Attack!");
    // Crear grafo
    Graph mapGraph(numRows, numCols);
    mapGraph.generateRandomObstacles(numObstacles);
    // Generar la matriz de adyacencia
    vector<vector<int>> matrizAdyacencia = mapGraph.generateAdjacencyMatrix();
    mapGraph.printAdjacencyMatrix(matrizAdyacencia);

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (mapGraph.isObstacle(i, j)) {
                // Crear un obstáculo en la celda actual
                Obstacle obstacle = {{j * cellSize, i * cellSize, cellSize, cellSize}, DARKGRAY};
                obstacles.push_back(obstacle); // Añadir el obstáculo a la lista
            }
        }
    }

    /* -----------------------------------------IMAGENES---------------------------------------------------- */
    // Definir un obstáculo
    Image image2 = LoadImage("/home/maarigonzalezz/Escritorio/Tank-Attack/Images/obstacle.png"); // Cargar la imagen
    Texture2D texture2 = LoadTextureFromImage(image2); // Convertir a textura
    if (texture2.id == 0) {
        printf("Error al cargar la textura\n");
        CloseWindow();
    }
    UnloadImage(image2); // Liberar la imagen de la memoria

    // Definir background
    Image imagebg = LoadImage("/home/maarigonzalezz/Escritorio/Tank-Attack/Images/arena.png"); // Cargar la imagen
    Texture2D texturebg = LoadTextureFromImage(imagebg); // Convertir a textura
    UnloadImage(imagebg); // Liberar la imagen de la memoria
    /* -----------------------------------------IMAGENES---------------------------------------------------- */

    // Jugador 1 - Tanques de colores: 2 amarillos y 2 celestes
    Tank player1Tanks[numTanksPerPlayer] = {
        {{100, 300}, 0.0f, RED},
        {{100, 350}, 0.0f, RED},
        {{100, 400}, 0.0f, BLUE},
        {{100, 450}, 0.0f, BLUE}
    };

    // Jugador 2 - Tanques de colores: 2 rojos y 2 azules
    Tank player2Tanks[numTanksPerPlayer] = {
        {{600, 300}, 180.0f, YELLOW},
        {{600, 350}, 180.0f, YELLOW},
        {{600, 400}, 180.0f, SKYBLUE},
        {{600, 450}, 180.0f, SKYBLUE}
    };

    //Jugadores

    Bullet bullets[40] = {0};
    // Definir un obstáculo
    Obstacle obstacle = {{0, 0, 100, 100}, DARKGRAY};

    //int currentPlayerIndex = player1.id;
    //int nextPlayerIndex = player2.id;
    float timeRemaining = matchDuration;
    float turnTime = 10.0f; // Duración de cada turno
    float turnTimer = turnTime;
    bool tankSelected = false; // Tracks if a tank is selected
    float remainingDistance = maxMoveDistance; // Distancia restante para mover el tanque
    Tank* currentPlayerTanks = player1Tanks;
    Tank* nextPlayerTanks = player2Tanks;
    int currentPlayerIndex = 0;
    int nextPlayerIndex = 0;
    bool moveInitiated;
    int tanksP1 = 4;
    int tanksP2 = 4;


    SetTargetFPS(60);
    // Bucle principal
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        timeRemaining -= deltaTime;
        turnTimer -= deltaTime;

        if (timeRemaining <= 0) {
            timeRemaining = 0;
            string ganador;
            if (tanksP1 > tanksP2) {
                ganador = "Player 1";
            } else if (tanksP1 < tanksP2){
                ganador = "Player 2";
            } else {
                ganador = "Empate";
            }
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Fin de la partida", screenWidth / 2 - 100, screenHeight / 2 - 20, 40, RED);
            DrawText(TextFormat("Ganador: %s", ganador.c_str()), screenWidth / 2 - 100, screenHeight / 2 + 20, 40, RED);
            EndDrawing();
            continue;
        }

        if (tanksP1 < 0 || tanksP2 < 0) {
            string ganador;
            if (tanksP1 > 0) {
                ganador = "Player 1";
            } else if (0 < tanksP2){
                ganador = "Player 2";
            }
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Fin de la partida", screenWidth / 2 - 100, screenHeight / 2 - 20, 40, RED);
            DrawText(TextFormat("Ganador: %s", ganador.c_str()), screenWidth / 2 - 100, screenHeight / 2 + 20, 40, RED);
            EndDrawing();
            continue;
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
            if (!moveInitiated) {
                isMoving = MoveTankToMouse(selectedTank, moveTarget, deltaTime, matrizAdyacencia, obstacle);
                moveInitiated = true; // Marcar el movimiento como iniciado
            }

            // Verifica si el movimiento se completó en esta llamada
            if (!isMoving) {
                turnComplete = true;
                moveInitiated = false; // Reinicia para el siguiente turno
            }
        }

        // El jugador puede disparar si ha completado el movimiento y presiona la barra espaciadora
        if (!turnComplete && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && selectedTank.active) {
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
                        int life = Restlife(player1Tanks[j]);
                        tanksP1 -= life;
                        bullets[i].active = false; // Desactivar la bala
                        break;
                    }
                }

                // Verificar colisión con tanques del jugador 2
                for (int j = 0; j < numTanksPerPlayer; j++) {
                    if (CheckCollisionBulletTank(bullets[i], player2Tanks[j])) {
                        int life = Restlife(player2Tanks[j]);
                        tanksP2 -= life;
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


        //Dibujar en pantalla
        BeginDrawing();
        ClearBackground(WHITE);
        // Dibujar el mapa
        DrawMap(matrizAdyacencia, cellSize, texture2, texturebg);
        for (const Obstacle& obstacle : obstacles) {
            DrawObstacle(obstacle); // Dibujar cada obstáculo
        }

        DrawText(TextFormat("Tiempo restante: %.0f segundos", timeRemaining), 10, 40, 20, WHITE);
        // Mostrar de quién es el turno y el tanque seleccionado
        if (currentPlayerTanks == player1Tanks) {
            DrawText(TextFormat("Turno del Jugador 1 - Tanque %d", currentPlayerIndex + 1), 10, 10, 20, BLUE);
        } else {
            DrawText(TextFormat("Turno del Jugador 2 - Tanque %d", currentPlayerIndex + 1), 10, 10, 20, RED);
        }

        // Dibujar tanques de ambos jugadores
        for (int i = 0; i < numTanksPerPlayer; i++) {
            DrawTank(player1Tanks[i]);
            DrawTank(player2Tanks[i]);
        }

        // Dibujar balas
        for (int i = 0; i < 40; i++) {
            if (bullets[i].active) {
                DrawCircleV(bullets[i].position, 5, BLACK);
            }
        }

        EndDrawing();
    }

    // Cerrar la ventana
    CloseWindow();
}

void Game::DrawObstacle(const Obstacle& obstacle) {
        DrawRectangleRec(obstacle.rect, obstacle.color);
    }

bool Game::CheckCollisionBulletTank(const Bullet &bullet, const Tank &tank) {
    if (!tank.active || bullet.shooter == &tank) return false; // No colisionar con tanques inactivos o el tanque que disparó
    return CheckCollisionPointCircle(bullet.position, tank.position, 15); // Asumimos un radio de 15 para el tanque
}

bool Game::CheckCollisionTankObstacle(const Tank &tank, const std::vector<Obstacle>& obstacles) {
    for (const auto &obstacle : obstacles) {
        // Verificar colisión del círculo (tanque con radio) con cada obstáculo (rectángulo)
        if (CheckCollisionCircleRec(tank.position, tankRadius, obstacle.rect)) {
            return true;  // Colisión detectada
        }
    }
    return false;  // No hay colisiones
}

void Game::FireBullet(Bullet &bullet, Tank &tank) {
    if(tank.active){
        bullet.active = true;
        bullet.position = tank.position;
        bullet.velocity = {cos(tank.rotation * DEG2RAD) * bulletSpeed, sin(tank.rotation * DEG2RAD) * bulletSpeed};
        bullet.shooter = &tank; // Asignar el tanque que dispara la bala
    }
}

bool Game::CheckCollisionBulletObstacles(Bullet bullet, const std::vector<Obstacle>& obstacles) {
    for (const auto& obstacle : obstacles) {
        if (CheckCollisionCircleRec(bullet.position, BulletRadius, obstacle.rect)) {
            return true;  // Colisión detectada
        }
    }
    return false;  // No hay colisiones
}

bool Game::MoveTankToMouse(Tank &tank, Vector2 targetPosition, float deltaTime, const vector<vector<int>>& matrizAdyacencia, const Obstacle &obstacle) {
    bool completeMove;
    if (ColorToInt(tank.color) == ColorToInt(RED) || ColorToInt(tank.color) == ColorToInt(YELLOW)) {
        cout << "entro aqui ar?" << endl;
        // Movimiento aleatorio
        completeMove = RAmovement(tank, targetPosition, deltaTime, matrizAdyacencia, obstacles);
    } else {
        // Movimiento algorítmico
        cout << "entro aqui azc?" << endl;
        completeMove = ACmovement(tank, targetPosition, deltaTime, matrizAdyacencia, obstacles);
    }
    // Si el movimiento se ha completado, retorna false para detener isMoving
    return false;
}

void Game::DrawMap(const std::vector<std::vector<int>>& adjMatrix, int cellSize, Texture2D texture2, Texture2D texturebg) {
    int rows = adjMatrix.size();
    int cols = adjMatrix[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (adjMatrix[i][j] == 1) {
                // Crear un obstáculo en la celda actual
                Obstacle obstacle = {
                    {static_cast<float>(j * cellSize), static_cast<float>(i * cellSize), static_cast<float>(cellSize), static_cast<float>(cellSize)}, // Inicializar rect
                    DARKGRAY
                };
                obstacles.push_back(obstacle); // Añadir el obstáculo a la lista
                DrawObstacle(obstacle);
            }
            else {
                DrawTextureEx(texturebg, (Vector2){static_cast<float>(j * cellSize), static_cast<float>(i * cellSize)}, 0.0f, 1.0f, WHITE);
            }
        }
    }
}


// Menú principal
void Game::Pmenu() {
    InitWindow(screenWidthP, screenHeightP, "Tank Attack! Menú Principal");

    Image image = LoadImage("/home/maarigonzalezz/Escritorio/Tank-Attack/Images/fondo.png"); // Cargar la imagen
    if (image.data == NULL) {
        printf("Error al cargar la imagen\n");
        CloseWindow();
    }
    Texture2D texture = LoadTextureFromImage(image); // Convertir a textura
    UnloadImage(image); // Liberar la imagen de la memoria
    if (texture.id == 0) {
        printf("Error al cargar la textura\n");
        CloseWindow();
    }

    // Configuración de FPS
    SetTargetFPS(60);

    // Variables para el botón
    Rectangle button = { 830, 400, 200, 40 }; // {x, y, width, height}
    bool buttonPressed = false;

    while (!WindowShouldClose()) {
        // Detecta si se hace clic en el botón
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePos = GetMousePosition();
            if (CheckCollisionPointRec(mousePos, button)) {
                buttonPressed = true; // Cambia el estado si el botón fue presionado
            }
        }

        // Comienza a dibujar
        BeginDrawing();
        ClearBackground(RAYWHITE); // Borra el fondo con un color blanco

        // Imagen de fondo
        DrawTextureEx(texture, (Vector2){0, 0}, 0.0f, (newWidth / texture.width, newHeight / texture.height), WHITE);

        // Dibuja el botón
        DrawRectangleRec(button, ORANGE);
        DrawText("INICIAR PARTIDA", button.x + 10, button.y + 10, 20, RAYWHITE); // Texto en el botón

        // Si el botón fue presionado, muestra un mensaje
        if (buttonPressed) {
            CloseWindow();
            sGame(true);

        }
        EndDrawing();
    }

    // Unload the texture to free memory
    UnloadTexture(texture); // Libera la textura de la memoria

    // Cierra la ventana y libera los recursos
    CloseWindow();
}