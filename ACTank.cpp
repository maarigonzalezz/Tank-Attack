//
// Created by maarigonzalezz on 10/10/24.
//

#include "ACTank.h"

int ACTank::probN() {
    std::random_device rd;
    std::mt19937 gen(rd()); // Generador de números aleatorios
    std::uniform_int_distribution<> dis(0, 99);
    return dis(gen);
}

void ACTank::movement() {
    //50% de probabilidad
    int decision = probN();
    if (decision % 2 == 0) {
        cout << "BFS" << endl;
    } else {
        cout << "movimiento aleatorio" << endl;
    }
}

void ACTank::initialPos(string type) {
    if (type == p1type) {
        //se coloca de lado izquierdo
    } else {
        //se coloca de lado derecho
    }
}