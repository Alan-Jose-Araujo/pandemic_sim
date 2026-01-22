/**
 * @file random_number_generator.hpp
 * @brief A thread-safe random number generator class.
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-21
 */

#pragma once

#include <random>
#include <chrono>

namespace Rng
{
    class RandomNumberGenerator
    {
    private:
        /**
         * The mersenne twister engine is a general-purpose pseudorandom number generator (PRNG).
         * Reference: M. Matsumoto and T. Nishimura, Mersenne Twister: A 623-Dimensionally
         * Equidistributed Uniform Pseudo-Random Number Generator, ACM Transactions
         * on Modeling and Computer Simulation, Vol. 8, No. 1, January 1998, pp 3-30.
         * Soruce: https://dl.acm.org/doi/abs/10.1145/272991.272995
         */
        static thread_local std::mt19937 generator;

        static thread_local std::uniform_real_distribution<double> distribution;

    public:
        static constexpr double MIN_ACCEPTABLE_VALUE = 0.0;

        static constexpr double MAX_ACCEPTABLE_VALUE = 1.0;

        RandomNumberGenerator() = default;

        static double getRandomNumber(double minValue, double maxValue);

        static double getRandomNumber();

        static void setSeed(unsigned int seed);
    };
};