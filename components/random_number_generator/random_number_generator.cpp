#include "../random_number_generator/random_number_generator.h"
#include <random>

int getRandomNumber(int lowerBound, int upperBound)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(lowerBound, upperBound);
    return dis(gen);
}