#pragma once
#include "Header.h"
#include "Bullet.h"
#include "Config.h"
#include "NormalBullet.h"

class Enemy {
private:
    RectangleShape hitbox;

    Sprite enemySprite;
    IntRect frameRect;
    static Texture enemyT;
    Clock animationClock;

    int state = 0;

    Clock shootCooldown;
    vector<Bullet> bullets;

    static SoundBuffer shootB;
    static Sound shootS;
public:
    Enemy(Vector2f position);

    void moveEnemy();

    void update();

    void setPosition(Vector2f pos);

    Vector2f getPosition();

    FloatRect getGlobalBounds();

    vector<Bullet>& getBullets();

    void reset();

    int getHits();

    void changeState();

    void setHits(int hits);

    void shoot();

    void moveBullets();

    void show(RenderWindow& window);
};