#ifndef DIRECTORY_HANDLER_H
#define DIRECTORY_HANDLER_H

#include <filesystem>
#include <string>
#include <iostream>

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

};

#endif