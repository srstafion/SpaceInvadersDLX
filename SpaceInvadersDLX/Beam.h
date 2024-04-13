#pragma once
#include "Bullet.h"
#include "Config.h"
#include "Player.h"

class Beam : public Bullet
{
public:
	Beam(Vector2f startPosition, int playerY);
};

