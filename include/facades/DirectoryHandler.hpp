/**
 * DirectoryHandler.hpp
 * @author Alan José <alanjsdelima@gmail.com>
 *
 * The DirectoryHandler handle the program output files.
 */

#ifndef DIRECTORY_HANDLER_H
#define DIRECTORY_HANDLER_H

#include <string>

namespace facades
{

    class DirectoryHandler
    {

        public:

            static void create_directory_if_not_exists(std::string path);

            static std::string generate_timestamped_filename(std::string &images_dir, const std::string &base_name);

    };
    

};

#endif // DIRECTORY_HANDLER_H