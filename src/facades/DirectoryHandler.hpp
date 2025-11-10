#include "../../include/facades/DirectoryHandler.hpp"
#include <filesystem>
#include <iostream>
#include <sstream>
#include <chrono>

namespace fs = std::filesystem;

namespace facades
{

    void DirectoryHandler::create_directory_if_not_exists(std::string path)
    {
        try
        {
            if(!fs::exists(path)) {
                fs::create_directories(path);
            }
        }
        catch(const fs::filesystem_error &error)
        {
            std::cerr << "[FILESYSTEM ERROR]: " << error.what() << std::endl;
        }
    }

    std::string generate_timestamped_filename(std::string &images_dir, const std::string &base_name)
    {
        auto now = std::chrono::system_clock::now();
        auto now_time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        tm local_time = *std::localtime(&now_time_t);
        std::ostringstream oss;
        oss << images_dir << "/"
        << base_name
        << std::put_time(&local_time, "%Y%m%d_%H%M%S")
        << "_" << std::setfill('0') << std::setw(3) << ms.count()
        << ".png";

        return oss.str();
    }

};