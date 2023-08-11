#pragma once

#include "Libs.hpp"

enum IndividualType{
    basic,
    fearful,
    deviant
};


const int MAXHEALTH = 5 + 1;
const int MAXDISTANCECANSEEPOWERUP = 90 + 1;
const int MAXDISTANCECANSENEMY = 90 + 20 + 1;
const float MAXSPEED = 1.05f;
const float MAXRADIUS = 15.0f;

const int MINHEALTH = 1;
const int MINDISTANCECANSEEPOWERUP = 30;
const int MINDISTANCECANSENEMY = 30 - 20;
const float MINSPEED = 0.35;
const float MINRADIUS = 5;


class Individual {
    public:
        Individual();
        sf::CircleShape individualSprite;
        virtual void move(std::vector<sf::Vector2i> enemyPosition, std::vector<sf::Vector2i> powerUpPosition) = 0;
        virtual int getType() = 0;
        virtual int getDistanceCanSeePowerUp() = 0;
        virtual int getDistanceCanSeeEnemy() = 0;
        virtual void makeBaby(int health, float radius, float speed, int distanceCanSeePowerUp, int distanceCanSeeEnemy) = 0;
        virtual void mutation() = 0;
        virtual sf::Text showInfo() = 0;
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
        sf::Text text;
        float radius = 10.0f;
        float speed = 0.7f;
        short int originalHealth = 3; // represents the number of life points at the birth of the individual
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