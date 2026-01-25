/**
 * @file directory_handler.hpp
 * @brief This entity is responsible by the directory handling.
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-25
 */

#pragma once

#include <string>

namespace Facades
{
    class FsHandler
    {
    public:
        static void createDirectoryIfNotExists(std::string path);

        static std::string generateTimestampedFilename(std::string imagesDir, const std::string basename);
    };
};