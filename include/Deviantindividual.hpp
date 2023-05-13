#pragma once 

#include "Population.hpp"

class DeviantIndividual : public Individual {

    public:
        DeviantIndividual();
        void move(std::vector<sf::Vector2i> enemyPosition, std::vector<sf::Vector2i> powerUpPosition) override;
        
};