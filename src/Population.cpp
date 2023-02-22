#include "../include/Population.hpp"
#include <iostream>

Individual::Individual() {
    std::cout << "a individual has been generated." << std::endl;
    if(!texture.loadFromFile("assets/Individual/Texture/Individual.jpg")) {
        std::cout << "error from load Texture..." << std::endl;
    }
    individualSprite.setTexture(&texture);
    individualSprite.setPosition(sf::Vector2(x, y));
    individualSprite.setRadius(radius);
}


void Individual::move() {
    x = individualSprite.getPosition().x;
    y = individualSprite.getPosition().y;
}