#pragma once
#include "SFML/Graphics.hpp"
#include "Header.h"

class Orb
{
protected:
	RectangleShape hitbox;
	static Texture orbT;
	Sprite orbSprite;
	IntRect frameRect;
	int orbType;
public:
	Orb(Vector2f position);

	void moveOrb();

	virtual int getType();

	Vector2f getPosition();

	FloatRect getGlobalBounds();

	void showOrb(RenderWindow& window);
};

