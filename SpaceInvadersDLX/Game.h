#pragma once
#include "Config.h"
#include "EnemyFactory.h"
#include "GameMenu.h"
#include "Header.h"
#include "Orb.h"
#include "OrbManager.h"
#include "Player.h"
#include "Skin.h"
#include "SkinsManager.h"
#include "Star.h"

class Game {
private:
    RenderWindow window;
    SkinsManager skinManager;
    GameMenu menu;
    Player player;
    EnemyFactory enemyFactory;
    OrbManager orbManager;

    int gameState = 0;

    float width = 750;
    float height = 800;

    RectangleShape frame;
    RectangleShape playRegion;
    RectangleShape gameBG1;
    RectangleShape gameBG2;
    RectangleShape background;

    Texture frameT;
    Texture gameBG1Texture;
    Texture gameBG2Texture;
    Texture backgroundTexture;

    vector<Star> stars;

    Text youLost;
    Text allScore;
    Text scoreText;
    Font scoreFont;

    int scoreTotal = 0;
    int scoreGame = 0;

    static int value;
    thread th;
public:
    Game();
    ~Game();

    void run();
    void handleEvents();
    void handleInput();
    void update();
    void render();

    void resetGame();

    bool collisionCheck();

    void saveScore(int score);
    void loadScore();

    void initializeTexts();
    void initializeBG();
    void initializeUI();

    void static incrementer();

    void initTexturedObject(RectangleShape& shape, Texture& texture, string path, Vector2f position, Vector2f size);
    void initText(Text& text, Font& font, float posX, float posY, string str, int sizeFont, int thickness, Color menuTextColor, Color outlineColor);
};