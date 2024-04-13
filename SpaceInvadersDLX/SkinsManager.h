#pragma once
#include "Header.h"
#include "Skin.h"

class SkinsManager
{
private:
	vector<Skin> skins;
public:
	SkinsManager();

	vector<Skin>& getSkins();

	void unlockSkin(int id);
};