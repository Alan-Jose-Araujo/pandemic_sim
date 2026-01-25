/**
 * @file fs_handler_impl.cpp
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-25
 */

#include "facades/fs_handler.hpp"
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

namespace Facades
{
    void FsHandler::createDirectoryIfNotExists(std::string path)
    {
        try
        {
            if(!fs::exists(path)) {
                fs::create_directories(path);
            }
        }
        catch(const fs::filesystem_error &error)
        {
            throw error;
        }
    }

    std::string FsHandler::generateTimestampedFilename(std::string imagesDir, const std::string basename)
    {
        auto now = std::chrono::system_clock::now();
        auto nowTimeT = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        tm localTime = *std::localtime(&nowTimeT);
        std::ostringstream oss;
        
        oss << imagesDir << "/"
        << basename
        << std::put_time(&localTime, "%Y%m%d_%H%M%S")
        << "_" << std::setfill('0') << std::setw(3) << ms.count()
        << ".png";

        return oss.str();
    }
};