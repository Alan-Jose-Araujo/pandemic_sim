#ifndef DIRECTORY_HANDLER_H
#define DIRECTORY_HANDLER_H

#include <filesystem>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>

namespace fs = std::filesystem;
using namespace std;

class DirectoryHandler {

    public:

        static void createDirectoryIfNotExists(string path)
        {
            try {
                if(!fs::exists(path)) {
                    fs::create_directories(path);
                }
            }
            catch(const fs::filesystem_error& error) {
                cerr << "FILESYSTEM ERROR: " << error.what() << endl;
            }
        }

        static string generateTimestampedFilename(string& imagesDir, const string& baseName)
        {
            using namespace chrono;

            auto now = system_clock::now();
            auto nowTimeT = system_clock::to_time_t(now);
            auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

            tm localTime = *std::localtime(&nowTimeT);
            ostringstream oss;
            oss << imagesDir << "/"
            << baseName
            << put_time(&localTime, "%Y%m%d_%H%M%S")
            << "_" << setfill('0') << std::setw(3) << ms.count()
            << ".png";
            
            return oss.str();
        }

};

#endif