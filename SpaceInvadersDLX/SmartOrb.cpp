#include "SmartOrb.h"

SmartOrb::SmartOrb(Vector2f startPosition)
	:Orb(startPosition)
{
	orbType = 1;
	frameRect = IntRect(100, 0, 50, 50);
	orbSprite.setTextureRect(frameRect);
}
