/**
 * Individual.hpp
 * @author Alan José <alanjsdelima@gmail.com>
 * 
 * The Config class will provide a interface to set the simulator params.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <string>

namespace simulator
{

    class Config
    {
        
        private:

            int number_of_runs;

            int population_matrix_size;

            int number_of_generations;

            double contagion_factor;

            int requested_state_count;

            bool apply_social_distance_effect;

            int thread_count;

            bool generate_image;

            std::vector<std::vector<double>> transition_probabilities;

        public:

            Config(
                int number_of_runs,
                int population_matrix_size,
                int number_of_generations,
                double contagion_factor,
                int requested_state_count,
                bool apply_social_distance_effect,
                int thread_count,
                bool generate_image,
                std::vector<std::vector<double>> transition_probabilities
            );

            static Config build_from_config_file(const std::string &file_path);

            int get_number_of_runs() const;

            int get_population_matrix_size() const;

            int get_number_of_generations() const;

            double get_contagion_factor() const;

            int get_requested_state_count() const;

            bool get_apply_social_distance_effect() const;

            int get_thread_count() const;

            bool get_generate_image() const;

            const std::vector<std::vector<double>> &get_transition_probabilities() const;
    };
    

};

#endif // CONFIG_H