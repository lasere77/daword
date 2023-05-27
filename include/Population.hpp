#pragma once

#include "Libs.hpp"

class Individual {
    public:
        Individual();
        sf::CircleShape individualSprite;
        virtual void move(std::vector<sf::Vector2i> enemyPosition, std::vector<sf::Vector2i> powerUpPosition) = 0;
        void borderColotion();
        void damage(std::vector<sf::Vector2i> enemyPosition);
        void setFitPoint(); 
        int bonusLife(std::vector<sf::Vector2i> powerUpPosition);
        sf::Text getText();
        
    protected:
        sf::Text text;
        float radius = 10.0f;
        float x = rand() % 1920;
        float y = rand() % 1080;
        float randX = ((float)rand() / RAND_MAX) * 2 - 1;
        float randY = ((float)rand() / RAND_MAX) * 2 - 1;

    private:
        sf::Texture texture;
        float speed = 4.0f;
        int health = 3;
        int fit = 0;
        bool sufferDamage = false;
        int nearestPowerUps;
        int delaySufferDamage;
};