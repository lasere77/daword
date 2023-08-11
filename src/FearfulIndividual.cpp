#include "../include/FearfulIndividual.hpp"
#include <iostream>
#include <math.h>
#include <random>

FearfulIndividual::FearfulIndividual() {
    std::cout << "a fearfulindividual has been generated." << std::endl;
    individualSprite.setFillColor(sf::Color::Blue);
}


//health changes are made on orignigalHealth and then on health
void FearfulIndividual::makeBaby(int health, float radius, float speed, int distanceCanSeePowerUp, int distanceCanSeeEnemy) {
    std::cout << "a baby fearfulindividual has been generated." << std::endl;
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
        case 2: // modify [health, 1, 4] [radius, 2, 3] [speed, 0, 4] [dp, 0, 3] [de, 1, 2] They are evenly distributed
            randomG = rand() % 5;
            switch (randomG) {
                case 0: // distanceCanSeePowerUp and speed are modified
                    std::cout << "distanceCanSeePowerUp" << std::endl;
                    std::cout << "speed" << std::endl;
                    this->distanceCanSeePowerUp = distanceCanSeePowerUp;
                    this->speed = speed;
                    break;
                case 1: // health and speed are modified
                    std::cout << "health" << std::endl;
                    std::cout << "distanceCanSeeEnemy" << std::endl;
                    this->originalHealth = health;
                    this->distanceCanSeeEnemy = distanceCanSeeEnemy;
                    break;
                case 2: // health and radius are modified
                    std::cout << "radius" << std::endl;
                    std::cout << "distanceCanSeeEnemy" << std::endl;
                    this->radius = radius;
                    this->distanceCanSeeEnemy = distanceCanSeeEnemy;
                    break;
                case 3: // raduis and distanceCanSeeenemy are modified
                    std::cout << "radius" << std::endl;
                    std::cout << "distanceCanSeeEnemy" << std::endl;
                    this->distanceCanSeeEnemy = distanceCanSeeEnemy;
                    this->radius = radius;
                    break;
                case 4: // health and speed are modified
                    std::cout << "health" << std::endl;
                    std::cout << "speed" << std::endl;
                    this->originalHealth = health;
                    this->speed = speed;
                    break;
                default:
                    std::cout << "mutation switch 2 error [case 2]" << std::endl;
                    exit(1);
                    break;
                }
                break;
        default:
            std::cout << "mutation main switch error" << std::endl;
            exit(1);
            break;
    }
    this->health = originalHealth;
    individualSprite.setFillColor(sf::Color::Blue);
    isAlive = true;
    text.setString(std::to_string(health));
}

//health changes are made on orignigalHealth and then on health
void FearfulIndividual::mutation() {
    std::random_device rd;
    std::mt19937 gen(rd());
    int randomG = rand() % 5;
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
        case 3: { // distance can see power up
                std::uniform_int_distribution<int> dis(MINDISTANCECANSEEPOWERUP, MAXDISTANCECANSEEPOWERUP);// determine the bounds of the random numbers (int)
                int randomDistanceCanSeePowerUp = dis(gen);
                this->distanceCanSeePowerUp = randomDistanceCanSeePowerUp;
                std::cout << "mutation [DISTANCEPOWERUP] " << randomDistanceCanSeePowerUp << std::endl;
            }
            break;
        case 4: { // distance can see enemy
                std::uniform_int_distribution<int> dis(MINDISTANCECANSENEMY, MAXDISTANCECANSENEMY);
                int randomDistanceCanSeeEnemy = dis(gen);
                this->distanceCanSeeEnemy = randomDistanceCanSeeEnemy;
                std::cout << "mutation [DISTANCEENEMY]: " << randomDistanceCanSeeEnemy << std::endl;
            }
            break;
        default:
            std::cout << "switch error mutation" << std::endl;
            exit(1);
            break;
    }
}

void FearfulIndividual::move(std::vector<sf::Vector2i> enemyPosition, std::vector<sf::Vector2i> powerUpPosition) {
    if(1 == rand() % 1000) {
        randX = ((float)rand() / RAND_MAX) * 2 - 1;
        randY = ((float)rand() / RAND_MAX) * 2 - 1;
        std::cout << "basic" << std::endl;
    }

    //goes in the direction posed if the individual is too close to the enemy
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
    //goes in the direction posed if the individual is too close to the powerUp
    for(int i = 0; i != powerUpPosition.size(); i++) {
        if(y >= powerUpPosition.at(i).y - distanceCanSeePowerUp && y <= powerUpPosition.at(i).y + distanceCanSeePowerUp && x >= powerUpPosition.at(i).x - distanceCanSeePowerUp && x <= powerUpPosition.at(i).x + distanceCanSeePowerUp) {
            if(x < 1920 - radius && x > 0 && y < 1080 - radius && y > 0) {
                if((x < powerUpPosition.at(i).x && randX > 0) || (x > powerUpPosition.at(i).x && randX < 0)) {
                    randX = randX * -1;
                }
                if((y < powerUpPosition.at(i).y && randY > 0) || (y > powerUpPosition.at(i).y && randY < 0)) {
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

    x = x + randX * speed;
    y = y + randY * speed;
    individualSprite.setPosition(x, y);
    text.setPosition(sf::Vector2(x + 5, y + 15));
}

sf::Text FearfulIndividual::showInfo() {
    sf::Text info;
    info.setFillColor(sf::Color::Blue);
    info.setString("health: " + std::to_string(originalHealth) + " speed: " + std::to_string(speed) + " radius: " + std::to_string(radius) + " canSeeEnemy: " + std::to_string(distanceCanSeeEnemy) + " canSeePowerUp: " + std::to_string(distanceCanSeePowerUp)); 
    return info;
}

int FearfulIndividual::getDistanceCanSeePowerUp() {
    return distanceCanSeePowerUp;
}
int FearfulIndividual::getDistanceCanSeeEnemy() {
    return distanceCanSeeEnemy;
}

int FearfulIndividual::getType() {
    return fearful;
}