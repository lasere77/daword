#pragma once

#include "Population.hpp"
#include "Enemy.hpp"
#include "PowerUp.hpp"

#include <array>
#include <memory>


/*
*nominal value {
*   enemy = 30;
*   individual = 15;
*   powerUp = 3;    
*}
*/

const int NBINDIVIDUAL = 15;
const int NBENEMY = 30;
const int NBPOWERUP = 3;

namespace entity {
    extern std::array<std::unique_ptr<Individual>, NBINDIVIDUAL> individuals;
    extern Enemy enemys[NBENEMY];
    extern PowerUp powerUps[NBPOWERUP];
}