#include <chrono>
#include "pandemic_sim/simulator/random_number_generator.hpp"

namespace Simulator
{
    RandomNumberGenerator::RandomNumberGenerator(double minValue, double maxValue, unsigned int seed)
    {
        std::random_device randomDevice;
        size_t combinedSeed = std::hash<size_t>()(seed ^ randomDevice());
        generator.seed(combinedSeed);
    }

    RandomNumberGenerator::RandomNumberGenerator(unsigned int seed)
        : RandomNumberGenerator(0.0, 1.0, seed) {}

    RandomNumberGenerator::RandomNumberGenerator()
        : RandomNumberGenerator(0.0, 1.0, std::chrono::high_resolution_clock::now().time_since_epoch().count()) {}

    /**
    * The mersenne twister engine is a general-purpose pseudorandom number generator (PRNG).
    * Reference: M. Matsumoto and T. Nishimura, Mersenne Twister: A 623-Dimensionally
    * Equidistributed Uniform Pseudo-Random Number Generator, ACM Transactions
    * on Modeling and Computer Simulation, Vol. 8, No. 1, January 1998, pp 3-30.
    * Soruce: https://dl.acm.org/doi/abs/10.1145/272991.272995
    */
    std::mt19937& RandomNumberGenerator::getGenerator()
    {
        auto timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::random_device rd;
        size_t hashedSeed = std::hash<size_t>()(timeSeed ^ rd());
        static std::mt19937 localGenerator(hashedSeed);
        return localGenerator;
    }

    double RandomNumberGenerator::getRandomNumber(double minValue, double maxValue)
    {
        std::uniform_real_distribution<> localDistribution(minValue, maxValue);
        return localDistribution(this->generator);
    }

    double RandomNumberGenerator::getRandomNumber()
    {
        return this->realDistribution(this->generator);
    }
};