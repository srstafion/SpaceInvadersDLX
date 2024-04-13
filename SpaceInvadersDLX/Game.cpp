#include "Game.h"

Game::Game() :
    window(sf::VideoMode(WIDTH, HEIGHT), "Space Invaders DLX"),
    player(skinManager),
    menu(window, player, skinManager),
    th(incrementer)
{
    loadScore();
    initializeTexts();
    initializeBG();
    initializeUI();
    player.setSkin(0);
}

Game::~Game()
{
    th.join();
}

void Game::initializeTexts()
{
    initText(scoreText, scoreFont, PLAYPOS / 8, 25, to_string(scoreGame), 
        40, 3, Color::White, Color::Black);
    initText(allScore, scoreFont, PLAYPOS / 8, 125, to_string(scoreTotal),
        40, 6, Color::White, Color::Black);
    initText(youLost, scoreFont, 500, 275,
        "You Lost!", 90, 6, Color::White, Color::Black);
}

void Game::initializeBG()
{
    initTexturedObject(gameBG1, gameBG1Texture, "background1",
        Vector2f(PLAYPOS, 0), Vector2f(width, height));
    initTexturedObject(gameBG2, gameBG2Texture, "background2",
        Vector2f(PLAYPOS, -HEIGHT), Vector2f(width, height));
    for (int i = 0; i < 5; i++) {
        stars.push_back(Star());
    }
}

void Game::initializeUI()
{
    scoreFont.loadFromFile("./Fonts/CooperBits.ttf");

    playRegion.setSize(Vector2f(PLAYWIDTH, HEIGHT));
    playRegion.setPosition(PLAYPOS, 0);

    initTexturedObject(frame, frameT, "frame", Vector2f(0, 0), Vector2f(WIDTH, HEIGHT));
    frame.setFillColor(Color(240, 74, 103));
}

void Game::run()
{
    while (window.isOpen()) {
        handleEvents();
        handleInput();
        update();
        render();
    }
}

void Game::handleEvents()
{
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
    }
    if (gameState == 0) {
        menu.MainMenu();
        if (menu.getResult()) {
            loadScore();
            gameState = 1;
            resetGame();
        }
    }
}

void Game::handleInput()
{
    if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
    if (gameState == 1) {
        if (Keyboard::isKeyPressed(Keyboard::W)) player.movePlayer(1);
        if (Keyboard::isKeyPressed(Keyboard::A)) player.movePlayer(2);
        if (Keyboard::isKeyPressed(Keyboard::S)) player.movePlayer(3);
        if (Keyboard::isKeyPressed(Keyboard::D)) player.movePlayer(4);
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            player.shoot();
            player.toggleShot(0);
        }
        else player.toggleShot(1);
    }
}

void Game::update()
{
    if (gameState != 2) {
        allScore.setString("Score:  \n" + to_string(scoreTotal));
        scoreText.setString("Total Score: \n" + to_string(scoreGame));

        player.update();
        player.updateBullets();

        if (value % 200 == 0) {
            enemyFactory.addRow();
            value = 0;
        }

        if (collisionCheck()) {
            gameState = 2;
            value = 0;
        }

        enemyFactory.updateEnemy();

        vector<Enemy>& enemies = enemyFactory.getEnemies();
        vector<Bullet>& playerBullets = player.getBullets();

        for (int i = 0; i < enemies.size(); i++) {
            if (enemies[i].getPosition().y >= HEIGHT + 75) {
                gameState = 2;
                break;
            }

            for (int j = 0; j < playerBullets.size(); j++) {
                if (playerBullets[j].getGlobalBounds().
                    intersects(enemies[i].getGlobalBounds())) {
                    if (enemies[i].getHits() == 2) {
                        scoreGame += 30 * playerBullets[j].getBulletValue();
                    }
                    else scoreGame += 10 * playerBullets[j].getBulletValue();
                    enemyFactory.handleBulletHit(i);
                    if (!playerBullets[j].getBeam()) player.deleteBullet(j);
                }
            }
        }

        orbManager.createOrb();
        orbManager.updateOrbs();
        vector<Orb>& orbs = orbManager.getOrbs();
        for (int i = 0; i < orbs.size(); i++) {
            if (player.getGlobalBounds()[0].intersects(orbs[i].getGlobalBounds())
                || player.getGlobalBounds()[1].intersects(orbs[i].getGlobalBounds())) {
                if (orbs[i].getType() == 0) {
                    player.resetShield();
                    player.setShield();
                }
                else {
                    player.resetPowerUp();
                    (player.setShootingMode(orbs[i].getType()));
                }
                orbManager.deleteOrb(i);
            }
        }

        gameBG1.move(0, 5);
        if (gameBG1.getPosition().y >= height) gameBG1.setPosition(PLAYPOS, -HEIGHT);
        gameBG2.move(0, 5);
        if (gameBG2.getPosition().y >= height) gameBG2.setPosition(PLAYPOS, -HEIGHT);

        for (auto& i : stars) {
            i.commenceMovement();
        }
    }
    else {
        Sleep(1000);
        saveScore(scoreGame);
        gameState = 0;
    }
}

