/**
 * ImageGenerator.hpp
 * @author Alan José <alanjsdelima@gmail.com>
 *
 * The ImageGenerator creates the visual example images.
 */

#ifndef IMAGE_GENERATOR_H
#define IMAGE_GENERATOR_H

#include "../simulator/Individual.hpp"
#include <vector>

using Population = std::vector<std::vector<simulator::Individual>>;

namespace image_generator
{
    
    class ImageGenerator
    {

        public:

            static void generate(const char* file_name, Population& population);

    };

};

#endif