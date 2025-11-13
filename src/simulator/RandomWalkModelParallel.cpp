#include "../../include/simulator/RandomWalkModelParallel.hpp"
#include "../../include/simulator/RandomWalkModel.hpp"
#include "../../include/facades/Multithreading.hpp"
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <memory>

namespace simulator
{

    RandomWalkModelParallel::RandomWalkModelParallel(int population_matrix_size, double contagion_factor, bool apply_social_distance_effect, int thread_count)
    : RandomWalkModel(population_matrix_size, contagion_factor, apply_social_distance_effect), thread_count(thread_count)
    {
        this->current_processor_available_threads = facades::Multithreading::get_current_processor_available_threads();
        this->throw_exception_if_multithreading_is_not_supported();
        this->throw_exception_if_maximum_threads_is_exceeded();
    };

    void RandomWalkModelParallel::proccess_chunk(int start_row, int end_row, rng::RandomNumberGenerator* rng)
    {
        for(int i = start_row; i < end_row; ++i) {
            for(int j = 0; j < this->population_matrix_size; ++j) {
                this->individual_transition(i, j, rng);
            }
        }
    }

    void RandomWalkModelParallel::throw_exception_if_maximum_threads_is_exceeded()
    {
        if(this->thread_count > this->current_processor_available_threads) {
            throw std::out_of_range("[ERROR]: The requested threads count exceeds the current processor available threads.");
        }
    }

    void RandomWalkModelParallel::throw_exception_if_multithreading_is_not_supported()
    {
        if(thread_count == 0) {
            throw std::out_of_range("[ERROR]: The current processor does not supports multithreading, please remove the -t param.");
        }
    }

    void RandomWalkModelParallel::parallel_simulation(int generations)
    {
        std::vector<std::unique_ptr<rng::RandomNumberGenerator>> thread_rngs;

        for(int t = 0; t < this->thread_count; ++t) {
            thread_rngs.push_back(std::make_unique<rng::RandomNumberGenerator>(t + 1));
        }

        for(int g = 0; g < generations; ++g) {
            // Create threads to process chunks of the population grid.
            std::vector<std::thread> threads;
            int rows_per_thread = this->population_matrix_size / this->thread_count;
            int remaining_rows = this->population_matrix_size % this->thread_count;

            for(int t = 0; t < this->thread_count; ++t) {
                int start_row = t * rows_per_thread;
                int end_row = start_row + rows_per_thread + (t < remaining_rows ? 1 : 0);
                threads.emplace_back([this, start_row, end_row, rng_ptr = thread_rngs[t].get()]() {
                    this->proccess_chunk(start_row, end_row, rng_ptr);
                });
            }

            // Wait for all threads to finish.
            for(auto& t : threads) {
                t.join();
            }

            // Swap population data.
            this->population = this->next_population;
        }
    }

};