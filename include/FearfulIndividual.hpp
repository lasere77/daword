#pragma once 

#include "Population.hpp"

class FearfulIndividual : public Individual {

    public:
        FearfulIndividual();
        FearfulIndividual(int health, float radius, float speed, int distanceCanSeePowerUp, int distanceCanSeeEnemy);
        void move(std::vector<sf::Vector2i> enemyPosition, std::vector<sf::Vector2i> powerUpPosition) override;
        int getType() override;
        int getDistanceCanSeePowerUp() override;
        int getDistanceCanSeeEnemy() override;

    private:
        int distanceCanSeePowerUp = 60;
        int distanceCanSeeEnemy = 60;
};