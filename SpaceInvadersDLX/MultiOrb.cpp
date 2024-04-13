#include "MultiOrb.h"

MultiOrb::MultiOrb(Vector2f startPosition)
	:Orb(startPosition)
{
	orbType = 2;
	frameRect = IntRect(50, 0, 50, 50);
	orbSprite.setTextureRect(frameRect);
}
