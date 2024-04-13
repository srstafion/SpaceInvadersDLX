#include "Star.h"

Star::Star()
{
    starT.loadFromFile("./Textures/star.png");
    star.setTexture(&starT);
    star.setSize(Vector2f(153, 138));
    star.setPosition(PLAYPOS + PLAYWIDTH, random(-400, 50));
}

void Star::commenceMovement()
{
    if (!waiting && star.getPosition().x <= -150) {
        waiting = true;
        clock.restart();
    }
    if (waiting) {
        if (clock.getElapsedTime().asMilliseconds() >= random(2000, 7000)) {
            waiting = false;
            star.setPosition(PLAYPOS + PLAYWIDTH, random(-400, 50));
        }
    }
    else {
        star.move(-40, 40);
    }
}

void Star::draw(RenderWindow& window)
{
    window.draw(star);
}
Texture Star::starT;