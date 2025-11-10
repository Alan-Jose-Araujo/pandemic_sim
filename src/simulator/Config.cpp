#include "../../include/simulator/Config.hpp"

namespace simulator
{

    Config::Config(
        int number_of_runs,
        int population_matrix_size,
        int number_of_generations,
        double contagion_factor,
        int requested_state_count,
        bool apply_social_distance_effect,
        int thread_count,
        bool generate_image,
        std::vector<std::vector<double>> transition_probabilities
    ) : number_of_runs(number_of_runs),
        population_matrix_size(population_matrix_size),
        number_of_generations(number_of_generations),
        contagion_factor(contagion_factor),
        requested_state_count(requested_state_count),
        apply_social_distance_effect(apply_social_distance_effect),
        thread_count(thread_count),
        generate_image(generate_image),
        transition_probabilities(transition_probabilities)
        {}

    int Config::get_number_of_runs() const
    {
        return number_of_runs;
    }

    int Config::get_population_matrix_size() const
    {
        return population_matrix_size;
    }

    int Config::get_number_of_generations() const
    {
        return number_of_generations;
    }

    double Config::get_contagion_factor() const
    {
        return contagion_factor;
    }

    int Config::get_requested_state_count() const
    {
        return requested_state_count;
    }

    bool Config::get_apply_social_distance_effect() const
    {
        return apply_social_distance_effect;
    }

    int Config::get_thread_count() const
    {
        return thread_count;
    }

    bool Config::get_generate_image() const
    {
        return  generate_image;
    }

    const std::vector<std::vector<double>> &Config::get_transition_probabilities() const
    {
        return transition_probabilities;
    }

};