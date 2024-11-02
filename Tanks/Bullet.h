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
    float speed = 300.0f;
};

void BounceBullet(Bullet &bullet, const Obstacle &obstacle);
void FireBullet(Bullet &bullet, const Tank &selectedTank);
Vector2 CalculateDirection(Vector2 start, Vector2 target);


#endif //BULLET_H
