#include "../include/Deviantindividual.hpp"
#include <iostream>
#include <math.h>

DeviantIndividual::DeviantIndividual()  {
    std::cout << "a Deviant has been generated." << std::endl;
    individualSprite.setFillColor(sf::Color::Red);
}

DeviantIndividual::DeviantIndividual(int health, float radius, float speed) {
    std::cout << "a baby Deviant has been generated." << std::endl;
    this->health = health;
    this->radius = radius;
    this->speed = speed;
    individualSprite.setFillColor(sf::Color::Red);
}


void DeviantIndividual::move(std::vector<sf::Vector2i> enemyPosition, std::vector<sf::Vector2i> powerUpPosition) {
    if(1 == rand() % 1000) {
        randX = ((float)rand() / RAND_MAX) * 2 - 1;
        randY = ((float)rand() / RAND_MAX) * 2 - 1;
        std::cout << "basic" << std::endl;
    }

    float magnetude = std::sqrt(std::pow(randX, 2) + std::pow(randY, 2));
    if(magnetude != 0) {
        randX/=magnetude;
        randY/=magnetude;
    }

    x = x + randX * speed;
    y = y + randY * speed;
    individualSprite.setPosition(x, y);
    text.setPosition(sf::Vector2(x + 5, y + 15));
}

int DeviantIndividual::getDistanceCanSeePowerUp() {
    return distanceCanSeePowerUp;
}
int DeviantIndividual::getDistanceCanSeeEnemy() {
    return distanceCanSeeEnemy;
}


int DeviantIndividual::getType() {
    return deviant;
}