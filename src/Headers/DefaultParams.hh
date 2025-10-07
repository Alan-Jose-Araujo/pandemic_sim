#ifndef DEFAULT_PARAMS
#define DEFAULT_PARAMS
#endif

#include <vector>
#include "State.hh"

#define NUMBER_OF_RUNS 1000
#define POPULATION_MATRIX_SIZE 100
#define NUMBER_OF_GENERATIONS 10
#define CONTAGION_FACTOR 0.5
#define REQUESTED_STATE_COUNT (int) State::dead
#define APPLY_SOCIAL_DISTANCE_EFFECT false
#define THREAD_COUNT 1
#define GENERATE_IMAGE false

std::vector<std::vector<double>> TRANSITION_PROBABILITIES = {
    {0.62, 0.3, 0.05, 0.0, 0.03}, // healthy
    {0.05, 0.64, 0.1, 0.01, 0.2}, // isolated
    {0.0, 0.1, 0.65, 0.1, 0.15},  // sick
    {0.0, 0.0, 0.0, 1.0, 0.0},    // dead
    {0.0, 0.05, 0.02, 0.0, 0.93}  // immune
};