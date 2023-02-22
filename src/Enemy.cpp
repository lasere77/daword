#include "../include/Enemy.hpp"
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
    y = enemySprite.getPosition().y + rand() % 2;
    x = enemySprite.getPosition().x + rand() % 2;

    enemySprite.setPosition(x, y);
}