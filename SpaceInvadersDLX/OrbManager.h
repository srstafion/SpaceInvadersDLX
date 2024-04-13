#pragma once
#include "Header.h"
#include "Orb.h"
#include "BeamOrb.h"
#include "MultiOrb.h"
#include "SmartOrb.h"
#include "ShieldOrb.h"
#include "Config.h"

class OrbManager {
private:
    vector<Orb> orbs;
    SoundBuffer powerB;
    Sound power;
    Clock cooldown;
public:
    OrbManager();

    void createOrb();

    void show(RenderWindow& window);

    void reset();

    void updateOrbs();

    void deleteOrb(int index);

    vector<Orb>& getOrbs();
};