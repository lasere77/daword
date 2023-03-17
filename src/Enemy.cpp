#include "../include/Enemy.hpp"
#include "../include/Time.hpp"
#include <iostream>

Enemy::Enemy() {
    std::cout << "a enemy has been generated." << std::endl;
    if(!texture.loadFromFile("assets/Enemy/Texture/Enemy.jpg")) {
        std::cout << "error from load Texture..." << std::endl;
    }
    enemySprite.setTexture(&texture);
    enemySprite.setPosition(sf::Vector2(x, y));
    enemySprite.setRadius(10.0f);
}

void Enemy::move() {
    if(enemySprite.getPosition().y > 1080 - enemySprite.getRadius() || enemySprite.getPosition().y < 0) {
        randY = randY * -1;
    }else if(enemySprite.getPosition().x > 1920 - 10.0f || enemySprite.getPosition().x < 0) {
        randX = randX * -1;
    }
    /*
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        y--;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        y++;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        x++;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        x--;
    }
    */
    if(1 == rand() % 1000) {
        randX = ((float)rand() / RAND_MAX) * 2 - 1;
        randY = ((float)rand() / RAND_MAX) * 2 - 1;
    }
    x = x + randX;
    y = y + randY;
    enemySprite.setPosition(x + randX, y + randY);
}

sf::Vector2i Enemy::getPosition() {
    return sf::Vector2i(x, y);
}