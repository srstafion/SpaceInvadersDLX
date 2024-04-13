#pragma once
#include "Header.h"
#include "Config.h"
#include "Player.h"
#include "Skin.h"
#include "SkinsManager.h"
using namespace std;
using namespace sf;
class GameMenu {
private:
    RenderWindow& window;

    Font buttonFont;
    Font titleFont;
    Font subtitleFont;

    Player& player;
    Texture playerVisualTexture;
    Sprite playerVisual;

    SkinsManager& skinManager;

    RectangleShape BG1;
    RectangleShape BG2;
    Texture BGT;

    RectangleShape logo;
    Texture logoT;

    Text subtitle;
    Text backButton;
    Text questionText;
    Text totalScoreText;
    vector<Text> buttonsText;
    vector<Text> buyButtons;
    vector<string> texts{ "Play", "Skins", "Exit" };
    vector<string> buyButtonsTexts{ "Yes", "No" };

    vector<RectangleShape> skinSlots;
    vector<Text> skinPrices;

    int page = 0;
    bool offeringPurchase = false;
    int skinToUnlock = 0;
    int totalScore;
    float menuY = 330;
    int menuStep = 120;
    bool resultMenu = false;

    SoundBuffer menuClickB;
    Sound menuClickS;
    SoundBuffer buyB;
    Sound buyS;
    SoundBuffer blockB;
    Sound blockS;
public:
    GameMenu(RenderWindow& win, Player& refPlayer, SkinsManager& manager);

    void processEvents();
    void update();
    void render();

    bool getResult();

    void loadScore();
    void saveScore();
    void saveSkinInfo();

    void handleColorChange(const Vector2i& mousePosition, Text& text);
    void handleMouseClick(const sf::Vector2i& mousePosition);

    void initText(Text& text, Font& font, int fontsize, float posX,
        float posY, string str, int outlineThicknessSize,
        Color color, Color outlineColor);

    void MainMenu();
};