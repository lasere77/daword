#pragma once

#include "Libs.hpp"

void joinThreadTimeEnemy(); 

class Enemy {
    public:
        Enemy();
        void move();
        sf::CircleShape enemySprite;

    private:
        sf::Texture texture;
        float x = 960;
        float y = 540;
        float randX = ((float)rand() / RAND_MAX) * 2 - 1;
        float randY = ((float)rand() / RAND_MAX) * 2 - 1;
};