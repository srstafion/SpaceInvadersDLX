#pragma once
#include "Header.h"

class Skin {
private:
    int skinId;
    string skinName;
    Sprite skinSprite;
    IntRect frameRect;
    int cost;
    bool unlocked;
    static Texture skinTextures;
public:
    Skin(int skinId, string skinName, IntRect zone, int cost, bool unlocked);

    int getSkinId();

    string getSkinName();

    Sprite& getSkinSprite();

    int getCost();

    bool isUnlocked();

    void unlock();
};