/**
 * @file random_walk_model_parallel.hpp
 * @brief Multithreading random walk model implementation.
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-25
 */

#pragma once

#include "simulator/random_walk_model.hpp"

namespace Simulator
{
    class RandomWalkModelParallel : public RandomWalkModel
    {
    private:
        int threadCount;

        int currentProcessorAvailableThreads;

        void processChunk(int startRow, int endRow);

        void throwIfMaximumThreadsIsExceeded();

        void throwIfMultithreadingIsNotSupported();

    public:
        using Simulator::RandomWalkModel::RandomWalkModel;

        RandomWalkModelParallel(int populationMatrixSize, double contagionFactor, bool applySocialDistanceEffect, std::vector<std::vector<double>> transitionProbabilities, int threadCount);

        void parallelSimulation(int generations);
    };
};