#include "Player.h"

Player::Player(SkinsManager& manager)
    :skinManager(manager)
{
    playerT.loadFromFile("./Textures/skins.png");
    player.setTexture(playerT);
    player.setScale(2.35, 2.35);
    player.setPosition(672.5f, 700);

    mask1.setFillColor(Color(0, 255, 0, 150));
    mask2.setFillColor(Color(0, 255, 0, 150));
    mask1.setSize(Vector2f(25, 75));
    mask2.setSize(Vector2f(75, 50));
    mask1.setPosition(697.5f, 700);
    mask2.setPosition(672.5f, 725);

    shieldShape.setSize(Vector2f(100, 100));
    shieldShape.setPosition(660, 687.5f);
    shieldT.loadFromFile("./Textures/shield.png");
    shieldShape.setTexture(&shieldT);

    shootCountdown.restart();
    beamB.loadFromFile("./Sounds/beamShot.wav");
    beamS.setBuffer(beamB);
    buffer.loadFromFile("./Sounds/laserShoot.wav");
    sound.setBuffer(buffer);
}

void Player::movePlayer(int direction)
{
    switch (direction) {
    case 1:
        if (player.getPosition().y > 15) {
            player.move(0, -5);
            mask1.move(0, -5);
            mask2.move(0, -5);
            shieldShape.move(0, -5);
            if (player.getPosition().y < 15) {
                player.setPosition(player.getPosition().x, 15);
                mask1.setPosition(player.getPosition().x + 25, 15);
                mask2.setPosition(player.getPosition().x, 40);
            }
        }
        break;
    case 2:
        if (player.getPosition().x > PLAYPOS + 15) {
            player.move(-5, 0);
            mask1.move(-5, 0);
            mask2.move(-5, 0);
            shieldShape.move(-5, 0);
            if (player.getPosition().x < PLAYPOS + 15) {
                player.setPosition(PLAYPOS + 15, player.getPosition().y);
                mask1.setPosition(PLAYPOS + 40, mask1.getPosition().y);
                mask2.setPosition(PLAYPOS + 15, mask2.getPosition().y);
            }
        }
        break;
    case 3:
        if (player.getPosition().y < HEIGHT - 90) {
            player.move(0, 5);
            mask1.move(0, 5);
            mask2.move(0, 5);
            shieldShape.move(0, 5);
        }
        break;
    case 4:
        if (player.getPosition().x < PLAYPOS + PLAYWIDTH - 90) {
            player.move(5, 0);
            mask1.move(5, 0);
            mask2.move(5, 0);
            shieldShape.move(5, 0);
            if (player.getPosition().x > PLAYPOS + PLAYWIDTH - 90) {
                player.setPosition(PLAYPOS + PLAYWIDTH - 90, player.getPosition().y);
                mask1.setPosition(PLAYPOS + PLAYWIDTH - 65, mask1.getPosition().y);
                mask2.setPosition(PLAYPOS + PLAYWIDTH - 90, mask2.getPosition().y);
            }
        }
        break;
    }
}

void Player::shoot()
{
    if (canShoot) {
        if (shootCountdown.getElapsedTime().asMilliseconds() >= 150
            || bullets.empty()) {
            switch (shootingMode) {
            case 0:
                createNormalBullet();
                shootCountdown.restart();
                break;
            case 1:
                createXPBullet();
                shootCountdown.restart();
                break;
            case 2:
                createTripleBullet();
                shootCountdown.restart();
                break;
            case 3:
                createBeamBullet();
                shootCountdown.restart();
                break;
            }
        }
    }
}

void Player::createNormalBullet()
{
    NormalBullet bullet(Vector2f(player.getPosition().x + 36,
        player.getPosition().y));
    bullets.push_back(bullet);
    sound.play();
}

