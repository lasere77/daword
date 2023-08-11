#include "../include/Deviantindividual.hpp"
#include <iostream>
#include <math.h>
#include <random>

DeviantIndividual::DeviantIndividual()  {
    std::cout << "a Deviant has been generated." << std::endl;
    individualSprite.setFillColor(sf::Color::Red);
}

void DeviantIndividual::makeBaby(int health, float radius, float speed, int distanceCanSeePowerUp, int distanceCanSeeEnemy) {
    std::cout << "a baby Deviant has been generated." << std::endl;
    int nbG = std::rand() % 3; //number of genes transmitted by the father
    int randomG; //the id of the genes to modify or not to modify (genes coming from the father)
    std::cout << "rng: " << nbG << std::endl;
    switch (nbG) {
        case 0:
            std::cout << "no mutations" << std::endl;
            break;
        case 1:
            randomG = rand() % 3;
            switch (randomG) { //modify the genes corresponding to randomG
                case 0: // health are modified
                    std::cout << "health" << std::endl;
                    this->originalHealth = health;
                    break;
                case 1: // radius are modified
                    std::cout << "radius" << std::endl;
                    this->radius = radius;
                    break;
                case 2: // speed are modified
                    std::cout << "speed" << std::endl;
                    this->speed = speed;
                    break;
                default:
                    std::cout << "mutation switch 2 error [case 1]" << std::endl;
                    exit(1);
                    break;
            }
            break;
        case 2: // modify all the genes except those corresponding to randomG
            randomG = rand() % 3;
            switch (randomG) {
                case 0: // raduis and speed are modified
                    std::cout << "radius" << std::endl;
                    std::cout << "speed" << std::endl;
                    this->radius = radius;
                    this->speed = speed;
                    break;
                case 1: // health and speed are modified
                    std::cout << "health" << std::endl;
                    std::cout << "speed" << std::endl;
                    this->originalHealth = health;
                    this->speed = speed;
                    break;
                case 2: // health and radius are modified
                    std::cout << "health" << std::endl;
                    std::cout << "radius" << std::endl;
                    this->originalHealth = health;
                    this->radius = radius;
                    break;
                default:
                    std::cout << "mutation switch 2 error [case 2]" << std::endl;
                    exit(1);
                    break;
                }
                break;
        default:
            std::cout << "mutation main switch" << std::endl;
            exit(1);
            break;
    }
    this->health = originalHealth;
    isAlive = true;
    text.setString(std::to_string(health));
    individualSprite.setFillColor(sf::Color::Red);
}


void DeviantIndividual::mutation() {
    std::random_device rd;
    std::mt19937 gen(rd());
    int randomG = rand() % 3;
    switch (randomG) {// modification of a single gene
        case 0: { // health
            std::uniform_int_distribution<int> dis(MINHEALTH, MAXHEALTH);// determine the bounds of the random numbers (int)
            int randomHealth = dis(gen);
            this->originalHealth = randomHealth;
            this->health = originalHealth;
            std::cout << "mutation [HEALTH] " << randomHealth << std::endl;
            }
            text.setString(std::to_string(health));
            break;
        case 1: { // radius
            std::uniform_real_distribution<float> dis(MINRADIUS, MAXRADIUS);// determine the bounds of the random numbers (float)
            float randomRadius = dis(gen);
            this->radius = randomRadius;
            std::cout << "mutation [RADIUS] " << randomRadius << std::endl;
            }
            individualSprite.setRadius(radius);
            break;
        case 2: { // speed
            std::uniform_real_distribution<float> dis(MINSPEED, MAXSPEED);
            float randomSpeed = dis(gen);
            this->speed = randomSpeed;
            std::cout << "mutation [SPEED] " << randomSpeed << std::endl;
            }
            break;
        default:
            std::cout << "switch error mutation" << std::endl;
            exit(1);
            break;
    }
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


sf::Text DeviantIndividual::showInfo() {
    sf::Text info;
    info.setFillColor(sf::Color::Red);
    info.setString("health: " + std::to_string(originalHealth) + " speed: " + std::to_string(speed) + " radius: " + std::to_string(radius)); 
    return info;
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