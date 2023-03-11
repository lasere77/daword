#pragma once

#include "Libs.hpp"

class PowerUp {
    public:
        PowerUp();
        sf::CircleShape powerUpSprite;
        sf::Vector2i getPosition();

    private:
        sf::Texture texture;
        float x = rand() % 1921;
        float y = rand() % 1081;
};