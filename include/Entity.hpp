#pragma once

#include "Population.hpp"
#include "Enemy.hpp"
#include "PowerUp.hpp"

#include <array>
#include <memory>

/*
*nominal value {
*   enemy = 50;
*   individual = 15;
*   powerUp = 5;    
*}
*/

const int NBINDIVIDUAL = 15;
const int NBENEMY = 50;
const int NBPOWERUP = 5;

namespace entity {
    extern std::array<std::unique_ptr<Individual>, NBINDIVIDUAL> individuals;
    extern Enemy enemys[NBENEMY];
    extern PowerUp powerUps[NBPOWERUP];
}