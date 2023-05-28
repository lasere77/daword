#include "../include/Entity.hpp"

namespace entity {
    std::array<std::unique_ptr<Individual>, NBINDIVIDUAL> individuals;
    Enemy enemys[NBENEMY];
    PowerUp powerUps[NBPOWERUP];
}