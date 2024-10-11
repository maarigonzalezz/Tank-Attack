
#ifndef RATANK_H
#define RATANK_H
#include <iostream>
#include <random>

using namespace std;
class RATank {
private:
    string p1type = "Rojo";
    string p2type = "Amarillo";
    int probN();
public:
    int vida= 1;
    RATank() = default;
    void movement();
    void initialPos(string type);
};




#endif //RATANK_H
