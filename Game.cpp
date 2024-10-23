#include "Game.h"
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

    //Jugadores
    Player player1({100, 300}, {100, 350}, {100, 400}, {100, 450}, 0.0f, RED, BLUE, matrizAdyacencia, cellSize, 0);
    Player player2({600, 300}, {600, 350}, {600, 400}, {600, 450}, 180.0f, YELLOW, SKYBLUE, matrizAdyacencia, cellSize, 0);

    Player* currentPlayerTanks = &player1;
    Player* nextPlayerTanks = &player2;
    int currentPlayerIndex = player1.id;
    int nextPlayerIndex = player2.id;


    // Definir un obstáculo
    Image image2 = LoadImage("/home/maarigonzalezz/Escritorio/Tank-Attack/Images/obstacle.png"); // Cargar la imagen
    Texture2D texture2 = LoadTextureFromImage(image2); // Convertir a textura
    if (texture2.id == 0) {
        printf("Error al cargar la textura\n");
        CloseWindow();
    }
    UnloadImage(image2); // Liberar la imagen de la memoria

    // Definir background
    Image imagebg = LoadImage("/home/maarigonzalezz/Escritorio/Tank-Attack/Images/grasss2.png"); // Cargar la imagen
    Texture2D texturebg = LoadTextureFromImage(imagebg); // Convertir a textura
    if (texturebg.id == 0) {
        printf("Error al cargar la textura\n");
        CloseWindow();
    }
    UnloadImage(imagebg); // Liberar la imagen de la memoria

    float timeRemaining = matchDuration;
    float turnTime = 5.0f; // Duración de cada turno
    float turnTimer = turnTime;
    int currentPlayer = 1; // Comienza con el jugador 1
    bool isMoving = false; // Controla si un tanque está en movimiento
    bool turnComplete = false; // Controla si el turno terminó
    Vector2 moveTarget = {0, 0}; // Destino de movimiento
    float remainingDistance = maxMoveDistance; // Distancia restante para mover el tanque

    SetTargetFPS(60);
    // Bucle principal
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        timeRemaining -= deltaTime;
        turnTimer -= deltaTime;

        if (timeRemaining <= 0) {
            timeRemaining = 0;
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Fin de la partida", screenWidth / 2 - 100, screenHeight / 2 - 20, 40, RED);
            EndDrawing();
            continue;
        }

        if(turnTimer <= 0){
            turnComplete = false;
            Player* temp = currentPlayerTanks;
            currentPlayerTanks = nextPlayerTanks;
            nextPlayerTanks = temp;
            int tempIndex = currentPlayerIndex;
            currentPlayerIndex = nextPlayerIndex;
            turnTimer = turnTime;
        }


        Vector2 mousePosition = GetMousePosition();
        // Revisar si se hace clic sobre un tanque para seleccionarlo
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !isMoving && !turnComplete) {
            cout << "click"<< endl;
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

        BeginDrawing();
        ClearBackground(WHITE);
        // Dibujar el mapa
        DrawMap(matrizAdyacencia, cellSize, texture2, texturebg);

        DrawText(TextFormat("Tiempo restante: %.0f segundos", timeRemaining), 10, 40, 20, WHITE);
        // Mostrar de quién es el turno y el tanque seleccionado
        if (currentPlayerTanks == &player1) {
            DrawText(TextFormat("Turno del Jugador 1 - Tanque %d", currentPlayerIndex), 10, 10, 20, BLUE);
        } else {
            DrawText(TextFormat("Turno del Jugador 2 - Tanque %d", currentPlayerIndex), 10, 10, 20, RED);
        }
        DrawText(TextFormat("Tiempo del turno: %.1f segundos", turnTimer), 10, 100, 20, WHITE);

        for (int i = 0; i < 4; i++) {
            player1.tanques[i]->DrawTank();
            player2.tanques[i]->DrawTank();
        }


        EndDrawing();
    }

    // Cerrar la ventana
    CloseWindow();
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

bool Game::CheckCollisionBulletObstacles(Bullet bullet, std::vector<Obstacle> vector1) {
    for (const auto &obstacle : obstacles) {
        if (CheckCollisionCircleRec(bullet.position,BulletRadius, obstacle.rect)) {

            return true;  // Colisión detectada
        }
    }
    return false;  // No hay colisiones
}

void Game::DrawObstacle(const Obstacle& obstacle) {
    // Verifica que la textura se haya cargado correctamente antes de dibujar
    if (obstacle.obs.id != 0) {
        Rectangle source = { 0.0f, 0.0f, (float)obstacle.obs.width, (float)obstacle.obs.height };
        Rectangle dest = { obstacle.rect.x, obstacle.rect.y, obstacle.rect.width, obstacle.rect.height };
        Vector2 origin = { 0.0f, 0.0f };
        DrawTexturePro(obstacle.obs, source, dest, origin, 0.0f, WHITE);
    } else {
        DrawRectangleRec(obstacle.rect, obstacle.color);
        std::cout << "Textura no válida" << std::endl;
    }
}

bool Game::CheckCollisionBulletTank(const Bullet &bullet, const Tank &tank) {
    if (!tank.active || bullet.shooter == &tank) return false; // No colisionar con tanques inactivos o el tanque que disparó
    return CheckCollisionPointCircle(bullet.position, tank.position, 15); // Asumimos un radio de 15 para el tanque
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

int Game::SelectTankByClick(Player* player, int numTanks, Vector2 mousePosition) {
    for (int i = 0; i < numTanks; i++) {
        if (CheckCollisionPointCircle(mousePosition, player->tanques[i]->position, 15)) {
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



void Game::DrawMap(const std::vector<std::vector<int>>& adjMatrix, int cellSize, Texture2D texture2, Texture2D texturebg) {
    int rows = adjMatrix.size();
    int cols = adjMatrix[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (adjMatrix[i][j] == 1) {
                // Crear un obstáculo en la celda actual
                Obstacle obstacle = {
                    {static_cast<float>(j * cellSize), static_cast<float>(i * cellSize), static_cast<float>(cellSize), static_cast<float>(cellSize)}, // Inicializar rect
                    DARKGRAY, // Color
                    texture2  // Textura
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