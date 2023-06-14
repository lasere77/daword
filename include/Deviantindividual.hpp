#pragma once 

#include "Population.hpp"

class DeviantIndividual : public Individual {

    public:
        DeviantIndividual();
        DeviantIndividual(int health, float radius, float speed);
        void move(std::vector<sf::Vector2i> enemyPosition, std::vector<sf::Vector2i> powerUpPosition) override;
        int getType() override;
        int getDistanceCanSeePowerUp() override;
        int getDistanceCanSeeEnemy() override;

    private:
        const int distanceCanSeePowerUp = 0;
        const int distanceCanSeeEnemy = 0;
};