#pragma once
#include "Orb.h"

class MultiOrb : public Orb
{
private:
	static Texture orbT;
public:
	MultiOrb(Vector2f startPosition);
};

