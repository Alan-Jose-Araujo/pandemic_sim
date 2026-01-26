/**
 * @file random_walk_model_parallel_impl.cpp
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-25
 */

#include "simulator/random_walk_simulator_parallel.hpp"
#include <stdexcept>
#include <memory>
#include <thread>

namespace Simulator
{
    RandomWalkModelParallel::RandomWalkModelParallel(int populationMatrixSize, double contagionFactor, bool applySocialDistanceEffect, std::vector<std::vector<double>> transitionProbabilities, int threadCount)
        : RandomWalkModel(populationMatrixSize, contagionFactor, applySocialDistanceEffect, transitionProbabilities), threadCount(threadCount)
    {
        this->currentProcessorAvailableThreads = 12;
        this->throwIfMultithreadingIsNotSupported();
        this->throwIfMaximumThreadsIsExceeded();
    }

    void RandomWalkModelParallel::processChunk(int startRow, int endRow)
    {
        for (int i = startRow; i < endRow; ++i)
        {
            for (int j = 0; j < this->populationMatrixSize; ++j)
            {
                this->individualTransition(i, j);
            }
        }
    }

    void RandomWalkModelParallel::throwIfMaximumThreadsIsExceeded()
    {
        if (this->threadCount > this->currentProcessorAvailableThreads)
        {
            throw std::out_of_range("The requested threads count exceeds the current processor available threads");
        }
    }

    void RandomWalkModelParallel::throwIfMultithreadingIsNotSupported()
    {
        if (this->threadCount == 0)
        {
            throw std::out_of_range("The current processor does not supports multithreading, please remove the '-t' param");
        }
    }

    void RandomWalkModelParallel::parallelSimulation(int generations)
    {
        for (int g = 0; g < generations; ++g)
        {
            std::vector<std::thread> threads;
            int rowsPerThread = this->populationMatrixSize / this->threadCount;
            int remainingRows = this->populationMatrixSize % this->threadCount;

            int currentRow = 0;
            for (int t = 0; t < this->threadCount; ++t)
            {
                int startRow = currentRow;
                int endRow = startRow + rowsPerThread + (t < remainingRows ? 1 : 0);
                currentRow = endRow;

                // MELHORIA: A lambda agora não precisa capturar ponteiros de RNG
                threads.emplace_back([this, startRow, endRow]() {
                // Dentro de processChunk, usamos o RNG estático e thread-safe
                this->processChunk(startRow, endRow);
             });
            }

            for (auto &t : threads)
                t.join();
            this->currentPopulation = this->nextPopulation;
        }
    }
};