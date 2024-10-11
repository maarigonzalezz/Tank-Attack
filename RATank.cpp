

#include "RATank.h"


int RATank::probN() {
    std::random_device rd;
    std::mt19937 gen(rd()); // Generador de números aleatorios
    std::uniform_int_distribution<> dis(0, 99);
    return  dis(gen);
}

void RATank::movement() {
    //80% de probabilidad
    int decision = probN();
    if (decision < 80) {
        cout << "Dijkstra" << endl;
    } else {
        cout << "movimiento aleatorio" << endl;
    }
}