
#ifndef RATANK_H
#define RATANK_H
#include <iostream>
#include <random>

using namespace std;
class RATank {
private:
    int probN();
public:
    int vida= 1;
    RATank() = default;
    void movement();
};




#endif //RATANK_H