void Game::render()
{
    window.clear();
    window.draw(gameBG1);
    window.draw(gameBG2);
    for (auto& i : stars) {
        i.draw(window);
    }
    for (auto& orb : orbManager.getOrbs()) {
        orb.showOrb(window);
    }
    for (auto& enemy : enemyFactory.getEnemies()) {
        enemy.show(window);
        for (auto& bullet : enemy.getBullets()) {
            bullet.showBullet(window);
        }
    }
    for (auto& bullet : enemyFactory.getTempBullets()) {
        bullet.showBullet(window);
    }
    for (auto& bullet : player.getBullets()) {
        bullet.showBullet(window);
    }
    player.show(window);
    window.draw(frame);
    window.draw(scoreText);
    window.draw(allScore);
    if (gameState == 2) {
        window.draw(youLost);
    }
    window.display();
    Sleep(10);
}

void Game::incrementer()
{
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(10));
        value++;
        cout << value << endl;
    }
}

void Game::resetGame()
{
    value = 0;
    enemyFactory.reset();
    player.reset();
    orbManager.reset();
    scoreGame = 0;
}

bool Game::collisionCheck()
{
    vector<Bullet>& tempBullets = enemyFactory.getTempBullets();
    if (!player.getShield()) {
        for (auto& enemy : enemyFactory.getEnemies()) {
            for (auto& bullet : enemy.getBullets()) {
                if (bullet.getGlobalBounds().intersects(player.getGlobalBounds()[0]) ||
                    bullet.getGlobalBounds().intersects(player.getGlobalBounds()[1])) {
                    saveScore(scoreGame);
                    return true;
                    break;
                }
            }
            if (player.getGlobalBounds()[0].intersects(enemy.getGlobalBounds()) ||
                player.getGlobalBounds()[1].intersects(enemy.getGlobalBounds())) {
                saveScore(scoreGame);
                return true;
                break;
            }
        }
        for (auto& tbullet : tempBullets) {
            if (tbullet.getGlobalBounds().intersects(player.getGlobalBounds()[0]) ||
                tbullet.getGlobalBounds().intersects(player.getGlobalBounds()[1])) {
                return true;
                break;
            }
        }
    }
    return false;
}

void Game::saveScore(int score) {
    scoreTotal += score;
    ofstream scoreFile("score.txt");
    if (scoreFile.is_open()) {
        scoreFile << scoreTotal;
    }
    scoreFile.close();
}

void Game::initTexturedObject(RectangleShape& shape, Texture& texture,
    string path, Vector2f position, Vector2f size)
{
    texture.loadFromFile("./Textures/" + path + ".png");
    shape.setTexture(&texture);
    shape.setSize(size);
    shape.setPosition(position);
}

void Game::loadScore() {
    ifstream scoreFile("score.txt");
    if (scoreFile.is_open()) {
        scoreFile >> scoreTotal;
    }
    scoreFile.close();
}

void Game::initText(Text& text, Font& font, float posX, float posY,
    string str, int sizeFont, int thickness,
    Color menuTextColor, Color outlineColor)
{
    text.setFont(font);
    text.setCharacterSize(sizeFont);
    text.setPosition(posX, posY);
    text.setString(str);
    text.setFillColor(menuTextColor);
    text.setOutlineThickness(thickness);
    text.setOutlineColor(outlineColor);
}
int Game::value = 0;