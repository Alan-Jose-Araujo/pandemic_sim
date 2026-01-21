/**
 * @file random_number_generator_impl.cpp
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-21
 */

#include "rng/random_number_generator.hpp"

namespace Rng
{
    std::mt19937 &RandomNumberGenerator::getGenerator()
    {
        auto timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::random_device randomDevice;
        size_t hashedSeed = std::hash<size_t>()(timeSeed ^ randomDevice());
        static std::mt19937 generator(hashedSeed);
        return generator;
    }

    RandomNumberGenerator::RandomNumberGenerator(double minValue, double maxValue, unsigned int seed)
    {
        std::random_device randomDevice;
        size_t combinedSeed = std::hash<size_t>()(seed ^ randomDevice());
        generator.seed(combinedSeed);
    }

    RandomNumberGenerator::RandomNumberGenerator(unsigned int seed)
    : RandomNumberGenerator(
        RandomNumberGenerator::MIN_ACCEPTABLE_VALUE,
        RandomNumberGenerator::MAX_ACCEPTABLE_VALUE,
        seed
    ) {}

    RandomNumberGenerator::RandomNumberGenerator()
    : RandomNumberGenerator(
        RandomNumberGenerator::MIN_ACCEPTABLE_VALUE,
        RandomNumberGenerator::MAX_ACCEPTABLE_VALUE,
        std::chrono::high_resolution_clock::now().time_since_epoch().count()
    ) {}

    double RandomNumberGenerator::getRandomNumber(double minValue, double maxValue)
    {
        std::uniform_real_distribution<> localDistribution(minValue, maxValue);
        return localDistribution(this->generator);
    }

    double RandomNumberGenerator::getRandomNumber()
    {
        return distribution(this->generator);
    }

};