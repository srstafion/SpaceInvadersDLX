#include "NormalBullet.h"

NormalBullet::NormalBullet(Vector2f startPosition)
	: Bullet(startPosition)
{
	bullet.setSize(Vector2f(3, 15));
	bullet.setOutlineThickness(2);
	bullet.setOutlineColor(Color::Yellow);

}
