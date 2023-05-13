#include "../include/FearfulIndividual.hpp"
#include <iostream>

FearfulIndividual::FearfulIndividual() {
    std::cout << "a fearfulindividual has been generated." << std::endl;
    individualSprite.setFillColor(sf::Color::Blue);
}

void FearfulIndividual::move(std::vector<sf::Vector2i> enemyPosition, std::vector<sf::Vector2i> powerUpPosition) {
    if(1 == rand() % 1000) {
        randX = ((float)rand() / RAND_MAX) * 2 - 1;
        randY = ((float)rand() / RAND_MAX) * 2 - 1;
        std::cout << "basic" << std::endl;
    }

    for(int i = 0; i != enemyPosition.size(); i++) {
            if(y >= enemyPosition.at(i).y - 60 && y <= enemyPosition.at(i).y + 60 && x >= enemyPosition.at(i).x - 60 && x <= enemyPosition.at(i).x + 60) {
                if(x < 1920 - radius && x < 0 && y < 1080  - radius && y < 0) {
                    if((x < enemyPosition.at(i).x && randX > 0) || (x > enemyPosition.at(i).x && randX < 0)) {
                        randY = randY * -1;
                    }
                }
            }
            if(y >= enemyPosition.at(i).y - 60 && y <= enemyPosition.at(i).y + 60 && x >= enemyPosition.at(i).x - 60 && x <= enemyPosition.at(i).x + 60) {
                if(x < 1920 - radius && x > 0 && y < 1080 - radius && y > 0) {
                    if((y < enemyPosition.at(i).y && randY > 0) || (y > enemyPosition.at(i).y && randY < 0)) {
                        randY = randY * -1;
                    }
                }
            }
        }
        //part dans la direction auposée si il l'individue est trop près du powerUp
        for(int i = 0; i != powerUpPosition.size(); i++) {
            if(y >= powerUpPosition.at(i).y - 60 && y <= powerUpPosition.at(i).y + 60 && x >= powerUpPosition.at(i).x - 60 && x <= powerUpPosition.at(i).x + 60) {
                if(x < 1920 - radius && x < 0 && y < 1080  - radius && y < 0) {
                    if((x < powerUpPosition.at(i).x && randX > 0) || (x > powerUpPosition.at(i).x && randX < 0)) {
                        randY = randY * -1;
                    }
                }
            }
            if(y >= powerUpPosition.at(i).y - 60 && y <= powerUpPosition.at(i).y + 60 && x >= powerUpPosition.at(i).x - 60 && x <= powerUpPosition.at(i).x + 60) {
                if(x < 1920 - radius && x > 0 && y < 1080 - radius && y > 0) {
                    if((y < powerUpPosition.at(i).y && randY > 0) || (y > powerUpPosition.at(i).y && randY < 0)) {
                        randY = randY * -1;
                    }
                }
            }
        }


    x = x + randX;
    y = y + randY;
    individualSprite.setPosition(x, y);
    text.setPosition(sf::Vector2(x + 5, y + 15));
}