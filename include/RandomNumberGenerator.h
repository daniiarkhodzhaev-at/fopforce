//
// Created by Sageblatt on 28.07.2021.
//

#ifndef THE_ARK_RANDOMNUMBERGENERATOR_H
#define THE_ARK_RANDOMNUMBERGENERATOR_H

#include <chrono>
#include <random>
#include <exception>
#include <stdexcept>

class RandomNumberGenerator
{
private:
    static std::default_random_engine r_engine;
public:
    int getRandomInt(int min, int max);
    float getRandomFloat(float min, float max);
    double getRandomDouble(double min, double max);
};

#endif
