#include "../include/PowerUp.hpp"
#include <iostream>

PowerUp::PowerUp() {
    std::cout << "a PowerUp has been generated." << std::endl;
    if(!texture.loadFromFile("assets/PowerUp/Texture/PowerUp.png")) {
        std::cout << "error from load Texture..." << std::endl;
    }
    powerUpSprite.setTexture(&texture);
    powerUpSprite.setPosition(sf::Vector2(x, y));
    powerUpSprite.setRadius(10.0f);
}

void PowerUp::generateNewPositon() {
    x = rand() % 1921;
    y = rand() % 1081;
    powerUpSprite.setPosition(sf::Vector2(x, y));
}

sf::Vector2i PowerUp::getPosition() {
    return sf::Vector2i(x, y);
}