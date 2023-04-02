#pragma once

#include "Libs.hpp"

class Individual {
    public:
        Individual();
        sf::CircleShape individualSprite;
        void move(std::vector<sf::Vector2i> enemyPosition, std::vector<sf::Vector2i> powerUpPosition);
        void damage(std::vector<sf::Vector2i> enemyPosition);
        int bonusLife(std::vector<sf::Vector2i> powerUpPosition);
        sf::Text getText();

    private:
        sf::Texture texture;
        sf::Text text;
        float radius = 10.0f;
        float speed = 4.0f;
        int health = 3;
        int fit = 0;
        bool basic = false;
        bool fearful = false;
        bool deviant = false;
        bool sufferDamage = false;
        int delaySufferDamage;
        float x = 500;
        float y = 200;
        float randX = ((float)rand() / RAND_MAX) * 2 - 1;
        float randY = ((float)rand() / RAND_MAX) * 2 - 1;
};