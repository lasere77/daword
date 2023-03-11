#include "../include/Population.hpp"
#include <iostream>

sf::Font font;

Individual::Individual() {
    std::cout << "a individual has been generated." << std::endl;
    if(!texture.loadFromFile("assets/Individual/Texture/Individual.jpg")) {
        std::cout << "error from load Texture..." << std::endl;
    }
    individualSprite.setTexture(&texture);
    individualSprite.setPosition(sf::Vector2(x, y));
    individualSprite.setRadius(radius);
    if(!font.loadFromFile("assets/font/poppins.ttf")) {
        std::cerr << "error to load font please check your assets" << std::endl;
    }
    text.setFont(font);
    text.setPosition(sf::Vector2(x + 5, y + 15));
    text.setString(std::to_string(health));
    text.setCharacterSize(15);
}

void Individual::move(std::vector<sf::Vector2i> enemyPosition) {
    if(individualSprite.getPosition().y > 1080 - individualSprite.getRadius() || individualSprite.getPosition().y < 0) {
        randY = randY * -1;
    }else if(individualSprite.getPosition().x > 1920 - 10.0f || individualSprite.getPosition().x < 0) {
        randX = randX * -1;
    }

    if(basic) {
        
    }else if(fearful){
        
    }else if(deviant) {

    }

    if(1 == rand() % 1000) {
        randX = ((float)rand() / RAND_MAX) * 2 - 1;
        randY = ((float)rand() / RAND_MAX) * 2 - 1;
        std::cout << ((float)rand() / RAND_MAX) * 2 - 1 << std::endl;
    }
    x = x + randX;
    y = y + randY;
    individualSprite.setPosition(x + randX, y + randY);
    text.setPosition(sf::Vector2(x + 5, y + 15));
}

sf::Text Individual::getText() {
    return text;
}