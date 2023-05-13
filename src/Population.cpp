#include "../include/Population.hpp"
#include "../include/Time.hpp"
#include <iostream>
#include <math.h>


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


void Individual::borderColotion() {
    if((y > 1080 - radius && randY > 0) || (y < 0 && randY < 0)) {
        randY = randY * -1;
    }else if((x > 1920 - radius && randX > 0) || (x < 0 && randX < 0)) {
        randX = randX * -1;
    }
}

void Individual::damage(std::vector<sf::Vector2i> enemyPosition) {
    if(delaySufferDamage + 3 < getTime()) {
        sufferDamage = false;
    }
    for(int i = 0; i != enemyPosition.size(); i++) {
        if(y >= enemyPosition.at(i).y - 20 && y <= enemyPosition.at(i).y + 20 && x >= enemyPosition.at(i).x - 20 && x <= enemyPosition.at(i).x + 20 && !sufferDamage) {
            sufferDamage = true;
            delaySufferDamage = getTime();
            health--;
            text.setString(std::to_string(health));
        }
    }
}

int Individual::bonusLife(std::vector<sf::Vector2i> powerUpPosition) {
    for(int i = 0; i != powerUpPosition.size(); i++) {
        if(y >= powerUpPosition.at(i).y - 20 && y <= powerUpPosition.at(i).y + 20 && x >= powerUpPosition.at(i).x - 20 && x <= powerUpPosition.at(i).x + 20) {
            health++;
            text.setString(std::to_string(health));
            return i;
        }
    }
    return -1;
}

void Individual::setFitPoint() {
    if(health > 0) {
        fit = getTime();
    }
}

sf::Text Individual::getText() {
    return text;
}