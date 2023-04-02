#include "../include/Libs.hpp"
#include "../include/Population.hpp"
#include "../include/Enemy.hpp"
#include "../include/PowerUp.hpp"
#include "../include/Time.hpp"
#include <iostream>
#include <thread>

const int NBINDIVIDUAL = 15;
const int NBENEMY = 15;
const int NBPOWERUP = 5;

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "daword", sf::Style::Fullscreen);
    window.setFramerateLimit(90);
    srand(time(nullptr));
    Individual individuals[NBINDIVIDUAL]; 
    Enemy enemys[NBENEMY];
    PowerUp powerUps[NBPOWERUP];

    std::thread timerThread(timer);


    std::vector<sf::Vector2i> enemysPosition;
    std::vector<sf::Vector2i> powerUpPosition;
    for(int i = 0; i != NBENEMY; i++) {
        enemys[i].enemySprite.setPosition(960, 540);
    }
    for(int i = 0; i != NBENEMY; i++) {
        enemys[i].enemySprite.setPosition(500, 200);
    }
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
            individuals[i].move(enemysPosition);
            individuals[i].damage(enemysPosition);
            int usedPowerUp = individuals[i].bonusLife(powerUpPosition);
            if(usedPowerUp >= 0) {
                powerUps[usedPowerUp].generateNewPositon();
            }
        }
        enemysPosition.clear();
        powerUpPosition.clear();

        window.clear();
        for(int i = 0; i != NBINDIVIDUAL; i++) {
            window.draw(individuals[i].individualSprite);
            window.draw(individuals[i].getText());
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