#include <catch2/catch_test_macros.hpp>
#include "simulator/random_walk_model.hpp"
#include "simulator/individual.hpp"
#include <string>
#include <vector>
#include <memory>

TEST_CASE("Random walk model can execute successfully", "[rwm][unit]")
{
    int numberOfRuns = 100;
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
            applySocialDistanceEffect
        );
        model->setTransitionProbabilities(transition_probabilities);
        model->simulation(numberOfGenerations);
        result = model->getStateCount(Simulator::IndividualState::Dead);
        REQUIRE(result >= 0);
    }
}