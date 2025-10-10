#ifndef GIF_GENERATOR
#define GIF_GENERATOR

#include <vector>
#include <string>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "lib/StbImage.hh"
#include "lib/Gif.hh"

using namespace std;

class GifGenerator
{

public:
    static void generateGif(const vector<string> &frames, const string &outputPath, int width, int height, int delayMs)
    {
        GifWriter writer;

        if (!GifBegin(&writer, outputPath.c_str(), width, height, delayMs / 10))
        {
            throw runtime_error("ERROR: COULD NOT INITIALIZE GIF FILE.");
        }

        for (const auto &framePath : frames)
        {
            int w, h, channels;
            uint8_t *image = stbi_load(framePath.c_str(), &w, &h, &channels, 4);
            if (!image)
            {
                cerr << "Warning: Could not load frame: " << framePath << endl;
                continue;
            }

            if (w != width || h != height)
            {
                cerr << "Warning: Frame size mismatch in " << framePath << " (expected "
                     << width << "x" << height << ", got " << w << "x" << h << ")\n";
            }

            GifWriteFrame(&writer, image, width, height, delayMs / 10);
            stbi_image_free(image);
        }

        GifEnd(&writer);
        cout << "GIF gerado com sucesso em: " << outputPath << endl;
    }
};

#endif