#ifndef ACTANK_H
#define ACTANK_H
#include <iostream>
#include <random>
#include <string>

using namespace std;
class ACTank {
private:
    string p1type = "Azul";
    string p2type = "Celeste";

    int probN();
public:
    int vida= 1;
    ACTank() = default;

    void movement();
    void initialPos(string type);

};



#endif //ACTANK_H