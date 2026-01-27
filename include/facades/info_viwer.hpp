/**
 * @file info_viwer.hpp
 * @brief Here houses the informations "about" the program, e.g: version, help, headers, etc...
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-27
 */

#pragma once

#include "facades/config.hpp"
#include <string>

namespace Facades
{
    class InfoViwer
    {
        public:
            const std::string VERSION = "1.0.0";

            void printASCIIArt();

            void printHeaders(Facades::Config &config);

            void printHelp();

            void printVersion();
    };
};