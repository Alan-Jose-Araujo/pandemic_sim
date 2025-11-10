/**
 * RandomWalkModel.hpp
 * @author Alan José <alanjsdelima@gmail.com>
 *
 * The RandomWalkModel class defines a simulation model where agents move randomly.
 */

#ifndef RANDOM_WALK_MODEL_H
#define RANDOM_WALK_MODEL_H

#include "../rng/RandomNumberGenerator.hpp"
#include "./Individual.hpp"

using Population = std::vector<std::vector<simulator::Individual>>;

namespace simulator
{

    class RandomWalkModel
    {

        protected:

            rng::RandomNumberGenerator sequential_rng;

            Population population;

            Population next_population;

            std::vector<std::vector<double>> transition_probabilities;

            double contagion_factor;

            int population_matrix_size;

            bool apply_social_distance_effect;

            void initialize_population();

            void initialize_sick_individuals();

            void compute_social_interactions(int line, int column, rng::RandomNumberGenerator* rng);

            void individual_transition(int line, int column, rng::RandomNumberGenerator* rng);

            void next_generation();

        public:

            RandomWalkModel(
                int population_matrix_size,
                double contagion_factor,
                bool apply_social_distance_effect
            );

            void set_transition_probabilities(const std::vector<std::vector<double>>& probabilities);

            int get_state_count(const std::string& state);

            void generate_image(const std::string& images_directory);

            void simulate(int generations);
    };

};

#endif // RANDOM_WALK_MODEL_H