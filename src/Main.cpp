#include "../include/Libs.hpp"
#include "../include/Population.hpp"
#include "../include/BasicIndividual.hpp"
#include "../include/FearfulIndividual.hpp"
#include "../include/Deviantindividual.hpp"
#include "../include/Enemy.hpp"
#include "../include/PowerUp.hpp"
#include "../include/Time.hpp"
#include <iostream>
#include <thread>
#include <vector>
#include <array>
#include <memory>

const int NBINDIVIDUAL = 15;
const int NBENEMY = 15;
const int NBPOWERUP = 5;

/*
*things to review/modify {
*   speed for individuals, 
*   the direction of the basic individual when he goes on a powerUp,
*   reponsives
*}
*/

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "daword", sf::Style::Fullscreen);
    window.setFramerateLimit(90);
    srand(time(nullptr));
    std::array<std::unique_ptr<Individual>, NBINDIVIDUAL> individuals;
    std::generate(individuals.begin(), individuals.end(), []() -> std::unique_ptr<Individual> {
        switch(rand() % 3) {
            case 0:
                return std::make_unique<BasicIndividual>();
            case 1:
                return std::make_unique<FearfulIndividual>();
            case 2: 
                return std::make_unique<DeviantIndividual>();
            default: 
                std::cout << "it didn't make sense this past like that..." << std::endl;
                exit(1);
        }
    });
    Enemy enemys[NBENEMY];
    PowerUp powerUps[NBPOWERUP];

    std::thread timerThread(timer);

    std::vector<sf::Vector2i> enemysPosition;
    std::vector<sf::Vector2i> powerUpPosition;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        //powerUps
        for(int i = 0; i != NBPOWERUP; i++) {
            powerUpPosition.push_back(powerUps[i].getPosition());
        }
        //enemys
        for(int i = 0; i != NBENEMY; i++) {
            enemys[i].move();
            enemys[i].enemySprite.getPosition();
            enemysPosition.push_back(enemys[i].getPosition());
        }
        //individuals
        for(int i = 0; i != NBINDIVIDUAL; i++) {
            individuals[i]->borderColotion();
            individuals[i]->move(enemysPosition, powerUpPosition);
            individuals[i]->damage(enemysPosition);
            individuals[i]->setFitPoint();
            int usedPowerUp = individuals[i]->bonusLife(powerUpPosition);
            if(usedPowerUp >= 0) {
                powerUps[usedPowerUp].generateNewPositon();
            }
        }
        enemysPosition.clear();
        powerUpPosition.clear();

        window.clear();
        for(int i = 0; i != NBINDIVIDUAL; i++) {
            window.draw(individuals[i]->individualSprite);
            window.draw(individuals[i]->getText());
        }
        for(int i = 0; i != NBENEMY; i++) {
            window.draw(enemys[i].enemySprite);
        }
        for(int i = 0; i != NBPOWERUP; i++) {
            window.draw(powerUps[i].powerUpSprite);
        }
        window.display();
    }
    killThread();
    timerThread.join();
    return 0;
}