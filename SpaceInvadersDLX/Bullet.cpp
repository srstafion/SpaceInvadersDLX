#include "Bullet.h"

Bullet::Bullet(Vector2f position) {
    bullet.setPosition(position);
    bullet.setFillColor(Color::White);
}

void Bullet::moveBullet(int amount)
{
    bullet.move(0, amount);
}

Vector2f Bullet::getPosition()
{
    return bullet.getPosition();
}

bool Bullet::getBeam()
{
    return beam;
}

void Bullet::evaluateBullet()
{
    bulletValue = 3;
    bullet.setOutlineColor(Color::Green);
}

int Bullet::getBulletValue()
{
    return bulletValue;
}

Clock Bullet::getLifetime()
{
    return lifetime;
}

FloatRect Bullet::getGlobalBounds()
{
    return bullet.getGlobalBounds();
}

void Bullet::opacify()
{
    bullet.setFillColor(Color(255, 255, 255, 150));
    bullet.setOutlineColor(Color(128, 240, 255, 150));
}

void Bullet::showBullet(RenderWindow& window)
{
    window.draw(bullet);
}