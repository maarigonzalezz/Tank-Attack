#ifndef ACTANK_H
#define ACTANK_H
#include <iostream>
#include <random>
#include <string>

using namespace std;
class ACTank {
private:
    string typeAzul = "Azul";
    int probN();
public:
    int vida= 1;
    ACTank() = default;

    void movement();

};



#endif //ACTANK_H
