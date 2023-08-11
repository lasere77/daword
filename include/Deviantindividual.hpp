#pragma once 

#include "Population.hpp"

class DeviantIndividual : public Individual {

    public:
        DeviantIndividual();
        void move(std::vector<sf::Vector2i> enemyPosition, std::vector<sf::Vector2i> powerUpPosition) override;
        void makeBaby(int health, float radius, float speed, int distanceCanSeePowerUp, int distanceCanSeeEnemy) override;
        void mutation() override;
        int getType() override;
        int getDistanceCanSeePowerUp() override;
        int getDistanceCanSeeEnemy() override;
        sf::Text showInfo() override;

    private:
        const int distanceCanSeePowerUp = 0;
        const int distanceCanSeeEnemy = 0;
};