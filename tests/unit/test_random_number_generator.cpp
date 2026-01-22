#include <catch2/catch_test_macros.hpp>
#include <map>
#include "rng/random_number_generator.hpp"

using RNG = Rng::RandomNumberGenerator;

TEST_CASE("RNG generates values ​​within the correct range.", "[unit][rng]")
{
    double result = RNG::getRandomNumber(),
    min = RNG::MIN_ACCEPTABLE_VALUE,
    max = RNG::MAX_ACCEPTABLE_VALUE;
    CHECK(result >= min);
    CHECK(result <= max);
}

TEST_CASE("RNG has an approximately uniform distribution.", "[unit][rng]")
{
    const int iterations = 100000;
    std::map<int, int> counts;
    double minValue = 0.0,
    maxValue = 10.0;
    
    for(int i = 0; i < iterations; ++i) {
        double value = RNG::getRandomNumber(minValue, maxValue);
        counts[static_cast<int>(value)]++;
    }

    for(int i = minValue; i < maxValue; ++i) {
        INFO("Checking bucket: " << i);
        CHECK(counts[i] > 8500);
        CHECK(counts[i] < 11500);
    }
}