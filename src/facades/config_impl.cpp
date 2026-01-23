/**
 * @file config_impl.hpp
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-22
 */

#include "facades/config.hpp"
#include "facades/json_parser.hpp"
#include <stdexcept>

namespace Facades
{
    int Config::getNumberOfRuns() const
    {
        return numberOfRuns;
    }

    int Config::getPopulationMatrixSize() const
    {
        return populationMatrixSize;
    }

    int Config::getNumberOfGenerations() const
    {
        return numberOfGenerations;
    }

    double Config::getContagionFactor() const
    {
        return contagionFactor;
    }

    Simulator::IndividualState Config::getRequestedState() const
    {
        return requestedState;
    }

    bool Config::getApplySocialDistanceEffect() const
    {
        return applySocialDistanceEffect;
    }

    int Config::getThreadCount() const
    {
        return threadCount;
    }

    bool Config::getGenerateImage() const
    {
        return generateImage;
    }

    const std::vector<std::vector<double>> &Config::getTransitionProbabilities() const
    {
        return transitionProbabilities;
    }

    void Config::setNumberOfRuns(int value)
    {
        numberOfRuns = value;
    }

    void Config::setPopulationMatrixSize(int value)
    {
        populationMatrixSize = value;
    }

    void Config::setNumberOfGenerations(int value)
    {
        numberOfGenerations = value;
    }

    void Config::setContagionFactor(double value)
    {
        contagionFactor = value;
    }

    void Config::setRequestedState(Simulator::IndividualState requestedState)
    {
        requestedState = requestedState;
    }

    void Config::setApplySocialDistanceEffect(bool value)
    {
        applySocialDistanceEffect = value;
    }

    void Config::setThreadCount(int value)
    {
        threadCount = value;
    }

    void Config::setGenerateImage(bool value)
    {
        generateImage = value;
    }

    void Config::setTransitionProbabilities(const std::vector<std::vector<double>> &value)
    {
        transitionProbabilities = value;
    }

    Config Config::buildFromConfigFile(const std::string &filePath)
    {
        JSON null_value(nullptr);
        bool configFileExistsAndIsValid = Facades::JsonParser::isValidJson(filePath);
        if(!configFileExistsAndIsValid) {
            throw std::runtime_error("Could not open the config file: " + filePath + ". Check if the file exists or has a valid syntax.");
        }

        JSON parser = Facades::JsonParser::getParser(filePath);

        Config configDto;
        configDto.setNumberOfRuns(parser.value("number_of_runs", null_value));
        configDto.setPopulationMatrixSize(parser.value("population_matrix_size", null_value));
        configDto.setNumberOfGenerations(parser.value("number_of_generations", null_value));
        configDto.setContagionFactor(parser.value("contagion_factor", null_value));
        configDto.setRequestedState(static_cast<Simulator::IndividualState>(parser.value("requested_state", Simulator::IndividualState::Healthy)));
        configDto.setApplySocialDistanceEffect(parser.value("apply_social_distance_effect", false));
        configDto.setThreadCount(parser.value("thread_count", 1));
        configDto.setGenerateImage(parser.value("generate_image", false));
        configDto.setTransitionProbabilities(parser.value("transition_probabilities", null_value));
        return configDto;
    }
};