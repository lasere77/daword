#include "../include/Deviantindividual.hpp"
#include <iostream>

DeviantIndividual::DeviantIndividual()  {
    std::cout << "a Deviant has been generated." << std::endl;
    individualSprite.setFillColor(sf::Color::Red);
}


void DeviantIndividual::move(std::vector<sf::Vector2i> enemyPosition, std::vector<sf::Vector2i> powerUpPosition) {
    if(1 == rand() % 1000) {
        randX = ((float)rand() / RAND_MAX) * 2 - 1;
        randY = ((float)rand() / RAND_MAX) * 2 - 1;
        std::cout << "basic" << std::endl;
    }


    x = x + randX;
    y = y + randY;
    individualSprite.setPosition(x, y);
    text.setPosition(sf::Vector2(x + 5, y + 15));
}