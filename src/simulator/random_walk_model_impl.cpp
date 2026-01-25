/**
 * @file random_walk_model_impl.cpp
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-24
 */

#include "simulator/random_walk_model.hpp"

namespace Simulator
{
    RandomWalkModel::RandomWalkModel(int populationMatrixSize, double contagionFactor, bool applySocialDistanceEffect, std::vector<std::vector<double>> transitionProbabilities)
    : populationMatrixSize(populationMatrixSize), contagionFactor(contagionFactor), applySocialDistanceEffect(applySocialDistanceEffect), transitionProbabilities(transitionProbabilities),
    sequentialRng()
    {
        this->initializePopulation();
        this->initializeSickIndividuals();
    }

    RandomWalkModel::RandomWalkModel(Facades::Config &config)
    : populationMatrixSize(config.getPopulationMatrixSize()), contagionFactor(config.getContagionFactor()), applySocialDistanceEffect(config.getApplySocialDistanceEffect()),
    transitionProbabilities(config.getTransitionProbabilities()), sequentialRng()
    {
        this->initializePopulation();
        this->initializeSickIndividuals();
    }

    void RandomWalkModel::initializePopulation()
    {
        this->currentPopulation.resize(
            this->populationMatrixSize,
            std::vector<Individual>(this->populationMatrixSize, Individual(IndividualState::Healthy))
        );
        this->nextPopulation = this->currentPopulation;
    }

    void RandomWalkModel::initializeSickIndividuals()
    {
        int startIndex = this->populationMatrixSize / 2;
        this->currentPopulation[startIndex][startIndex].setCurrentState(IndividualState::Sick);
        this->nextPopulation[startIndex][startIndex].setCurrentState(IndividualState::Sick);
    }

    void RandomWalkModel::computeSocialInteractions(int line, int column, Rng::RandomNumberGenerator *randomNumberGenerator)
    {
        int initialLine = std::max(0, line - 1);
        int finalLine = std::min(line + 2, this->populationMatrixSize);
        int initialColumn = std::max(0, column - 1);
        int finalColumn = std::min(column + 2, this->populationMatrixSize);

        int isolatedCount = 0;

        if(this->applySocialDistanceEffect) {
            for(int i = initialLine; i < finalLine; ++i) {
                for(int j = initialColumn; j < finalColumn; ++j) {
                    if(this->currentPopulation[i][j].getIndividualState() == IndividualState::Isolated) {
                        isolatedCount++;
                    }
                }
            }
        }

        double effectiveContagion = this->contagionFactor;

        if(isolatedCount > 0 && this->applySocialDistanceEffect) {
            double reduction = 0.05 * isolatedCount;
            effectiveContagion = std::max(effectiveContagion * (1.0 - reduction), 0.1);
        }

        for(int i = initialLine; i < finalLine; ++i) {
            for(int j = initialColumn; j < finalColumn; ++j) {
                Individual &neighbour = this->currentPopulation[i][j];

                if(neighbour.getIndividualState() == IndividualState::Sick) {
                    this->computeSickContact(
                        this->nextPopulation[line][column],
                        neighbour,
                        randomNumberGenerator,
                        effectiveContagion
                    );
                }
            }
        }
    }

    void RandomWalkModel::computeSickContact(Simulator::Individual &individual, Simulator::Individual &neighbour, Rng::RandomNumberGenerator *randomNumberGenerator, double effectiveContagion)
    {
        if(individual.getIndividualState() == IndividualState::Dead || individual.getIndividualState() == IndividualState::Sick) return;

        double randomNumber = randomNumberGenerator->getRandomNumber();

        if(randomNumber < effectiveContagion) {
            individual.setCurrentState(IndividualState::Sick);
        }
    }

    void RandomWalkModel::individualTransition(int line, int column, Rng::RandomNumberGenerator *randomNumberGenerator)
    {
        Individual &individual = this->currentPopulation[line][column];

        if(individual.getIndividualState() == IndividualState::Dead) return;

        if(individual.getIndividualState() == IndividualState::Healthy) {
            this->computeSocialInteractions(line, column, randomNumberGenerator);
        } else {
            const std::vector<double> &probabilities = this->transitionProbabilities[static_cast<int>(individual.getIndividualState())];
            double number = randomNumberGenerator->getRandomNumber();

            double cumulativeProbability = 0.0;
            for(size_t i = 0; i < probabilities.size(); ++i) {
                cumulativeProbability += probabilities[i];
                if(number <= cumulativeProbability) {
                    this->nextPopulation[line][column].setCurrentState(static_cast<IndividualState>(i));
                    break;
                }
            }
        }
    }

    void RandomWalkModel::goToNextGeneration()
    {
        for(int i = 0; i < this->populationMatrixSize; ++i) {
            for(int j = 0; j < this->populationMatrixSize; ++j) {
                this->individualTransition(i, j, &this->sequentialRng);
            }
        }

        std::swap(this->currentPopulation, this->nextPopulation);

        this->nextPopulation = this->currentPopulation;
    }

    int RandomWalkModel::getIndividualQuantityByState(Simulator::IndividualState individualState)
    {
        int cumulated = 0;
        for(const auto &row : this->currentPopulation) {
            for(const auto &individual : row) {
                if(individual.getIndividualState() == individualState) {
                    cumulated++;
                }
            }
        }
        return cumulated;
    }

    void RandomWalkModel::startSimulation(int generations)
    {
        for(int i = 0; i < generations; ++i) {
            this->goToNextGeneration();
        }
    }
};