#pragma once
#include <SFML/Graphics.hpp>
#include "Header.h"
#include "Config.h"

class Star {
private:
    RectangleShape star;
    static Texture starT;
    Clock clock;
    bool waiting = true;
public:
    Star();

    void commenceMovement();

    void draw(RenderWindow& window);
};