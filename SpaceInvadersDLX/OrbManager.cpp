#include "OrbManager.h"

OrbManager::OrbManager()
{
}

void OrbManager::createOrb()
{
	Time elapsed = cooldown.getElapsedTime();
	if (elapsed.asSeconds() >= 5) {
		if (random(1, 1000) < 10) {
			int p = random(1, 10);
			if (p <= 4) orbs.push_back(SmartOrb(Vector2f(random(373, 980), -75)));
			else if (p <= 7 && p > 4) orbs.push_back(MultiOrb(Vector2f(random(373, 980), -75)));
			else if (p <= 8 && p > 7) orbs.push_back(BeamOrb(Vector2f(random(373, 980), -75)));
			else if (p > 8) orbs.push_back(ShieldOrb(Vector2f(random(373, 980), -75)));
			cooldown.restart();
		}
	}
}

void OrbManager::show(RenderWindow& window)
{
	for (auto orb : orbs) {
		orb.showOrb(window);
	}
}

void OrbManager::reset()
{
	orbs.clear();
	cooldown.restart();
}

void OrbManager::updateOrbs()
{
	for (auto& orb : orbs) {
		orb.moveOrb();
		if (orb.getPosition().y > HEIGHT) {
			orbs.pop_back();
		}
	}
}

void OrbManager::deleteOrb(int index)
{
	orbs.erase(orbs.begin() + index);
}

vector<Orb>& OrbManager::getOrbs()
{
	return orbs;
}
