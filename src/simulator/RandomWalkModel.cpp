#include "../../include/simulator/RandomWalkModel.hpp"

namespace simulator
{

    RandomWalkModel::RandomWalkModel(
        int population_matrix_size,
        double contagion_factor,
        bool apply_social_distance_effect
    ) : population_matrix_size(population_matrix_size),
        contagion_factor(contagion_factor),
        apply_social_distance_effect(apply_social_distance_effect),
        sequential_rng()
    {
        this->initialize_population();
        this->initialize_sick_individuals();
    }

    void RandomWalkModel::initialize_population()
    {
        this->population.resize(
            this->population_matrix_size,
            std::vector<Individual>(this->population_matrix_size, Individual("healthy"))
        );
        this->next_population = this->population;
    }

    void RandomWalkModel::initialize_sick_individuals()
    {
        int start_index = this->population_matrix_size / 2;
        this->population[start_index][start_index].set_state("sick");
        this->next_population[start_index][start_index].set_state("sick");
    }

    void RandomWalkModel::compute_sick_contact(Individual& individual, Individual& neighbour, rng::RandomNumberGenerator* rng)
    {
        if(individual.get_state() == Individual::valid_states["dead"]) return;

        double random_number = rng->get_random_number();

        if(random_number < this->contagion_factor) {
            individual.set_state("sick");
        }
    }

    void RandomWalkModel::compute_social_interactions(int line, int column, rng::RandomNumberGenerator* rng)
    {
        int initial_line = std::max(0, line - 1);
        int final_line = std::min(line + 2, this->population_matrix_size);
        int isolated_count = 0;

        for(int i = initial_line; i < final_line; ++i) {
            int initial_column = std::max(0, column - 1);
            int final_column = std::min(column + 2, this->population_matrix_size);

            for(int j = initial_column; j < final_column; ++j) {
                Individual& neighbour = this->population[i][j];

                if(neighbour.get_state() == Individual::valid_states["isolated"] && this->apply_social_distance_effect) {
                    isolated_count++;
                }

                if(neighbour.get_state() == Individual::valid_states["sick"]) {
                    this->compute_sick_contact(next_population[line][column], neighbour, rng);
                }
            }
        }
    }

    void RandomWalkModel::individual_transition(int line, int column, rng::RandomNumberGenerator* rng)
    {
        Individual& individual = population[line][column];

        if(individual.get_state() == Individual::valid_states["dead"]) {
            return;
        }

        if(individual.get_state() == Individual::valid_states["healthy"]) {
            this->compute_social_interactions(line, column, rng);
        } else {
            const std::vector<double>& probabilities = this->transition_probabilities[individual.get_state()];
            double random_number = rng->get_random_number();
            double cumulative_probability = 0.0;

            for(size_t i = 0; i < probabilities.size(); ++i) {
                cumulative_probability += probabilities[i];
                if(random_number <= cumulative_probability) {
                    this->next_population[line][column].set_state(i);
                    break;
                }
            }
        }
    }

    void RandomWalkModel::next_generation()
    {
        for(int i = 0; i < this->population_matrix_size; ++i) {
            for(int j = 0; j < this->population_matrix_size; ++j) {
                this->individual_transition(i, j, &this->sequential_rng);
            }
        }
        this->population = this->next_population;
    }

    void RandomWalkModel::set_transition_probabilities(const std::vector<std::vector<double>>& probabilities)
    {
        this->transition_probabilities = transition_probabilities;
    }

    int RandomWalkModel::get_state_count(const int state)
    {
        int cumulated = 0;
        for(const auto &row : this->population) {
            for(const auto &individual : row) {
                if(individual.get_state() == state) {
                    cumulated++;
                }
            }
        }
        return cumulated;
    }

    void RandomWalkModel::generate_image(const std::string& images_directory)
    {
        //
    }

    void RandomWalkModel::simulate(int generations)
    {
        for(int i = 0; i < generations; ++i) {
            this->next_generation();
        }
    }

};