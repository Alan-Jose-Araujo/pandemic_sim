/**
 * RandomWalkModelParallel.hpp
 * @author Alan José <alanjsdelima@gmail.com>
 *
 * The RandomWalkModelParallel class uses the base model in multithreading mode.
 */

#ifndef RANDOM_WALK_MODEL_PARALLEL_H
#define RANDOM_WALK_MODEL_PARALLEL_H

#include "./RandomWalkModel.hpp"
#include "../rng/RandomNumberGenerator.hpp"

namespace simulator
{

    class RandomWalkModelParallel: public RandomWalkModel
    {

        private:

            int thread_count;

            int current_processor_available_threads;

            void proccess_chunk(int start_row, int end_row, rng::RandomNumberGenerator* rng);

            void throw_exception_if_maximum_threads_is_exceeded();

            void throw_exception_if_multithreading_is_not_supported();

        public:

            using RandomWalkModel::RandomWalkModel;

            RandomWalkModelParallel(int population_matrix_size, double contagion_factor, bool apply_social_distance_effect, int thread_count);

            void parallel_simulation(int generations);
    };

};

#endif