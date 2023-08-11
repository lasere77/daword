#include "../include/Libs.hpp"
#include "../include/Entity.hpp"
#include "../include/BasicIndividual.hpp"
#include "../include/FearfulIndividual.hpp"
#include "../include/Deviantindividual.hpp"
#include "../include/Time.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <unordered_map>

sf::Text nbInstance;

std::string setTimeur();
void crossover(std::unordered_map<int, int> individualFit);  //make baby and mutation

unsigned int nbGeneration = 0;
unsigned short int nbDeadIndividuals = 0;

/*
* probable bug/bug {
*    hitbox,
*    the basic and Fearful dont have the same functioning as the Devient for make a baby(Devient have good process);
*}
*/

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "daword", sf::Style::Fullscreen);
    window.setFramerateLimit(90);
    srand(time(nullptr));
    std::generate(entity::individuals.begin(), entity::individuals.end(), []() -> std::unique_ptr<Individual> {
        switch(rand() % 5) {
            case 0: case 1:
                return std::make_unique<BasicIndividual>();
            case 2: case 3:
                return std::make_unique<FearfulIndividual>();
            case 4: 
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

    //nbInstance
    nbInstance.setFont(font);
    nbInstance.setPosition(0, 0);
    nbInstance.setCharacterSize(15);
    nbInstance.setString("generation: " + std::to_string(nbGeneration));

    std::unordered_map<int, int> individualFit;
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
                nbDeadIndividuals++;
                individualFit.insert({i, entity::individuals[i]->getFitPoint()});
                if(nbDeadIndividuals == NBINDIVIDUAL) {
                    //std::cout << "STOP INSTANCE !!!!! [ " << minute << " ; " <<  seconde - 60 * minute << " ]" << std::endl;
                    for(int j = 0; j != individualFit.size(); j++) {
                        std::cout << j << " : " << individualFit.at(j) << std::endl;
                    }
                    crossover(individualFit);
                }
           }
        }
        nbDeadIndividuals = 0;
        individualFit.clear();
        enemysPosition.clear();
        powerUpPosition.clear();

        generalTime.setString("[ "  + setTimeur() + " ]");

        window.clear();
        window.draw(nbInstance);
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            for(int i = 0; i != NBINDIVIDUAL; i++) {
                sf::Text IndividualInfo = entity::individuals[i]->showInfo();
                IndividualInfo.setFont(font);
                IndividualInfo.setPosition(0, 60 * i + 40); //pay attention to the number of individuals. If you change it
                IndividualInfo.setCharacterSize(15);
                window.draw(IndividualInfo);
            }
        }
        window.display();
    }
    killThread();
    timerThread.join();
    return 0;
}


void crossover(std::unordered_map<int, int> individualFit) {
    nbGeneration++;
    nbInstance.setString("generation: " + std::to_string(nbGeneration));
    int mostFitIndividual = 0; //he fit
    int mostFitIndividualID = 0; //he id
    for (int i = 0; i != individualFit.size(); i++) {
        if(individualFit.at(i) >= mostFitIndividual) {
            mostFitIndividual = individualFit.at(i);
            mostFitIndividualID = i;
        }
    }
    //regener the best Individual for the new generation.
    entity::individuals[mostFitIndividualID]->resetLife();

    //the mutation is done on all the individuals except on the best.

    // make baby and make their mutation
    for(int i = 0; i !=individualFit.size(); i++) {
        if(i != mostFitIndividualID) {
            switch(entity::individuals[i]->getType()) {
                case IndividualType::basic:
                    entity::individuals[i]->makeBaby(entity::individuals[mostFitIndividualID]->getOriginalHealth(), entity::individuals[mostFitIndividualID]->getRadius(), entity::individuals[mostFitIndividualID]->getSpeed(), entity::individuals[mostFitIndividualID]->getDistanceCanSeePowerUp(), entity::individuals[mostFitIndividualID]->getDistanceCanSeeEnemy());
                    entity::individuals[i]->mutation();
                    break;
                case IndividualType::fearful:
                    entity::individuals[i]->makeBaby(entity::individuals[mostFitIndividualID]->getOriginalHealth(), entity::individuals[mostFitIndividualID]->getRadius(), entity::individuals[mostFitIndividualID]->getSpeed(), entity::individuals[mostFitIndividualID]->getDistanceCanSeePowerUp(), entity::individuals[mostFitIndividualID]->getDistanceCanSeeEnemy());
                    entity::individuals[i]->mutation();
                    break;
                case IndividualType::deviant:
                    entity::individuals[i]->makeBaby(entity::individuals[mostFitIndividualID]->getOriginalHealth(), entity::individuals[mostFitIndividualID]->getRadius(), entity::individuals[mostFitIndividualID]->getSpeed(), entity::individuals[mostFitIndividualID]->getDistanceCanSeePowerUp(), entity::individuals[mostFitIndividualID]->getDistanceCanSeeEnemy());
                    entity::individuals[i]->mutation();
                    break;
                default:
                    std::cout << "it didn't make sense this past like that..." << std::endl;
                    exit(1);
            }
        }
    }
}


std::string setTimeur() {
    unsigned static int hour = 0;
    unsigned static int minute = 0;
    unsigned static int oldMinute = 0;
    unsigned static int oldSeconde = 0;
    unsigned int seconde = 0;
    seconde = getTime();
    if (seconde % 60 == 0 && oldSeconde != seconde && seconde != 0) {
        oldSeconde = seconde;
        minute+=1;
    }
    if(minute % 60 == 0 && oldMinute != minute && minute != 0) {
        oldMinute = minute;
        hour+=1;
    }
    return std::to_string(hour) + "h ; " +  std::to_string(minute - 60 * hour) + "min ; " + std::to_string(seconde - 60 * minute) + "s";
}