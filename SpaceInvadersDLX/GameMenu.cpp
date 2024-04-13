#include "Header.h"
#include "GameMenu.h"

GameMenu::GameMenu(RenderWindow& win, Player& refPlayer, SkinsManager& manager)
	:window(win),
	player(refPlayer),
	skinManager(manager)
{
	menuClickB.loadFromFile("./Sounds/blipSelect.wav");
	menuClickS.setBuffer(menuClickB);

	buyB.loadFromFile("./Sounds/bought.wav");
	buyS.setBuffer(buyB);

	blockB.loadFromFile("./Sounds/block.wav");
	blockS.setBuffer(blockB);

	loadScore();
	buttonFont.loadFromFile("./Fonts/CooperBits.ttf");
	titleFont.loadFromFile("./Fonts/Crang.ttf");
	subtitleFont.loadFromFile("./Fonts/VeniceClassic.ttf");


	BGT.loadFromFile("./Textures/menuBG.png");
	BG1.setTexture(&BGT);
	BG1.setSize(Vector2f(WIDTH, HEIGHT));

	BG2.setTexture(&BGT);
	BG2.setSize(Vector2f(-WIDTH, HEIGHT));

	logoT.loadFromFile("./Textures/logo.png");
	logo.setSize(Vector2f(1409, 207));
	logo.scale(0.5, 0.5);
	logo.setPosition(Vector2f(100, 80));
	logo.setTexture(&logoT);

	initText(subtitle, subtitleFont, 80, 100, 180, "(Deluxe)",
		5, Color(92, 222, 255), Color(78, 80, 191));

	for (int i = 0, posY = menuY; i < texts.size(); i++, posY += menuStep) {
		Text text;
		initText(text, buttonFont, 80, 100, posY,
			texts[i], 5, Color::White, Color::Black);
		buttonsText.push_back(text);
	}
	for (int i = 0; i < buyButtonsTexts.size(); i++) {
		Text text;
		initText(text, buttonFont, 80, 400 * (i + 1), HEIGHT/2 - 40,
			buyButtonsTexts[i], 5, Color::White, Color::Black);
		buyButtons.push_back(text);
	}

	initText(backButton, buttonFont, 60, 20, 10, "Back", 5, Color::White, Color::Black);

	initText(totalScoreText, buttonFont, 60, 1000, 10, "Score: " + to_string(totalScore), 
		5, Color::White, Color::Black);

	for (int i = 1; i < 3; i++) {
		for (int j = 1; j < 3; j++) {
			RectangleShape slot;
			slot.setFillColor(Color(51, 51, 51, 150));
			slot.setPosition(Vector2f(250 * (j-0.7), 250 * (i-0.3)));
			slot.setSize(Vector2f(200, 200));
			skinSlots.push_back(slot);
		}
	}
	playerVisualTexture.loadFromFile("./Textures/skins.png");
	playerVisual.setTexture(playerVisualTexture);
	playerVisual.setTextureRect(IntRect(0, 0, 32, 32));
	playerVisual.setPosition(875, 250);
	playerVisual.setScale(12, 12);

	for (int i = 0; i < skinManager.getSkins().size(); i++) {
		Text temp;
		float posX = (i % 2) * 250 + 200 * 0.3f + 40;
		float posY = (i / 2) * 250 + 200 * 0.3f + 295;
		initText(temp, buttonFont, 60, posX, posY, 
			to_string(skinManager.getSkins()[i].getCost()),
			5, Color::White, Color::Black);
		skinPrices.push_back(temp);
	}

	for (int i = 0; i < skinManager.getSkins().size(); ++i) {
		if (i < skinSlots.size()) {
			float posX = (i % 2) * 250 + 200 * 0.3f + 50;
			float posY = (i / 2) * 250 + 200 * 0.3f + 150;
			skinManager.getSkins()[i].getSkinSprite().setPosition(posX, posY);
			skinManager.getSkins()[i].getSkinSprite().setScale(4, 4);
		}
	}

	initText(questionText, buttonFont, 60, 200, 250,
		"Would you like to buy this Skin?", 5, Color::White, Color::Black);
}

void GameMenu::processEvents()
{
	Event event;
	while (window.pollEvent(event)) {
		Vector2i mousePosition = Mouse::getPosition(window);
		if (event.type == Event::Closed) {
			exit(0);
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			exit(0);
			window.close();
		}

		if (event.type == Event::MouseButtonPressed &&
			event.mouseButton.button == Mouse::Left) {
			handleMouseClick(mousePosition);
		}
	}
}

void GameMenu::update()
{
	totalScoreText.setString("Score: " + to_string(totalScore));
	BG1.move(0.2, 0);
	if (BG1.getPosition().x >= WIDTH) BG1.setPosition(Vector2f(0, 0));
	BG2.move(0.2, 0);
	if (BG2.getPosition().x >= WIDTH) BG2.setPosition(Vector2f(0, 0));
	Vector2i mousePosition = Mouse::getPosition(window);

	handleColorChange(mousePosition, backButton);
	for (auto& i : buyButtons) {
		handleColorChange(mousePosition, i);
	}
	for (auto& i : buttonsText) {
		handleColorChange(mousePosition, i);
	}
}

