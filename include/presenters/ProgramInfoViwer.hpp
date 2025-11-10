/**
 * ProgramInfoViwer.hpp
 * @author Alan José <alanjsdelima@gmail.com>
 *
 * The program info viwer provides information about the program like: version, help, usage, etc.
 */

#ifndef PROGRAM_INFO_VIWER_H
#define PROGRAM_INFO_VIWER_H

namespace presenters
{

    class ProgramInfoViwer
    {

        private:

            const char VERSION[];

        public:

            void print_ASCII_art();

            // TODO: Define &Config instance as param.
            void print_headers();

            void print_help();

            void print_version();
    };
    

};

#endif // PROGRAM_INFO_VIWER_H