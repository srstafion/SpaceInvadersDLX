#include "EnemyFactory.h"

EnemyFactory::EnemyFactory()
{
    hitHurtB.loadFromFile("./Sounds/hitHurt.wav");
    hitHurt.setBuffer(hitHurtB);
    explodeB.loadFromFile("./Sounds/explosion.wav");
    explode.setBuffer(explodeB);
}

void EnemyFactory::addRow()
{
    int pattern = rand() % 3;
    switch (pattern) {
    case 0:
        for (int i = 1; i < 7; i++) {
            float x = PLAYPOS - 12.5 + i * 100.0f;
            enemies.push_back(Enemy(Vector2f(x, -50)));
        }
        break;
    case 1:
        for (int i = 0; i < 5; i++) {
            float x;
            if (i == 0) {
                x = PLAYPOS - 12.5 + 100.0f;
            }
            else if (i == 1)
                x = PLAYPOS - 12.5 + 250.0f;
            else if (i == 4)
                x = PLAYPOS - 12.5 + 600.0f;
            else
                x = PLAYPOS - 12.5 + 150 + i * 100.0f;
            enemies.push_back(Enemy(Vector2f(x, -50)));
        }
        break;
    case 2:
        for (int i = 0; i < 2; i++) {
            float x;
            if (i == 0) {
                x = PLAYPOS - 12.5 + 250.0f;
            }
            else
                x = PLAYPOS - 12.5 + 450.0f;
            enemies.push_back(Enemy(Vector2f(x, -50)));
        }
        break;
    }
}

void EnemyFactory::show(RenderWindow& window)
{
    for (auto i : enemies) {
        i.show(window);
    }
}

void EnemyFactory::updateEnemy()
{
    for (int i = 0; i < temporaryBullets.size(); i++) {
        temporaryBullets[i].moveBullet(7);
        if (temporaryBullets[i].getPosition().y > HEIGHT) {
            temporaryBullets.erase(temporaryBullets.begin() + i);
        }
    }
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i].update();
        if (enemies[i].getPosition().y > HEIGHT + 75) {
            deleteEnemy(i);
        }
    }
}

void EnemyFactory::reset()
{
    for (auto& i : enemies) {
        i.reset();
    }
    enemies.clear();
    temporaryBullets.clear();
}

void EnemyFactory::deleteEnemy(int index)
{
    for (auto& i : enemies[index].getBullets()) {
        temporaryBullets.push_back(i);
    }
    enemies[index].reset();
    enemies.erase(enemies.begin() + index);
}

void EnemyFactory::handleBulletHit(int index)
{
    Enemy& enemy = enemies[index];
    enemy.setHits(enemy.getHits() + 1);
    if (enemy.getHits() == 3) {
        deleteEnemy(index);
        explode.play();
    }
    else {
        enemy.changeState();
        hitHurt.play();
    }
}

vector<Bullet>& EnemyFactory::getTempBullets()
{
    return temporaryBullets;
}

vector<Enemy>& EnemyFactory::getEnemies()
{
    return enemies;
}
