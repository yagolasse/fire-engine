#include "random.hpp"

#include <random>

float Random::getFloat() {
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, 99);
    return (float)distrib(gen) / 100;
}
