#include "Skin.h"

Skin::Skin(int skinId, string skinName, IntRect zone, int cost, bool unlocked)
{
    this->skinId = skinId;
    this->skinName = skinName;
    frameRect = zone;
    skinTextures.loadFromFile("./Textures/skins.png");
    skinSprite.setTexture(skinTextures);
    skinSprite.setTextureRect(frameRect);
    this->cost = cost;
    this->unlocked = unlocked;
}

int Skin::getSkinId()
{
    return skinId;
}

string Skin::getSkinName()
{
    return skinName;
}

Sprite& Skin::getSkinSprite()
{
    return skinSprite;
}

int Skin::getCost()
{
    return cost;
}

bool Skin::isUnlocked()
{
    return unlocked;
}

void Skin::unlock()
{
    unlocked = true;
}
Texture Skin::skinTextures;