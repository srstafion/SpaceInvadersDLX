#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Bullet.h"
#include "NormalBullet.h"
#include "Beam.h"
#include "Config.h"
#include "Skin.h"
#include "SkinsManager.h"
#include <vector>
using namespace sf;
using namespace std;

class Player {
private:
    Sprite player;
    Texture playerT;
    RectangleShape mask1;
    RectangleShape mask2;

    SkinsManager& skinManager;

    vector<Bullet> bullets;
    Clock shootCountdown;
    Clock powerupDuration;
    int shootingMode = 0;
    int beamShots = 0;

    RectangleShape shieldShape;
    Texture shieldT;
    bool shield = 0;
    Clock shieldDuration;

    SoundBuffer beamB;
    Sound beamS;

    SoundBuffer buffer;
    Sound sound;

    bool canShoot = true;
public:
    Player(SkinsManager& manager);

    void movePlayer(int direction);

    void shoot();

    void update();

    void createNormalBullet();

    void createTripleBullet();

    void createBeamBullet();

    void createXPBullet();

    Vector2f getPosition();

    Skin getSkin(vector<Skin>& skins);

    void setSkin(int selectedSkin);

    void reset();

    vector<FloatRect> getGlobalBounds();

    void setShootingMode(int mode);

    int getShootingMode();

    void resetPowerUp();

    void resetShield();

    void setShield();

    bool getShield();

    vector<Bullet>& getBullets();

    void updateBullets();

    void toggleShot(int toggle);

    void deleteBullet(int index);

    void show(RenderWindow& window);
};