#include "../../include/facades/Multithreading.hpp"

#include <thread>

namespace facades
{

    int Multithreading::get_current_processor_available_threads()
    {
        return std::thread::hardware_concurrency();
    }

    bool Multithreading::current_processor_supports_multithreading()
    {
        return Multithreading::get_current_processor_available_threads() > 1;
    }

};