void GameMenu::render()
{
	window.clear();
	if (page == 0) {
		window.draw(BG1);
		window.draw(BG2);
		window.draw(logo);
		window.draw(subtitle);
		for (auto i : buttonsText) {
			window.draw(i);
		}
	}
	else if (page == 1) {
		window.draw(BG1);
		window.draw(BG2);
		window.draw(backButton);
		window.draw(totalScoreText);
		for (auto i : skinSlots) {
			window.draw(i);
		}
		for (auto& i : skinManager.getSkins()) {
			window.draw(i.getSkinSprite());
		}
		for (int i = 0; i < skinManager.getSkins().size(); i++) {
			if (!skinManager.getSkins()[i].isUnlocked()) {
				window.draw(skinPrices[i]);
			}
		}
	}
	window.draw(playerVisual);
	if (offeringPurchase) {
		window.draw(questionText);
		for (auto i : buyButtons) {
			window.draw(i);
		}
	}
	window.display();
}

bool GameMenu::getResult()
{
	return resultMenu;
}

void GameMenu::loadScore()
{
	ifstream scoreFile("score.txt");
	if (scoreFile.is_open()) {
		scoreFile >> totalScore;
	}
	scoreFile.close();
}

void GameMenu::saveScore()
{
	ofstream scoreFile("score.txt");
	if (scoreFile.is_open()) {
		scoreFile << totalScore;
	}
	scoreFile.close();
}

void GameMenu::saveSkinInfo()
{
	ofstream skinFile("skins.txt");
	if (skinFile.is_open()) {
		for (auto i : skinManager.getSkins()) {
			skinFile << i.getSkinId() << ";" << i.getSkinName() << ";" <<
				i.getSkinSprite().getTextureRect().left << ";" <<
				i.getSkinSprite().getTextureRect().top << ";" <<
				i.getSkinSprite().getTextureRect().width << ";" <<
				i.getSkinSprite().getTextureRect().height << ";" <<
				i.getCost() << ";" << i.isUnlocked() << endl;
		}
	}
}

void GameMenu::handleColorChange(const Vector2i& mousePosition, Text& text) {
	if (text.getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y))) {
		text.setFillColor(Color::Black);
	}
	else {
		text.setFillColor(Color::White);
	}
}

void GameMenu::initText(Text& text, Font& font, int fontsize, float posX,
	float posY, string str,
	int outlineThicknessSize, Color color, Color outlineColor) {
	text.setFont(font);
	text.setCharacterSize(fontsize);
	text.setPosition(posX, posY);
	text.setString(str);
	text.setFillColor(color);
	text.setOutlineThickness(outlineThicknessSize);
	text.setOutlineColor(outlineColor);
}

void GameMenu::MainMenu() {
	resultMenu = false;
	while (!resultMenu && window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

void GameMenu::handleMouseClick(const Vector2i& mousePosition) {
	loadScore();
	if (page == 1) {
		if (!offeringPurchase) {
			if (backButton.getGlobalBounds().contains(float(mousePosition.x),
				float(mousePosition.y))) {
				menuClickS.play();
				page = 0;
			}
			for (int i = 0; i < skinSlots.size() - 1; i++) {
				if (skinSlots[i].getGlobalBounds().contains(float(mousePosition.x),
					float(mousePosition.y))) {
					if (!skinManager.getSkins()[i].isUnlocked()){
						if (skinManager.getSkins()[i].getCost() <= totalScore) {
							menuClickS.play();
							skinToUnlock = i;
							offeringPurchase = true;
							break;
						}
						else blockS.play();
					}
					else {
						menuClickS.play();
						player.setSkin(i);
						playerVisual.setTextureRect(IntRect(i * 32, 0, 32, 32));
					}
				}
			}
		}
		else {
			if (buyButtons[0].getGlobalBounds().contains(float(mousePosition.x),
				float(mousePosition.y))) {
				buyS.play();
				skinManager.unlockSkin(skinToUnlock);
				totalScore -= skinManager.getSkins()[skinToUnlock].getCost();
				saveScore();
				loadScore();
				saveSkinInfo();
				offeringPurchase = false;
			}
			else if (buyButtons[1].getGlobalBounds().contains(float(mousePosition.x),
				float(mousePosition.y))) {
				menuClickS.play();
				offeringPurchase = false;
			}
		}
	}
	else if (page == 0) {
		for (int i = 0; i < buttonsText.size(); i++) {
			if (buttonsText[i].getGlobalBounds().contains(float(mousePosition.x),
				float(mousePosition.y))) {
				menuClickS.play();
				switch (i) {
				case 0:
					resultMenu = true;
					break;
				case 1:
					page = 1;
					break;
				case 2:
					exit(0);
					window.close();
					break;
				}
			}
		}
	}
}