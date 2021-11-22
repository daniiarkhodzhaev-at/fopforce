//
// Created by Sageblatt on 28.07.2021.
//

#include "RandomNumberGenerator.h"

std::default_random_engine RandomNumberGenerator::r_engine = std::default_random_engine(std::chrono::steady_clock::now().time_since_epoch().count());

int RandomNumberGenerator::getRandomInt(int min, int max) {
    if (min > max)
        throw std::invalid_argument("MIN/MAX MISMATCH IN getRandomInt");
    std::uniform_int_distribution<int> d(min, max);
    return d(r_engine);
}

float RandomNumberGenerator::getRandomFloat(float min, float max) {
    if (min > max)
        throw std::invalid_argument("MIN/MAX MISMATCH IN getRandomFloat");
    std::uniform_real_distribution<float> d(min, max);
    return d(r_engine);
}

double RandomNumberGenerator::getRandomDouble(double min, double max) {
    if (min > max)
        throw std::invalid_argument("MIN/MAX MISMATCH IN getRandomDouble");
    std::uniform_real_distribution<double> d(min, max);
    return d(r_engine);
}
