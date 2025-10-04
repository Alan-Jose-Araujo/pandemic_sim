#ifndef CONFIG_H
#define CONFIG_H
#endif

#include "lib/json.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include "DefaultParams.hh"

using namespace std;
using json = nlohmann::json;

class Config {

    public:

        int numberOfRuns;
        int populationMatrixSize;
        int numberOfGenerations;
        double contagionFactor;
        int requestedStateCount;
        bool applySocialDistanceEffect;
        int threadCount;
        bool generateImage;

        static Config buildFromConfigFile(const string& path) {
            ifstream in(path);

            if (!in.is_open()) {
                throw runtime_error("Could not open the config file: " + path);
            }

            json jsonParser;
            in >> jsonParser;

            Config config;
            config.numberOfRuns = jsonParser.value("number_of_runs", NUMBER_OF_RUNS);
            config.populationMatrixSize = jsonParser.value("population_matrix_size", POPULATION_MATRIX_SIZE);
            config.numberOfGenerations = jsonParser.value("number_of_generations", NUMBER_OF_GENERATIONS);
            config.contagionFactor = jsonParser.value("contagion_factor", CONTAGION_FACTOR);
            config.requestedStateCount = jsonParser.value("requested_state_count", REQUESTED_STATE_COUNT);
            config.applySocialDistanceEffect = jsonParser.value("apply_social_distance_effect", APPLY_SOCIAL_DISTANCE_EFFECT);
            config.threadCount = jsonParser.value("thread_count", THREAD_COUNT);
            config.generateImage = jsonParser.value("generate_image", GENERATE_IMAGE);

            return config;
        }
};