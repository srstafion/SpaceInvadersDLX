#include "Enemy.h"

Enemy::Enemy(Vector2f position)
{
    hitbox.setSize(Vector2f(75, 75));
    hitbox.setPosition(position);

    shootCooldown.restart();

    frameRect = IntRect(0, 0, 32, 32);

    enemyT.loadFromFile("./Textures/enemySprites.png");
    enemySprite.setTexture(enemyT);
    enemySprite.setTextureRect(frameRect);
    enemySprite.setPosition(position);
    enemySprite.scale(2.4, 2.4);

    shootB.loadFromFile("./Sounds/laserShootEnemy.wav");
    shootS.setBuffer(shootB);
}

void Enemy::moveEnemy()
{
    hitbox.move(0, 0.7);
    enemySprite.move(0, 0.7);
}

void Enemy::update()
{
    moveEnemy();
    shoot();
    moveBullets();
    for (auto i = bullets.begin(); i != bullets.end(); ) {
        if (i->getPosition().y > HEIGHT) {
            i = bullets.erase(i);
        }
        else {
            i++;
        }
    }

    if (animationClock.getElapsedTime().asSeconds() >= 1) {
        if (frameRect.top == 32) {
            frameRect.top = 0;
        }
        else frameRect.top += 32;
        enemySprite.setTextureRect(frameRect);
        animationClock.restart();
    }
}

void Enemy::setPosition(Vector2f pos)
{
    hitbox.setPosition(pos);
    enemySprite.setPosition(pos);
}

Vector2f Enemy::getPosition()
{
    return hitbox.getPosition();
}

FloatRect Enemy::getGlobalBounds()
{
    return hitbox.getGlobalBounds();
}

vector<Bullet>& Enemy::getBullets()
{
    return bullets;
}

void Enemy::reset()
{
    bullets.clear();
}

int Enemy::getHits()
{
    return state;
}

void Enemy::changeState()
{
    frameRect.left += 32;
    enemySprite.setTextureRect(frameRect);
}

void Enemy::setHits(int hits)
{
    state = hits;
}

void Enemy::shoot()
{
    int rate = (state == 2) ? 16 : 4;
    if (random(1, 1000) < rate) {
        NormalBullet bullet(Vector2f(hitbox.getPosition().x + hitbox.getSize().x / 2,
            hitbox.getPosition().y + hitbox.getSize().y));
        bullets.push_back(bullet);
        shootS.play();
    }
}

void Enemy::moveBullets()
{
    for (auto& bullet : bullets) {
        bullet.moveBullet(7);
    }
}

void Enemy::show(RenderWindow& window)
{
    window.draw(enemySprite);
}
Texture Enemy::enemyT;
SoundBuffer Enemy::shootB;
Sound Enemy::shootS;