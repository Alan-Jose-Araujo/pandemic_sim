#include <catch2/catch_test_macros.hpp>
#include "simulator/random_walk_model.hpp"
#include "simulator/individual.hpp"
#include <string>
#include <vector>
#include <memory>

TEST_CASE("Random walk model can execute successfully", "[rwm][unit]")
{
    int populationMatrixSize = 100;
    int numberOfGenerations = 10;
    double contagionFactor = 0.5;
    Simulator::IndividualState requestedStateCount = Simulator::IndividualState::Dead;
    bool applySocialDistanceEffect = false;
    std::vector<std::vector<double>> transition_probabilities = {
        {0.62, 0.3, 0.05, 0.0, 0.03}, // healthy
        {0.05, 0.64, 0.1, 0.01, 0.2}, // isolated
        {0.0, 0.1, 0.65, 0.1, 0.15},  // sick
        {0.0, 0.0, 0.0, 1.0, 0.0},    // dead
        {0.0, 0.05, 0.02, 0.0, 0.93}  // immune
    };

    SECTION("RWM can be initialized and get the 'DEAD' individuals count")
    {
        std::unique_ptr<Simulator::RandomWalkModel> model;
        int result;
        model = std::make_unique<Simulator::RandomWalkModel>(
            populationMatrixSize,
            contagionFactor,
            applySocialDistanceEffect,
            transition_probabilities
        );
        model->startSimulation(numberOfGenerations);
        result = model->getIndividualQuantityByState(Simulator::IndividualState::Dead);
        REQUIRE(result >= 0);
    }

    SECTION("RWM Death toll follows a non-deterministic but plausible results")
    {
        std::unique_ptr<Simulator::RandomWalkModel> model;
        int result;
        model = std::make_unique<Simulator::RandomWalkModel>(
            populationMatrixSize,
            contagionFactor,
            applySocialDistanceEffect,
            transition_probabilities
        );
        model->startSimulation(numberOfGenerations);
        result = model->getIndividualQuantityByState(Simulator::IndividualState::Dead);
        INFO("Death toll: " << result);
        CHECK(result > 0);
        CHECK(result < populationMatrixSize * populationMatrixSize);
    }

    SECTION("RWM statistical variance test (Monte Carlo)")
    {
        std::vector<int> results;
        for(int i = 0; i < 100; ++i) {
            auto model = std::make_unique<Simulator::RandomWalkModel>(
                populationMatrixSize,
                contagionFactor,
                applySocialDistanceEffect,
                transition_probabilities
            );
            model->startSimulation(numberOfGenerations);
            results.push_back(
                model->getIndividualQuantityByState(Simulator::IndividualState::Dead)
            );
        }

        double mean = std::accumulate(results.begin(), results.end(), 0.0) / results.size();
        INFO("Mean: " << mean);
        REQUIRE(mean > 0);
    }
}