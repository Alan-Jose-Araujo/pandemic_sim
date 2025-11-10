/**
 * Multithreading.hpp
 * @author Alan José <alanjsdelima@gmail.com>
 *
 * The Multithreading facade handles multithreading operations.
 */

#ifndef MULTITHREADING_H
#define MULTITHREADING_H

namespace facades
{

    class Multithreading
    {

        public:

            static int get_current_processor_available_threads();

            static bool current_processor_supports_multithreading();

    };

};

#endif