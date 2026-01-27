/**
 * @file multithread_controller.hpp
 * @brief Multithread relative functions.
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-26
 */

#pragma once

#include <thread>

namespace Facades
{
    class MultithreadController
    {
        public:
            static int getCurrentProcessorAvailableThreads();

            static bool currentProcessorSupportsMultithreading();
    };
};