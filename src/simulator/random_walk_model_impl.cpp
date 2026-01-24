/**
 * @file random_walk_model_impl.cpp
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-24
 */

#include "simulator/random_walk_model.hpp"

namespace Simulator
{
    RandomWalkModel::RandomWalkModel(int populationMatrixSize, double contagionFactor, bool applySocialDistanceEffect)
    : populationMatrixSize(populationMatrixSize), contagionFactor(contagionFactor), applySocialDistanceEffect(applySocialDistanceEffect),
    sequentialRng()
    {
        this->initializePopulation();
        this->initializeSickIndividuals();
    }

    void RandomWalkModel::initializePopulation()
    {
        this->getCurrentPopulation().resize(
            this->populationMatrixSize,
            std::vector<Individual>(this->populationMatrixSize, Individual(IndividualState::Healthy))
        );
        this->setNextPopulation(this->getCurrentPopulation());
    }

    void RandomWalkModel::initializeSickIndividuals()
    {
        int startIndex = populationMatrixSize / 2;
        this->getCurrentPopulation()[startIndex][startIndex].setCurrentState(IndividualState::Sick);
        this->getNextPopulation()[startIndex][startIndex].setCurrentState(IndividualState::Sick);
    }

    void RandomWalkModel::computeSocialInteractions(int line, int column, Rng::RandomNumberGenerator *randomNumberGenerator)
    {
        int initialLine = std::max(0, line - 1);
        int finalLine = std::min(line + 2, this->getPopulationMatrixSize());

        int isolatedCount = 0;

        for(int i = initialLine; i < finalLine; ++i) {
            int initialColumn = std::max(0, column - 1);
            int finalColumn = std::min(column + 2, this->getPopulationMatrixSize());

            for(int j = initialColumn; j < finalColumn; ++j) {
                Individual &neighbour = this->getCurrentPopulation()[i][j];

                if(neighbour.getIndividualState() == IndividualState::Isolated && this->getApplySocialDistanceEffect()) {
                    isolatedCount++;
                }

                if(neighbour.getIndividualState() == IndividualState::Sick) {
                    computeSickContact(this->getNextPopulation()[line][column], neighbour, randomNumberGenerator);
                }
            }
        }

        if(isolatedCount > 0 && this->getApplySocialDistanceEffect()) {
            double reduction = 0.05 * isolatedCount;
            this->setContagionFactor(std::max(this->getContagionFactor() * (1.0 - reduction), 0.1));
        }
    }

    void RandomWalkModel::computeSickContact(Simulator::Individual &individual, Simulator::Individual &neighbour, Rng::RandomNumberGenerator *randomNumberGenerator)
    {
        if(individual.getIndividualState() == IndividualState::Dead) return;

        double number = randomNumberGenerator->getRandomNumber();

        if(number < this->getContagionFactor()) {
            individual.setCurrentState(IndividualState::Sick);
        }
    }

    void RandomWalkModel::individualTransition(int line, int column, Rng::RandomNumberGenerator *randomNumberGenerator)
    {
        Individual &individual = this->getCurrentPopulation()[line][column];

        if(individual.getIndividualState() == IndividualState::Dead) return;

        if(individual.getIndividualState() == IndividualState::Healthy) {
            this->computeSocialInteractions(line, column, randomNumberGenerator);
        } else {
            const std::vector<double> &probabilities = this->getTransitionProbabilities()[static_cast<int>(individual.getIndividualState())];
            double number = randomNumberGenerator->getRandomNumber();

            double cumulativeProbability = 0.0;
            for(size_t i = 0; i < probabilities.size(); ++i) {
                cumulativeProbability += probabilities[i];
                if(number <= cumulativeProbability) {
                    this->getCurrentPopulation()[line][column].setCurrentState(static_cast<IndividualState>(i));
                    break;
                }
            }
        }
    }

    void RandomWalkModel::nextGeneration()
    {
        for(int i = 0; i < this->getPopulationMatrixSize(); ++i) {
            for(int j = 0; j < this->getPopulationMatrixSize(); ++j) {
                this->individualTransition(i, j, &this->getSequentialRng());
            }
        }
        this->setCurrentPopulation(this->getNextPopulation());
    }

    int RandomWalkModel::getStateCount(Simulator::IndividualState requestedState)
    {
        int cumulated = 0;
        for(const auto &row : this->getCurrentPopulation()) {
            for(const auto &individual : row) {
                if(individual.getIndividualState() == requestedState) cumulated++;
            }
        }
        return cumulated;
    }

    void RandomWalkModel::generateImage(std::string imagesDir)
    {
        // TODO: Implement it.
    }

    void RandomWalkModel::simulation(int generations)
    {
        for(int i = 0; i < generations; ++i) {
            this->nextGeneration();
        }
    }

    void RandomWalkModel::setSequenialRng(Rng::RandomNumberGenerator value)
    {
        this->sequentialRng = value;
    }

    Rng::RandomNumberGenerator RandomWalkModel::getSequentialRng()
    {
        return this->sequentialRng;
    }

    void RandomWalkModel::setCurrentPopulation(std::vector<std::vector<Simulator::Individual>> value)
    {
        this->currentPopulation = value;
    }

    std::vector<std::vector<Simulator::Individual>> &RandomWalkModel::getCurrentPopulation()
    {
        return this->currentPopulation;
    }

    void RandomWalkModel::setNextPopulation(std::vector<std::vector<Simulator::Individual>> value)
    {
        this->nextPopulation = value;
    }

    std::vector<std::vector<Simulator::Individual>> &RandomWalkModel::getNextPopulation()
    {
        return this->nextPopulation;
    }

    void RandomWalkModel::setTransitionProbabilities(std::vector<std::vector<double>> value)
    {
        this->transitionProbabilities = value;
    }

    std::vector<std::vector<double>> &RandomWalkModel::getTransitionProbabilities()
    {
        return this->transitionProbabilities;
    }

    void RandomWalkModel::setContagionFactor(double value)
    {
        this->contagionFactor = value;
    }

    double RandomWalkModel::getContagionFactor()
    {
        return this->contagionFactor;
    }

    void RandomWalkModel::setPopulationMatrixSize(int value)
    {
        this->populationMatrixSize = value;
    }

    int RandomWalkModel::getPopulationMatrixSize()
    {
        return this->populationMatrixSize;
    }

    void RandomWalkModel::setApplySocialDistanceEffect(bool value)
    {
        this->applySocialDistanceEffect = value;
    }

    bool RandomWalkModel::getApplySocialDistanceEffect()
    {
        return this->applySocialDistanceEffect;
    }
};