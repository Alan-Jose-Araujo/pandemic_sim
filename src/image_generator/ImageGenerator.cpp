#include "../../include/image_generator/ImageGenerator.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../vendor/stb_image_write.hpp"
#include <iostream>

namespace image_generator
{

    void ImageGenerator::generate(const char* file_name, Population& population)
    {
        // Get the population matrix dimensions
        const int lines = static_cast<int>(population.size());
        const int columns = static_cast<int>(population[0].size());

        const bool isolated_states_exists = simulator::Individual::valid_states.contains("isolated");

        // Create an RGB buffer to store the image
        std::vector<unsigned char> imageBuffer(lines * columns * 3, 0);

        // Iterate over the population matrix and set pixel colors based on the individual's state
        for (int i = 0; i < lines; ++i) {
            for (int j = 0; j < columns; ++j) {
                int index = (i * columns + j) * 3; // Calculate the buffer index

                int current_state = population[i][j].get_state();

                if(current_state == simulator::Individual::valid_states["healthy"]) {
                    // Green color.
                    imageBuffer[index + 0] = 0; // Red channel.
                    imageBuffer[index + 1] = 255; // Green channel.
                    imageBuffer[index + 2] = 0; // Blue channel.
                } else if(current_state == simulator::Individual::valid_states["sick"]) {
                    // Yellow color.
                    imageBuffer[index + 0] = 255;
                    imageBuffer[index + 1] = 255;
                    imageBuffer[index + 2] = 0;
                } else if(current_state == simulator::Individual::valid_states["dead"]) {
                    // Red color.
                    imageBuffer[index + 0] = 255;
                    imageBuffer[index + 1] = 0;
                    imageBuffer[index + 2] = 0;
                } else if(current_state == simulator::Individual::valid_states["immune"]) {
                    // Blue color.
                    imageBuffer[index + 0] = 0;
                    imageBuffer[index + 1] = 0;
                    imageBuffer[index + 2] = 255;

                } else if(isolated_states_exists && current_state == simulator::Individual::valid_states["isolated"]) {
                    // Black color.
                    imageBuffer[index + 0] = 0;
                    imageBuffer[index + 1] = 0;
                    imageBuffer[index + 2] = 0;
                } else {
                    std::cerr << "[ERROR]: Invalid state on image generation." << std::endl;
                }
            }
        }

        stbi_write_png(file_name, columns, lines, 3, imageBuffer.data(), columns * 3);
    }

};