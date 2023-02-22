#pragma once

#include "Libs.hpp"

class Enemy {
    public:
        Enemy();
        void move();
        sf::CircleShape enemySprite;

    private:
        sf::Texture texture;
        float x;
        float y;
};