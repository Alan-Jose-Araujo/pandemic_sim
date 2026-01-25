/**
 * @file config.hpp
 * @brief A DTO to hold the simulator config params.
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-22
 */

#pragma once

#include "simulator/individual.hpp"
#include <vector>
#include <string>

namespace Facades
{
    class Config
    {
    private:
        int numberOfRuns;
        
        int populationMatrixSize;
        
        int numberOfGenerations;
        
        double contagionFactor;
        
        Simulator::IndividualState requestedState;
        
        bool applySocialDistanceEffect;
        
        int threadCount;
        
        bool generateImage;
        
        std::vector<std::vector<double>> transitionProbabilities;

    public:
        int getNumberOfRuns() const;

        int getPopulationMatrixSize() const;

        int getNumberOfGenerations() const;

        double getContagionFactor() const;

        Simulator::IndividualState getRequestedState() const;

        bool getApplySocialDistanceEffect() const;

        int getThreadCount() const;

        bool getGenerateImage() const;

        const std::vector<std::vector<double>>& getTransitionProbabilities() const;

        void setNumberOfRuns(int numberOfRuns);

        void setPopulationMatrixSize(int value);

        void setNumberOfGenerations(int value);

        void setContagionFactor(double value);

        void setRequestedState(Simulator::IndividualState requestedState);

        void setApplySocialDistanceEffect(bool value) ;

        void setThreadCount(int value);

        void setGenerateImage(bool value);

        void setTransitionProbabilities(const std::vector<std::vector<double>>& value);

        static Config buildFromConfigFile(const std::string &filePath);

        static void generateConfigFile(std::string outputPath);
    };
};