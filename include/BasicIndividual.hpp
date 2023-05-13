#pragma once
#include "Population.hpp"


class BasicIndividual : public Individual {

    public:
        BasicIndividual();
        void move(std::vector<sf::Vector2i> enemyPosition, std::vector<sf::Vector2i> powerUpPosition) override;
};