/**
 * @file image_generator.hpp
 * @brief A image generator to create simulator visual examples.
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-27
 */

 #pragma once

#include "simulator/individual.hpp"
#include <vector>

 namespace VisualGenerator
 {
    class ImageGenerator
    {
      public:
         using Population = std::vector<std::vector<Simulator::Individual>>;

         static void generate(const char* name, Population &population);
    };
 };