#include "Orb.h"

Orb::Orb(Vector2f position)
{
	orbT.loadFromFile("./Textures/orbs.png");
	orbSprite.setTexture(orbT);
	orbSprite.setPosition(position);
	orbSprite.scale(1.5, 1.5);

	hitbox.setSize(Vector2f(60, 60));
	hitbox.setPosition(position.x + 7.5, position.y + 7.5);
}

void Orb::moveOrb()
{
	orbSprite.move(0, 5);
	hitbox.move(0, 5);
}

int Orb::getType()
{
	return orbType;
}

Vector2f Orb::getPosition()
{
	return hitbox.getPosition();
}

FloatRect Orb::getGlobalBounds()
{
	return hitbox.getGlobalBounds();
}

void Orb::showOrb(RenderWindow& window)
{
	window.draw(orbSprite);
}
Texture Orb::orbT;