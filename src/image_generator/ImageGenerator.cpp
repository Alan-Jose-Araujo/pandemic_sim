#include "../../include/image_generator/ImageGenerator.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../vendor/stb_image_write.hpp"
#include <iostream>

namespace image_generator
{

    ImageGenerator::static void generate(const char* name, Population& population)
    {
        // Get the population matrix dimensions
        const int lines = static_cast<int>(population.size());
        const int columns = static_cast<int>(population[0].size());

        // Create an RGB buffer to store the image
        std::vector<unsigned char> image_buffer(lines * columns * 3, 0);

        // Iterate over the population matrix and set pixel colors based on the individual's state
        for (int i = 0; i < lines; ++i) {
            for (int j = 0; j < columns; ++j) {
                int index = (i * columns + j) * 3; // Calculate the buffer index

                switch (population[i][j].get_state()) {
                    case Individual::valid_states["healthy"]:
                        image_buffer[index + 0] = 0; // Red
                        image_buffer[index + 1] = 255; // Green
                        image_buffer[index + 2] = 0; // Blue
                        break;

                    // TODO: Handle isolated condition.
                    // case State::isolated:
                    //     image_buffer[index + 0] = 0;
                    //     image_buffer[index + 1] = 0;
                    //     image_buffer[index + 2] = 0;
                    //     break;

                    case Individual::valid_states["sick"]:
                        image_buffer[index + 0] = 255;
                        image_buffer[index + 1] = 255;
                        image_buffer[index + 2] = 0;
                        break;

                    case Individual::valid_states["dead"]:
                        image_buffer[index + 0] = 255;
                        image_buffer[index + 1] = 0;
                        image_buffer[index + 2] = 0;
                        break;

                    case Individual::valid_states["imune"]:
                        image_buffer[index + 0] = 0;
                        image_buffer[index + 1] = 0;
                        image_buffer[index + 2] = 255;
                        break;

                    default:
                        std::cerr << "[ERROR]: Invalid state on image generation." << endl;
                        break;
                }
            }
        }

        stbi_write_png(name, columns, lines, 3, image_buffer.data(), columns * 3);
    }

};