#include "ShieldOrb.h"

ShieldOrb::ShieldOrb(Vector2f startPosition)
	:Orb(startPosition)
{
	orbType = 0;
	frameRect = IntRect(150, 0, 50, 50);
	orbSprite.setTextureRect(frameRect);
}
