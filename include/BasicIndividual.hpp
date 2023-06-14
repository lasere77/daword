#pragma once
#include "Population.hpp"


class BasicIndividual : public Individual {

    public:
        BasicIndividual();
        BasicIndividual(int health, float radius, float speed, int distanceCanSeePowerUp, int distanceCanSeeEnemy);
        void move(std::vector<sf::Vector2i> enemyPosition, std::vector<sf::Vector2i> powerUpPosition) override;
        int getType() override;
        int getDistanceCanSeePowerUp() override;
        int getDistanceCanSeeEnemy() override;

    private:
        int distanceCanSeeEnemy = 60;
        int distanceCanSeePowerUp = 60;
};