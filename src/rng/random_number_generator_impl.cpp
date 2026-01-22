/**
 * @file random_number_generator_impl.cpp
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-21
 */

#include "rng/random_number_generator.hpp"

namespace Rng
{
    thread_local std::mt19937 RandomNumberGenerator::generator = [] {
        std::random_device randomDevice;
        return std::mt19937(randomDevice() ^ static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    }();

    thread_local std::uniform_real_distribution<double> RandomNumberGenerator::distribution {
        RandomNumberGenerator::MIN_ACCEPTABLE_VALUE,
        RandomNumberGenerator::MAX_ACCEPTABLE_VALUE
    };

    double RandomNumberGenerator::getRandomNumber(double minValue, double maxValue)
    {
        std::uniform_real_distribution<> localDistribution(minValue, maxValue);
        return localDistribution(generator);
    }

    double RandomNumberGenerator::getRandomNumber()
    {
        return distribution(generator);
    }

    void RandomNumberGenerator::setSeed(unsigned int seed)
    {
        generator.seed(seed);
    }

};