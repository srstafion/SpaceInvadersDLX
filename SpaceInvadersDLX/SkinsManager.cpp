#include "SkinsManager.h"

SkinsManager::SkinsManager()
{
	ifstream file("skins.txt");
	string line;
	while (getline(file, line)) {
		int skinId;
		string skinName;
		IntRect zone;
		int cost;
		bool unlocked;

		int startPos = 0;
		for (int i = 0; i < 7; i++) {
			int endPos = line.find(';', startPos);
			string token = line.substr(startPos, endPos - startPos);
			switch (i) {
			case 0:
				skinId = stoi(token);
				break;
			case 1:
				skinName = token;
				break;
			case 2:
				zone.left = stoi(token);
				break;
			case 3:
				zone.top = stoi(token);
				break;
			case 4:
				zone.width = stoi(token);
				break;
			case 5:
				zone.height = stoi(token);
				break;
			case 6:
				cost = stoi(token);
				break;
			}
			startPos = endPos + 1;
		}
		unlocked = stoi(line.substr(startPos));
		skins.push_back(Skin(skinId, skinName, zone, cost, unlocked));
	}
	file.close();
}

vector<Skin>& SkinsManager::getSkins()
{
	return skins;
}

void SkinsManager::unlockSkin(int id)
{
	for (auto& i : skins) {
		if (i.getSkinId() == id) {
			i.unlock();
		}
	}
}
