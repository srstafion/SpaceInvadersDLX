#include "BeamOrb.h"

BeamOrb::BeamOrb(Vector2f startPosition)
	:Orb(startPosition)
{
	orbType = 3;
	frameRect = IntRect(0, 0, 50, 50);
	orbSprite.setTextureRect(frameRect);
}
