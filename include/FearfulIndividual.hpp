#pragma once 

#include "Population.hpp"

class FearfulIndividual : public Individual {

    public:
        FearfulIndividual();
        void move(std::vector<sf::Vector2i> enemyPosition, std::vector<sf::Vector2i> powerUpPosition) override;
};