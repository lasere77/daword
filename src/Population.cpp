#include "../include/Population.hpp"
#include "../include/Time.hpp"
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
    //
    int rng = rand() % 3;
    if(rng == 0) {
        fearful = true;
    }else if(rng == 1) {
        basic = true;
    }else { 
        deviant = true;
    }
    
}

void Individual::move() {
    if(individualSprite.getPosition().y > 1080 - individualSprite.getRadius() || individualSprite.getPosition().y < 0) {
        randY = randY * -1;
    }else if(individualSprite.getPosition().x > 1920 - 10.0f || individualSprite.getPosition().x < 0) {
        randX = randX * -1;
    }

    if(basic) {//esquive que les enemy

    }else if(fearful){//esquive tous
        
    }else if(deviant) {
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
            if(1 == rand() % 1000) {
            randX = ((float)rand() / RAND_MAX) * 2 - 1;
            randY = ((float)rand() / RAND_MAX) * 2 - 1;
        }
        x = x + randX;
        y = y + randY;
    }
    individualSprite.setPosition(x + randX, y + randY);
    text.setPosition(sf::Vector2(x + 5, y + 15));
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

void Individual::bonusLife(std::vector<sf::Vector2i> powerUpPosition) {
    for(int i = 0; i != powerUpPosition.size(); i++) {
        if(y >= powerUpPosition.at(i).y - 20 && y <= powerUpPosition.at(i).y + 20 && x >= powerUpPosition.at(i).x - 20 && x <= powerUpPosition.at(i).x + 20) {
            health++;
            text.setString(std::to_string(health));
        }
    }
}

sf::Text Individual::getText() {
    return text;
}