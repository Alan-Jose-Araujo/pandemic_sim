/**
 * @file random_walk_model.hpp
 * @brief Abstraction of the mathematical model of random walk.
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-23
 */

#pragma once

#include "rng/random_number_generator.hpp"
#include "simulator/individual.hpp"
#include "facades/config.hpp"
#include <vector>

namespace Simulator
{
    using Population = std::vector<std::vector<Simulator::Individual>>;

    class RandomWalkModel
    {
    protected:
        Rng::RandomNumberGenerator sequentialRng;

        Population currentPopulation;

        Population nextPopulation;

        std::vector<std::vector<double>> transitionProbabilities;

        double contagionFactor;

        int populationMatrixSize;

        bool applySocialDistanceEffect;

        void initializePopulation();

        void initializeSickIndividuals();

        void computeSocialInteractions(int line, int column, Rng::RandomNumberGenerator *randomNumberGenerator);

        void computeSickContact(Simulator::Individual &individual, Simulator::Individual &neighbour, Rng::RandomNumberGenerator *randomNumberGenerator, double effectiveContagion);

        void individualTransition(int line, int column, Rng::RandomNumberGenerator *randomNumberGenerator);

        void goToNextGeneration();

    public:
        RandomWalkModel(int populationMatrixSize, double contagionFactor, bool applySocialDistanceEffect, std::vector<std::vector<double>> transitionProbabilities);

        RandomWalkModel(Facades::Config &config);

        int getIndividualQuantityByState(Simulator::IndividualState individualState);

        void startSimulation(int generations);
    };
};