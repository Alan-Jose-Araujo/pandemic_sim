#ifndef RANDOM_NUMBER_GENERATOR_H
#define RANDOM_NUMBER_GENERATOR_H

#include <random>
#include <chrono>
#include <functional>

/**
 * The number randomization machine returns a random double
 * generated by a uniform continuous distribution.
 */
class RandomNumberGenerator {

    private:

        /**
         * The mersenne twister engine is a general-purpose pseudorandom number generator (PRNG).
         * Reference: M. Matsumoto and T. Nishimura, Mersenne Twister: A 623-Dimensionally
         * Equidistributed Uniform Pseudo-Random Number Generator, ACM Transactions
         * on Modeling and Computer Simulation, Vol. 8, No. 1, January 1998, pp 3-30.
         * Soruce: https://dl.acm.org/doi/abs/10.1145/272991.272995
         */
        std::mt19937& getGenerator()
        {
            auto timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
            std::random_device rd;
            size_t hashedSeed = std::hash<size_t>()(timeSeed ^ rd());
            static std::mt19937 gen(hashedSeed);
            return gen;
        }

    public:

        double getRandomNumber(double minValue = 0, double maxValue = 1)
        {
            static std::uniform_real_distribution<> dis(minValue, maxValue);
            return dis(this->getGenerator());
        }

};

#endif