#include "Game.h"
#include "Config.h"
#include "Header.h"
#include "GameMenu.h"

int main() {
    srand(time(NULL));
    Game game;
    game.run();
}