#include "Bullet.h"

void BounceBullet(Bullet &bullet, const Obstacle &obstacle) {
    // Borde del círculo de la bala (posición + radio)
    float bulletLeft = bullet.position.x - bullet.radius;
    float bulletRight = bullet.position.x + bullet.radius;
    float bulletTop = bullet.position.y - bullet.radius;
    float bulletBottom = bullet.position.y + bullet.radius;

    // Borde del rectángulo (obstáculo)
    float obstacleLeft = obstacle.rect.x;
    float obstacleRight = obstacle.rect.x + obstacle.rect.width;
    float obstacleTop = obstacle.rect.y;
    float obstacleBottom = obstacle.rect.y + obstacle.rect.height;

    // Verificar si hay colisión
    bool collisionX = bulletRight >= obstacleLeft && bulletLeft <= obstacleRight;
    bool collisionY = bulletBottom >= obstacleTop && bulletTop <= obstacleBottom;

    if (collisionX && collisionY) {
        // Determinar el lado de colisión
        float overlapLeft = bulletRight - obstacleLeft;
        float overlapRight = obstacleRight - bulletLeft;
        float overlapTop = bulletBottom - obstacleTop;
        float overlapBottom = obstacleBottom - bulletTop;

        // Revisar cuál de los cuatro lados tiene la menor superposición
        bool hitFromLeft = overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom;
        bool hitFromRight = overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom;
        bool hitFromTop = overlapTop < overlapBottom && overlapTop < overlapLeft && overlapTop < overlapRight;
        bool hitFromBottom = overlapBottom < overlapTop && overlapBottom < overlapLeft && overlapBottom < overlapRight;

        // Invertir la velocidad de acuerdo con el lado de colisión
        if (hitFromLeft || hitFromRight) {
            bullet.velocity.x *= -1;
            // Ajustar posición para evitar solapamiento
            bullet.position.x += (hitFromLeft ? overlapLeft : -overlapRight);
        }
        if (hitFromTop || hitFromBottom) {
            bullet.velocity.y *= -1;
            // Ajustar posición para evitar solapamiento
            bullet.position.y += (hitFromTop ? overlapTop : -overlapBottom);
        }
    }
}