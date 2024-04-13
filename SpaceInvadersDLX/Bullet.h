#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
using namespace sf;

class Bullet {
protected:
    RectangleShape bullet;
    bool beam = false;
    Clock lifetime;
    int bulletValue = 1;
public:
    Bullet(Vector2f position);

    void moveBullet(int amount);

    Vector2f getPosition();

    bool getBeam();

    void evaluateBullet();

    int getBulletValue();

    Clock getLifetime();

    FloatRect getGlobalBounds();

    void opacify();

    void showBullet(RenderWindow& window);
};