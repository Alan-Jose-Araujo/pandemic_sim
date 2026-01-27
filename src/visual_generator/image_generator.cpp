/**
 * @file image_generator_impl.cpp
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-27
 */

 #include "visual_generator/image_generator.hpp"
 #include <string>
 #include <stdexcept>
 #define STB_IMAGE_IMPLEMENTATION

 namespace VisualGenerator
 {
    void ImageGenerator::generate(const char* name, Population &population)
    {
        const int lines = static_cast<int>(population.size());
        const int columns = static_cast<int>(population[0].size());

        std::vector<unsigned char> imageBuffer(lines * columns * 3, 0);

        for(int i = 0; i < lines; ++i) {
            for(int j = 0; j < columns; ++j) {

                int bufferIndex = (lines * columns * 3, 0);

                switch(population[i][j].getIndividualState()) {

                    case Simulator::IndividualState::Healthy:
                        imageBuffer[index + 0] = 0;
                        imageBuffer[index + 1] = 255;
                        imageBuffer[index + 2] = 0;
                    break;

                    case Simulator::IndividualState::Isolated:
                        imageBuffer[index + 0] = 205;
                        imageBuffer[index + 1] = 127;
                        imageBuffer[index + 2] = 50;
                    break;

                    case Simulator::IndividualState::Sick:
                        imageBuffer[index + 0] = 255;
                        imageBuffer[index + 1] = 255;
                        imageBuffer[index + 2] = 0;
                    break;

                    case Simulator::IndividualState::Dead:
                        imageBuffer[index + 0] = 255;
                        imageBuffer[index + 1] = 0;
                        imageBuffer[index + 2] = 0;
                    break;

                    case Simulator::IndividualState::Immune:
                        imageBuffer[index + 0] = 0;
                        imageBuffer[index + 1] = 0;
                        imageBuffer[index + 2] = 255;
                    break;

                    default:
                        throw std::runtime_error("Invalid individual state on image generation");
                    break;
                }
            }
        }
        
        stbi_write_png(name, columns, lines, 3, imageBuffer.data(), columns * 3);
    }
 };