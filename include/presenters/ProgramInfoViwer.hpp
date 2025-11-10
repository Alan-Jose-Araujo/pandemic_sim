/**
 * ProgramInfoViwer.hpp
 * @author Alan José <alanjsdelima@gmail.com>
 *
 * The program info viwer provides information about the program like: version, help, usage, etc.
 */

#ifndef PROGRAM_INFO_VIWER_H
#define PROGRAM_INFO_VIWER_H

#include "../simulator/Config.hpp"

namespace presenters
{

    class ProgramInfoViwer
    {

        public:

            static const char VERSION[10];

            static void print_ASCII_art();

            static void print_headers(simulator::Config &config);

            static void print_help();

            static void print_version();
    };
    

};

#endif // PROGRAM_INFO_VIWER_H