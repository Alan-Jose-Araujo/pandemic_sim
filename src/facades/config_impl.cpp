/**
 * @file config_impl.cpp
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-22
 */

#include "facades/config.hpp"
#include "facades/json_parser.hpp"
#include <stdexcept>
#include <fstream>
#include <iomanip>

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
        if (!configFileExistsAndIsValid)
        {
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

    void Config::generateConfigFile(std::string outputPath)
    {
        if(outputPath.find(".json") == std::string::npos) {
            outputPath += ".json";
        }

        JSON json;
        std::vector<std::vector<double>> transitionProbabilities = {
            {0.62, 0.3, 0.05, 0.0, 0.03}, // healthy
            {0.05, 0.64, 0.1, 0.01, 0.2}, // isolated
            {0.0, 0.1, 0.65, 0.1, 0.15},  // sick
            {0.0, 0.0, 0.0, 1.0, 0.0},    // dead
            {0.0, 0.05, 0.02, 0.0, 0.93}  // immune
        };
        json["number_of_runs"] = 0;
        json["population_matrix_size"] = 0;
        json["number_of_generations"] = 0;
        json["contagion_factor"] = 0.0;
        json["requested_state"] = static_cast<int>(Simulator::IndividualState::Healthy);
        json["apply_social_distance_effect"] = false;
        json["thread_count"] = 1;
        json["generate_image"] = false;
        json["transition_probabilities"] = transitionProbabilities;

        std::ofstream file(outputPath);
        file << std::setw(4) << json << std::endl;
    }
};