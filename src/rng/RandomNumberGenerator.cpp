#include "../../include/rng/RandomNumberGenerator.hpp"

namespace rng
{

    std::mt19937 &RandomNumberGenerator::get_generator()
    {
        auto time_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::random_device random_device;
        size_t hashed_seed = std::hash<size_t>()(time_seed ^ random_device());
        static std::mt19937 generator(hashed_seed);
        return generator;
    }

    RandomNumberGenerator::RandomNumberGenerator(double min_value, double max_value, unsigned int seed)
        : distribution(min_value, max_value)
    {
        std::random_device random_device;
        size_t combined_seed = std::hash<size_t>()(seed ^ random_device());
        generator.seed(combined_seed);
    }

    RandomNumberGenerator::RandomNumberGenerator(unsigned int seed)
        : RandomNumberGenerator(0.0, 1.0, seed)
    {
    }

    RandomNumberGenerator::RandomNumberGenerator()
        : RandomNumberGenerator(
              0.0,
              1.0,
              static_cast<unsigned int>(
                  std::chrono::high_resolution_clock::now().time_since_epoch().count()))
    {
    }

    double RandomNumberGenerator::get_random_number()
    {
        return distribution(this->generator);
    }

    double RandomNumberGenerator::get_random_number(double min_value, double max_value)
    {
        std::uniform_real_distribution<> local_distribution(min_value, max_value);
        return local_distribution(this->generator);
    }

};