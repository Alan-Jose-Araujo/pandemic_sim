/**
* @file random_number_generatpr.hpp
* @brief RNG dependencie for the random walk model.
*/

#pragma once

#include <random>

/**
 * @class RandomNumberGenerator
 * Properties: std::mt19937 generator,
 * std::uniform_real_distribution<> realDistribution,
 * std::mt19937& getGenerator().
 * Methods: RandomNumberGenerator(double minValue, double maxValue, unsigned int seed),
 * RandomNumberGenerator(unsigned int seed),
 * RandomNumberGenerator(),
 * double getRandomNumber(),
 * double getRandomNumber(double minValue, double maxValue)
 */
namespace Simulator
{
    class RandomNumberGenerator
    {
    private:

        std::mt19937 generator;

        std::uniform_real_distribution<> realDistribution;

        std::mt19937& getGenerator();

    public:

        RandomNumberGenerator(double minValue, double maxValue, unsigned int seed);

        RandomNumberGenerator(unsigned int seed);

        RandomNumberGenerator();

        double getRandomNumber();

        double getRandomNumber(double minValue, double maxValue);
    };
};