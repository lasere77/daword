#pragma once

#include "Libs.hpp"

class Individual {
    public:
        Individual();
        sf::CircleShape individualSprite;
        virtual void move(std::vector<sf::Vector2i> enemyPosition, std::vector<sf::Vector2i> powerUpPosition) = 0;
        virtual int getType() = 0;
        virtual int getDistanceCanSeePowerUp() = 0;
        virtual int getDistanceCanSeeEnemy() = 0;
        void borderColotion();
        void damage(std::vector<sf::Vector2i> enemyPosition);
        void resetLife();
        void setFitPoint();
        int getFitPoint();
        int bonusLife(std::vector<sf::Vector2i> powerUpPosition);
        void checkHealth();
        sf::Text getText();
        int getOriginalHealth();
        float getRadius();
        float getSpeed();
        bool isAlive = true;
        
    protected:
        enum IndividualType{
            basic,
            fearful,
            deviant
        };
        sf::Text text;
        float radius = 10.0f; 
        float speed = 0.7f;
        short int originalHealth = 3;
        short int health = originalHealth;
        float x = rand() % 1920;
        float y = rand() % 1080;
        float randX = ((float)rand() / RAND_MAX) * 2 - 1;
        float randY = ((float)rand() / RAND_MAX) * 2 - 1;

    private:
        sf::Texture texture;
        unsigned int fit = 0;
        bool sufferDamage = false;
        int nearestPowerUps;
        int delaySufferDamage;
};