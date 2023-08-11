#include "../include/Population.hpp"
#include "../include/Time.hpp"
#include <iostream>
#include <math.h>


sf::Font font;

Individual::Individual() {
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
        if(y >= enemyPosition.at(i).y - radius * 2 && y <= enemyPosition.at(i).y + radius && x >= enemyPosition.at(i).x - radius * 2 && x <= enemyPosition.at(i).x + radius && !sufferDamage) {
            sufferDamage = true;
            delaySufferDamage = getTime();
            health--;
            text.setString(std::to_string(health));
        }
    }
}

void Individual::resetLife() {
    std::cout << "the father of the new generation has regained his strength." << std::endl;
    health = originalHealth;
    isAlive = true;
    text.setString(std::to_string(health));
    individualSprite.setFillColor(sf::Color::Cyan);
}

int Individual::bonusLife(std::vector<sf::Vector2i> powerUpPosition) {
    for(int i = 0; i != powerUpPosition.size(); i++) {
        if(y >= powerUpPosition.at(i).y - radius * 2 && y <= powerUpPosition.at(i).y + radius && x >= powerUpPosition.at(i).x - radius * 2 && x <= powerUpPosition.at(i).x + radius && health < 5) {
            health++;
            text.setString(std::to_string(health));
            return i;
        }
    }
    return -1;
}

int Individual::getOriginalHealth() {
    return originalHealth;
}
float Individual::getRadius() {
    return radius;
}
float Individual::getSpeed() {
    return speed;
}

void Individual::checkHealth() {
    if(health <= 0) {
        isAlive = false;
        std::cout << "he is dead" << std::endl;
    }
}

void Individual::setFitPoint() {
    if(health > 0) {
        fit = getTime();
    }
}

int Individual::getFitPoint() {
    return fit;
}

sf::Text Individual::getText() {
    return text;
}