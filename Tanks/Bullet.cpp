

#include "Bullet.h"

void Bullet::FireBullet(Tank1 &tank) {
    if(tank.active){
        active = true;
        position = tank.position;
        velocity = {cos(tank.rotation * DEG2RAD) * bulletSpeed, sin(tank.rotation * DEG2RAD) * bulletSpeed};
        shooter = &tank; // Asignar el tanque que dispara la bala
    }


}

void Bullet::BounceBullet(const Obstacle &obstacle) {
    // Revisar si la bala colisiona en el lado horizontal (superior/inferior) del obstáculo
    if ((this->position.x > obstacle.rect.x && this->position.x < obstacle.rect.x + obstacle.rect.width) &&
        (this->position.y <= obstacle.rect.y || this->position.y >= obstacle.rect.y + obstacle.rect.height)) {
        this->velocity.y *= -1;  // Invertir la dirección en el eje Y
        }
    // Revisar si la bala colisiona en el lado vertical (izquierda/derecha) del obstáculo
    if ((this->position.y > obstacle.rect.y && this->position.y < obstacle.rect.y + obstacle.rect.height) &&
        (this->position.x <= obstacle.rect.x || this->position.x >= obstacle.rect.x + obstacle.rect.width)) {
        this->velocity.x *= -1;  // Invertir la dirección en el eje X
        }
}