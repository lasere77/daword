#pragma once

#include "Libs.hpp"

class Individual {
    public:
        Individual();
        sf::CircleShape individualSprite;
        void move();

    private:
        sf::Texture texture;
        float radius = 10.0f;
        float speed = 4.0f;
        int health = 3;
        int fit = 0;
        bool basic;
        bool fearful;
        bool deviant;
        float x;
        float y;
};