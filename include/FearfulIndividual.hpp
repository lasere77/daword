#pragma once 

#include "Population.hpp"

class FearfulIndividual : public Individual {

    public:
        FearfulIndividual();
        void makeBaby(int health, float radius, float speed, int distanceCanSeePowerUp, int distanceCanSeeEnemy) override;
        void mutation() override;
        void move(std::vector<sf::Vector2i> enemyPosition, std::vector<sf::Vector2i> powerUpPosition) override;
        int getType() override;
        int getDistanceCanSeePowerUp() override;
        int getDistanceCanSeeEnemy() override;
        sf::Text showInfo() override;

    private:
        int distanceCanSeePowerUp = 60;
        int distanceCanSeeEnemy = 60;
};