#include "../include/Libs.hpp"
#include "../include/Entity.hpp"
#include "../include/BasicIndividual.hpp"
#include "../include/FearfulIndividual.hpp"
#include "../include/Deviantindividual.hpp"
#include "../include/Time.hpp"

#include <iostream>
#include <vector>
#include <thread>


void setTimeur();

unsigned int minute = 0;
unsigned int oldSeconde = 0;
unsigned int seconde = 0;


/*
*things to review/modify {
*   speed for individuals, reponsives
*}
*/

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "daword", sf::Style::Fullscreen);
    window.setFramerateLimit(90);
    srand(time(nullptr));
    std::generate(entity::individuals.begin(), entity::individuals.end(), []() -> std::unique_ptr<Individual> {
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

    std::thread timerThread(timer);
    sf::Font font;

    if(!font.loadFromFile("assets/font/poppins.ttf")) {
        std::cerr << "error from load font please check your assets" << std::endl;
    }
    sf::Text generalTime;
    generalTime.setFont(font);
    generalTime.setPosition(960, 0);
    generalTime.setCharacterSize(15);

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
            powerUpPosition.push_back(entity::powerUps[i].getPosition());
        }
        //enemys
        for(int i = 0; i != NBENEMY; i++) {
            entity::enemys[i].move();
            entity::enemys[i].enemySprite.getPosition();
            enemysPosition.push_back(entity::enemys[i].getPosition());
        }
        //individuals
        for(int i = 0; i != NBINDIVIDUAL; i++) {
            if(entity::individuals[i]->isAlive) {
                entity::individuals[i]->borderColotion();
                entity::individuals[i]->move(enemysPosition, powerUpPosition);
                entity::individuals[i]->damage(enemysPosition);
                entity::individuals[i]->setFitPoint();
                entity::individuals[i]->checkHealth();
                int usedPowerUp = entity::individuals[i]->bonusLife(powerUpPosition);
                if(usedPowerUp >= 0) {
                    entity::powerUps[usedPowerUp].generateNewPositon();
                }
            }else {

            }
        }
        enemysPosition.clear();
        powerUpPosition.clear();

        setTimeur();
        generalTime.setString("[ " + std::to_string(minute) + " ; " + std::to_string(seconde - 60 * minute) + " ]");

        window.clear();
        window.draw(generalTime);
        for(int i = 0; i != NBINDIVIDUAL; i++) {
            window.draw(entity::individuals[i]->individualSprite);
            window.draw(entity::individuals[i]->getText());
        }
        for(int i = 0; i != NBENEMY; i++) {
            window.draw(entity::enemys[i].enemySprite);
        }
        for(int i = 0; i != NBPOWERUP; i++) {
            window.draw(entity::powerUps[i].powerUpSprite);
        }
        window.display();
    }
    killThread();
    timerThread.join();
    return 0;
}


void setTimeur() {
    seconde = getTime();
    if(seconde % 60 == 0 && oldSeconde != seconde && seconde != 0) {
        oldSeconde = seconde;
        minute+=1;
    }
    std::cout << "old seconde: " << oldSeconde << std::endl;
    std::cout << "seconde: " << seconde << std::endl;
    std::cout << "minute: " << minute << std::endl;
}