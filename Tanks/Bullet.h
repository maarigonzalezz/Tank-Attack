#ifndef BULLET_H
#define BULLET_H
#include "Tank.h"
#include <vector>
#include "../GameLogic/Obstacle.h"



struct Bullet {
    Vector2 position;
    Vector2 velocity;
    bool active;
    Tank* shooter; // Referencia al tanque que disparó la bala
    float radius = 5.0f;
};

void BounceBullet(Bullet &bullet, const Obstacle &obstacle);


#endif //BULLET_H
