#ifndef BULLET_H
#define BULLET_H
#include "Tank.h"
#include <vector>
#include "../GameLogic/Obstacle.h"


class Bullet {

public:
    Bullet( Vector2 pos, Vector2 vel, bool act): position(pos), velocity(vel), active(act){}
    Vector2 position;
    Vector2 velocity;
    bool active;
    Tank1* shooter = nullptr; // Referencia al tanque que disparó la bala
    const float bulletSpeed = 400.0f;

    void FireBullet(Tank1 &tank);
    void BounceBullet( const Obstacle &obstacle);
    bool CheckCollisionBulletTank( const Tank1 &tank);

};



#endif //BULLET_H
