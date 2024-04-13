#pragma once
#include "Header.h"
#include "Enemy.h"
#include "Config.h"

class EnemyFactory {
private:
    vector<Enemy> enemies;
    vector<Bullet> temporaryBullets;
    SoundBuffer hitHurtB;
    Sound hitHurt;
    SoundBuffer explodeB;
    Sound explode;
public:
    EnemyFactory();

    void addRow();

    void show(RenderWindow& window);

    void updateEnemy();

    void reset();

    void deleteEnemy(int index);

    void handleBulletHit(int index);

    vector<Bullet>& getTempBullets();

    vector<Enemy>& getEnemies();
};