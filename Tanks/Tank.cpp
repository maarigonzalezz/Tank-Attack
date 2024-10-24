//
// Created by maarigonzalezz on 21/10/24.
//

#include "Tank.h"

Tank1::Tank1(Vector2 pos, float rot, Texture2D col) : position(pos), rotation(rot), color(col) {}

void Tank1::DrawTank() {
    if (!this->active) return; // No dibujar tanques destruidos
    // Definir las proporciones del rectángulo de la textura
    Rectangle sourceRect = { 0, 0, static_cast<float>(this->color.width), static_cast<float>(this->color.height) }; // Rectángulo de la imagen completa
    Rectangle destRect = { this->position.x, this->position.y, 50, 40 }; // Rectángulo de destino para dibujar el tanque (ajusta según el tamaño del tanque)
    Vector2 origin = { 25, 15 }; // Centro del tanque (ajústalo si es necesario)

    // Dibujar la textura del tanque con rotación
    DrawTexturePro(
        this->color,    // Textura a dibujar
        sourceRect,           // La porción de la textura que se va a dibujar
        destRect,             // Donde se dibujará en la pantalla
        origin,               // Punto de origen para la rotación
        this->rotation,       // Rotación en grados
        WHITE                 // Color de tinte (puedes usar WHITE para no alterar la textura)
    );
}

bool Tank1::IsMouseOver(Vector2 mousePosition) {
    // Suponiendo que el tanque es un rectángulo
    return (mousePosition.x >= position.x && mousePosition.x <= position.x + width &&
            mousePosition.y >= position.y && mousePosition.y <= position.y + height);
}

 int Tank1::probN() {
    std::random_device rd;
    std::mt19937 gen(rd()); // Generador de números aleatorios
    std::uniform_int_distribution<> dis(0, 99);
    return  dis(gen);
}

bool Tank1::IsCellFree(Vector2 position, const std::vector<std::vector<int>>& adjMatrix, int cellSize) {
    // Determina si la celda está libre basada en la matriz de adyacencia
    int cellX = position.x / cellSize;
    int cellY = position.y / cellSize;
    return adjMatrix[cellY][cellX] == 0; // Asumiendo 0 es libre
}

