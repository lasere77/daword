#include "../include/BasicIndividual.hpp"
#include <iostream>
#include <math.h>

BasicIndividual::BasicIndividual() {
    std::cout << "a Basicindividual has been generated." << std::endl;
    individualSprite.setFillColor(sf::Color::Green);
}

BasicIndividual::BasicIndividual(int health, float radius, float speed, int distanceCanSeePowerUp, int distanceCanSeeEnemy) {
    std::cout << "a Basicindividual has been generated." << std::endl;
    this->health = health;
    this->radius = radius;
    this->speed = speed;
    this->distanceCanSeePowerUp = distanceCanSeePowerUp;
    this->distanceCanSeeEnemy = distanceCanSeeEnemy;
    individualSprite.setFillColor(sf::Color::Green);
}

void BasicIndividual::move(std::vector<sf::Vector2i> enemyPosition, std::vector<sf::Vector2i> powerUpPosition) {
    if(1 == rand() % 1000) {
        randX = ((float)rand() / RAND_MAX) * 2 - 1;
        randY = ((float)rand() / RAND_MAX) * 2 - 1;
        std::cout << "basic" << std::endl;
    }

    
    //go to the powerUp
    if(!powerUpPosition.empty() && health < 5) {
        sf::Vector2i closestPowerUp;
        float closestDistance = std::numeric_limits<float>::max();
        float distancePowerUp;
        // find the most closest power-up 
        for (const auto& powerUp : powerUpPosition) {
            distancePowerUp = std::sqrt(std::pow(powerUp.x - x, 2) + std::pow(powerUp.y - y, 2));
            if (distancePowerUp <= distanceCanSeePowerUp) {
                closestPowerUp = powerUp;
                closestDistance = distancePowerUp;
                break;
            }
        }
        
        if(distancePowerUp <= distanceCanSeePowerUp) {
            randX = closestPowerUp.x - x;
            randY = closestPowerUp.y - y;
        }
    }

    //escape to enemy
    for(int i = 0; i != enemyPosition.size(); i++) {
        if(y >= enemyPosition.at(i).y - distanceCanSeeEnemy && y <= enemyPosition.at(i).y + distanceCanSeeEnemy && x >= enemyPosition.at(i).x - distanceCanSeeEnemy && x <= enemyPosition.at(i).x + distanceCanSeeEnemy) {
            if(x < 1920 - radius && x > 0 && y < 1080 - radius && y > 0) {
                if((x < enemyPosition.at(i).x && randX > 0) || (x > enemyPosition.at(i).x && randX < 0)) {
                    randX = randX * -1;
                }
                if((y < enemyPosition.at(i).y && randY > 0) || (y > enemyPosition.at(i).y && randY < 0)) {
                    randY = randY * -1;
                }
            }
        }
    }


    float magnetude = std::sqrt(std::pow(randX, 2) + std::pow(randY, 2));
    if(magnetude != 0) {
        randX/=magnetude;
        randY/=magnetude;
    }

    x += randX * speed;
    y += randY * speed;
    individualSprite.setPosition(x, y);
    text.setPosition(sf::Vector2(x + 5, y + 15));
}


int BasicIndividual::getDistanceCanSeePowerUp() {
    return distanceCanSeePowerUp;
}
int BasicIndividual::getDistanceCanSeeEnemy() {
    return distanceCanSeeEnemy;
}

int BasicIndividual::getType() {
    return basic;
}