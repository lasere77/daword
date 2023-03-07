#include "../include/Libs.hpp"
#include "../include/Population.hpp"
#include "../include/Enemy.hpp"

const int NBINDIVIDUAL = 15;
const int NBENEMY = 15;

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "daword", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    srand(time(nullptr));
    Individual individuals[NBINDIVIDUAL]; 
    Enemy enemys[NBENEMY];
    
    //individuals
    for(int i = 0; i != NBINDIVIDUAL; i++) {
        individuals[i].individualSprite.setPosition(individuals[i].individualSprite.getPosition().x, individuals[i].individualSprite.getPosition().y + (15 * i));
    }
    for(int i = 0; i != NBENEMY; i++) {
        enemys[i].enemySprite.setPosition(960, 540);
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
        for(int i = 0; i != NBENEMY; i++) {
            enemys[i].move();
        }
        window.clear();
        for(int i = 0; i != NBINDIVIDUAL; i++) {
            window.draw(individuals[i].individualSprite);
        }
        for(int i = 0; i != NBENEMY; i++) {
            window.draw(enemys[i].enemySprite);
        }
        window.display();
    }
    return 0;
}