void Player::update()
{
    if (shootingMode == 1 &&
        powerupDuration.getElapsedTime().asSeconds() >= 7) {
        shootingMode = 0;
    }
    else if (shootingMode == 2 &&
        powerupDuration.getElapsedTime().asSeconds() >= 1.5) {
        shootingMode = 0;
    }
    else if (shield && shieldDuration.getElapsedTime().asSeconds() >= 10) {
        shield = 0;
    }
    if (beamShots == 3) {
        shootingMode = 0;
        beamShots = 0;
    }
}

void Player::createTripleBullet()
{
    NormalBullet bullet(Vector2f(player.getPosition().x + 36,
        player.getPosition().y));
    NormalBullet bulletA(Vector2f(player.getPosition().x + 6,
        player.getPosition().y + 35));
    NormalBullet bulletB(Vector2f(player.getPosition().x + 67,
        player.getPosition().y + 35));
    bullets.push_back(bullet);
    bullets.push_back(bulletA);
    bullets.push_back(bulletB);
    sound.play();
}

void Player::createBeamBullet()
{
    if (beamShots < 3) {
        Beam bullet(Vector2f(player.getPosition().x + 31.1, 0),
            player.getPosition().y);
        bullets.push_back(bullet);
        beamS.play();
        beamShots++;
    }
    else {
        shootingMode = 0;
        beamShots = 0;
    }
}

void Player::createXPBullet()
{
    NormalBullet bullet(Vector2f(player.getPosition().x + 36,
        player.getPosition().y));
    bullet.evaluateBullet();
    bullets.push_back(bullet);
    sound.play();
}

Vector2f Player::getPosition()
{
    return player.getPosition();
}

Skin Player::getSkin(vector<Skin>& skins)
{
    for (auto& skin : skins) {
        if (skin.getSkinSprite().getTextureRect() == player.getTextureRect()) {
            return skin;
        }
    }
}

void Player::setSkin(int selectedSkin) {
    for (auto& skin : skinManager.getSkins()) {
        if (skin.getSkinId() == selectedSkin) {
            player.setTextureRect(skin.getSkinSprite().getTextureRect());
            break;
        }
    }
}

vector<FloatRect> Player::getGlobalBounds()
{
    vector<FloatRect> bounds;
    bounds.push_back(mask1.getGlobalBounds());
    bounds.push_back(mask2.getGlobalBounds());
    return bounds;
}

void Player::reset()
{
    mask1.setPosition(697.5f, 700);
    mask2.setPosition(672.5f, 725);
    player.setPosition(672.5f, 700);
    bullets.clear();
    shootingMode = 0;
    beamShots = 0;
    shield = 0;
    canShoot = true;
}

void Player::setShootingMode(int mode)
{
    shootingMode = mode;
}

int Player::getShootingMode()
{
    return shootingMode;
}

void Player::setShield()
{
    shield = 1;
}

bool Player::getShield()
{
    return shield;
}

void Player::resetPowerUp()
{
    powerupDuration.restart();
}

void Player::resetShield()
{
    shieldDuration.restart();
}

vector<Bullet>& Player::getBullets()
{
    return bullets;
}

void Player::updateBullets()
{
    for (int i = 0; i < bullets.size(); i++) {
        if (!bullets[i].getBeam()) {
            bullets[i].moveBullet(-10);
            if (bullets[i].getPosition().y < 0) bullets.erase(bullets.begin() + i);
        }
        else {
            Time elapsed = bullets[i].getLifetime().getElapsedTime();
            if (elapsed.asSeconds() >= 2) bullets[i].opacify();
            if (elapsed.asSeconds() >= 2.5) bullets.erase(bullets.begin() + i);
        }
    }
}

void Player::toggleShot(int toggle)
{
    canShoot = toggle;
}

void Player::deleteBullet(int index)
{
    bullets.erase(bullets.begin() + index);
}

void Player::show(RenderWindow& window)
{
    window.draw(player);
    if (shield) window.draw(shieldShape);
}
