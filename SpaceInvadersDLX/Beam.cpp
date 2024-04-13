#include "Beam.h"

Beam::Beam(Vector2f startPosition, int playerY)
	:Bullet(startPosition)
{
	beam = true;
	bullet.setSize(Vector2f(12, playerY));
	bullet.setOutlineThickness(7);
	bullet.setOutlineColor(Color(128, 240, 255));
}
