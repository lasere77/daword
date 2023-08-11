#pragma once
#include "Population.hpp"


class BasicIndividual : public Individual {

    public:
        BasicIndividual();
        void move(std::vector<sf::Vector2i> enemyPosition, std::vector<sf::Vector2i> powerUpPosition) override;
        void makeBaby(int health, float radius, float speed, int distanceCanSeePowerUp, int distanceCanSeeEnemy) override;
        void mutation() override;
        int getType() override;
        int getDistanceCanSeePowerUp() override;
        int getDistanceCanSeeEnemy() override;
        sf::Text showInfo() override;

    private:
        int distanceCanSeeEnemy = 60;
        int distanceCanSeePowerUp = 60;
};