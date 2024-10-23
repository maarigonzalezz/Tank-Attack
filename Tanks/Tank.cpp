//
// Created by maarigonzalezz on 21/10/24.
//

#include "Tank.h"
void Tank1::DrawTank() {
    if (!this->active) return; // No dibujar tanques destruidos
    DrawRectanglePro({this->position.x, this->position.y, 50, 30}, {25, 15}, this->rotation, this->color);
    DrawCircleV(this->position, 15, DARKGRAY);
    Vector2 cannonEnd = {
        this->position.x + cos(this->rotation * DEG2RAD) * 35,
        this->position.y + sin(this->rotation * DEG2RAD) * 35
};
    DrawLineEx(this->position, cannonEnd, 5, BLACK);
}
bool Tank1::IsMouseOver(Vector2 mousePosition) {
    // Suponiendo que el tanque es un rectángulo
    return (mousePosition.x >= position.x && mousePosition.x <= position.x + width &&
            mousePosition.y >= position.y && mousePosition.y <= position.y + height);
}