#pragma once

#include "Libs.hpp"

class Individual {
    public:
        Individual();
        sf::CircleShape individualSprite;
        void move(std::vector<sf::Vector2i> enemyPosition);
        sf::Text getText();

    private:
        sf::Texture texture;
        sf::Text text;
        float radius = 10.0f;
        float speed = 4.0f;
        int health = 3;
        int fit = 0;
        bool basic;
        bool fearful;
        bool deviant;
        float x;
        float y;
        float randX = ((float)rand() / RAND_MAX) * 2 - 1;
        float randY = ((float)rand() / RAND_MAX) * 2 - 1;
};