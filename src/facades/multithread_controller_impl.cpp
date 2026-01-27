/**
 * @file multithread_controller_impl.cpp
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-26
 */

#include "facades/multithread_controller.hpp"

namespace Facades
{
    int MultithreadController::getCurrentProcessorAvailableThreads()
    {
        return std::thread::hardware_concurrency();
    }

    bool MultithreadController::currentProcessorSupportsMultithreading()
    {
        return std::thread::hardware_concurrency() > 1;
    }
};