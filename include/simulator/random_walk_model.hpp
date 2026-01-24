/**
 * @file random_walk_model.hpp
 * @brief Abstraction of the mathematical model of random walk.
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-23
 */

#pragma once

#include "rng/random_number_generator.hpp"
#include "simulator/individual.hpp"
#include <vector>

namespace Simulator
{
    class RandomWalkModel
    {
    protected:
        Rng::RandomNumberGenerator sequentialRng;

        std::vector<std::vector<Simulator::Individual>> currentPopulation;

        std::vector<std::vector<Simulator::Individual>> nextPopulation;

        std::vector<std::vector<double>> transitionProbabilities;

        double contagionFactor;

        int populationMatrixSize;

        bool applySocialDistanceEffect;

        void initializePopulation();

        void initializeSickIndividuals();

        void computeSocialInteractions(int line, int column, Rng::RandomNumberGenerator *randomNumberGenerator);

        void computeSickContact(Simulator::Individual &individual, Simulator::Individual &neighbour, Rng::RandomNumberGenerator *randomNumberGenerator);

        void individualTransition(int line, int column, Rng::RandomNumberGenerator *randomNumberGenerator);

        void nextGeneration();

    public:
        RandomWalkModel(int populationMatrixSize, double contagionFactor, bool applySocialDistanceEffect);

        int getStateCount(Simulator::IndividualState requestedState);

        void generateImage(std::string imagesDir);

        void simulation(int generations);

        // Getters and Setters

        void setSequenialRng(Rng::RandomNumberGenerator value);

        Rng::RandomNumberGenerator getSequentialRng();

        void setCurrentPopulation(std::vector<std::vector<Simulator::Individual>> value);

        std::vector<std::vector<Simulator::Individual>> &getCurrentPopulation();

        void setNextPopulation(std::vector<std::vector<Simulator::Individual>> value);

        std::vector<std::vector<Simulator::Individual>> &getNextPopulation();

        void setTransitionProbabilities(std::vector<std::vector<double>> value);

        std::vector<std::vector<double>> &getTransitionProbabilities();

        void setContagionFactor(double value);

        double getContagionFactor();

        void setPopulationMatrixSize(int value);

        int getPopulationMatrixSize();

        void setApplySocialDistanceEffect(bool value);

        bool getApplySocialDistanceEffect();
    };
};