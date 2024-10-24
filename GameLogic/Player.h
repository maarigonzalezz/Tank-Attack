#ifndef PLAYER_H
#define PLAYER_H
#include "../Tanks/ACTank.h"
#include "../Tanks/RATank.h"

using namespace std;
class Player {
public:
    Tank1* tanques[4];  // Punteros a tanques
    int id;

    // Constructor de Player que inicializa los tanques
    Player(Vector2 pos1, Vector2 pos2, Vector2 pos3, Vector2 pos4, float rot, Texture2D color1, Texture2D color2, const std::vector<std::vector<int>>& adjMatrix, int cellSize, int iD)
    : id(iD)  // Inicialización del ID
    {
        // Asignar dinámicamente los tanques al array de punteros
        tanques[0] = new ACTank(IsCellFree(pos1, adjMatrix, cellSize) ? pos1 : FindNearestFreeCell(pos1, adjMatrix, cellSize), rot, color2);
        tanques[1] = new ACTank(IsCellFree(pos2, adjMatrix, cellSize) ? pos2 : FindNearestFreeCell(pos2, adjMatrix, cellSize), rot, color2);
        tanques[2] = new RATank(IsCellFree(pos3, adjMatrix, cellSize) ? pos3 : FindNearestFreeCell(pos3, adjMatrix, cellSize), rot, color1);
        tanques[3] = new RATank(IsCellFree(pos4, adjMatrix, cellSize) ? pos4 : FindNearestFreeCell(pos4, adjMatrix, cellSize), rot, color1);
    }

    // Función para acceder a un tanque por índice
    Tank1* getTank(int index) {
        return tanques[index]; // Retorna el tanque en la posición index
    }

    bool IsCellFree(Vector2 position, const std::vector<std::vector<int>>& adjMatrix, int cellSize);
    Vector2 FindNearestFreeCell(Vector2 position, const std::vector<std::vector<int>>& adjMatrix, int cellSize);
    bool MoveTank(int index, Vector2 target);

    // Destructor para liberar memoria
    ~Player() {
        for (int i = 0; i < 4; i++) {
            delete tanques[i];
        }
    }
};




#endif //PLAYER_H

