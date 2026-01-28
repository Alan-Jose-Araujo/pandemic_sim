/**
 * @file info_viwer_impl.cpp
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-27
 */

 #include "facades/info_viwer.hpp"
 #include "facades/multithread_controller.hpp"
 #include <functional>
 #include <iostream>

 namespace Facades
 {
    void InfoViwer::printASCIIArt()
    {
      std::cout << "__________                    .___             .__              _________.__         " << std::endl;
      std::cout << "\\______   \\_____    ____    __| _/____   _____ |__| ____       /   _____/|__| _____  " << std::endl;
      std::cout << " |     ___/\\__  \\  /    \\  / __ |/ __ \\ /     \\|  |/ ___\\      \\_____  \\ |  |/     \\ " << std::endl;
      std::cout << " |    |     / __ \\|   |  \\/ /_/ \\  ___/|  Y Y  \\  \\  \\___      /        \\|  |  Y Y  \\" << std::endl;
      std::cout << " |____|    (____  /___|  /\\____ |\\___  >__|_|  /__|\\___  >____/_______  /|__|__|_|  /" << std::endl;
      std::cout << "                \\/     \\/      \\/    \\/      \\/        \\/_____/       \\/          \\/ " << std::endl;
    }

    void InfoViwer::printHeaders(Facades::Config &config)
    {
      int populationMatrixSize = config.getPopulationMatrixSize();
      std::string applySocialDistanceEffectStr = config.getApplySocialDistanceEffect() ? "Yes" : "No";
      std::string generateImageOnFinishStr = config.getGenerateImage() ? "Yes" : "No";

      std::cout << "-------------------------------------------------------------------------------------------" << std::endl;
      this->printASCIIArt();
      std::cout << "-- Number of runs: " << config.getNumberOfRuns() << std::endl;
      std::cout << "-- Population matrix size: " << populationMatrixSize << " (" << populationMatrixSize * populationMatrixSize << " individuals)" << std::endl;
      std::cout << "-- Number of generations: " << config.getNumberOfGenerations() << std::endl;
      std::cout << "-- Disease contagion factor: " << config.getContagionFactor() << std::endl;
      std::cout << "-- Social distance effect applyied: " << applySocialDistanceEffectStr << std::endl;
      std::cout << "-- Threads: " << config.getThreadCount() << std::endl;
      std::cout << "-- Generate visual example image on finish: " << generateImageOnFinishStr << std::endl;
      std::cout << "-------------------------------------------------------------------------------------------" << std::endl;
    }

    void InfoViwer::printHelp()
    {
      printASCIIArt();
      std::cout << "-------------------------------------------------------------------------------------------" << std::endl;
      std::cout << "Usage: simulator [-v | --version] [-h | --help] [-r | --runs <value>] [-p | --population <value>]" << std::endl;
      std::cout << "                 [-g | --generations <value>] [-s | --social-distance-effect] [-t | --threads <value>]" << std::endl;
      std::cout << "                 [-c | --contagion-factor <value>] [-o | --output-state <value>] [-i | --image]" << std::endl;
      std::cout << "                 [-f | --config-file <value>]]" << std::endl;
      std::cout << "\n" << std::endl;
      std::cout << "Multithreading is available : " << (Facades::MultithreadController::currentProcessorSupportsMultithreading() ? "Yes" : "No") << "." << std::endl;
      std::cout << "CPU Threads available       : " << Facades::MultithreadController::getCurrentProcessorAvailableThreads() << "." << std::endl;
      std::cout << "\n" << std::endl;
      std::cout << "Individual states           : " << std::endl;
      std::cout << "Healthy                     : " << "0" << std::endl;
      std::cout << "Isolated                    : " << "1" << std::endl;
      std::cout << "Sick                        : " << "2" << std::endl;
      std::cout << "Dead                        : " << "3" << std::endl;
      std::cout << "Immune                      : " << "4" << std::endl;
      std::cout << "\n" << std::endl;
      std::cout << "Parameter descriptions        :" << std::endl;
      std::cout << "-v | --version                :       Show the program version." << std::endl;
      std::cout << "-h | --help                   :       Show this message." << std::endl;
      std::cout << "-r | --runs                   :       Define how many times the model will be executed, determining the number of results (integer)." << std::endl;
      std::cout << "-p | --population             :       Define the population matrix side length. Use the square root, e.g., 100 corresponds to 10,000 (integer)." << std::endl;
      std::cout << "-g | --generations            :       Specify the number of generations in weeks (integer)." << std::endl;
      std::cout << "-s | --social-distance-effect :       Run the simulations with the social distancing/lockdown effect applied, reducing the disease contagion factor." << std::endl;
      std::cout << "-t | --threads                :       Run the simulations with a multi-threaded profile. Specifies the number of threads the program may use. The maximum value is the number of threads available on the current processor (integer)." << std::endl;
      std::cout << "-c | --contagion-factor       :       Defines the disease contagion factor, minimum 0.1, maximum 1 (double)." << std::endl;
      std::cout << "-o | --output-state           :       Defines the state for which you want to obtain the number of affected individuals (integer)." << std::endl;
      std::cout << "-f | --config-file            :       Set the .json config file. Check the docs to see the file standard." << std::endl;
      std::cout << "-i | --image                  :       Generate a visual disease spread example as a .png image." << std::endl;
      std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
      std::cout << "Default params: r(1000), p(100), g(10), c(0.5), o(3), s(false), t(1), i(false)" << std::endl;
    }

    void InfoViwer::printVersion()
    {
      printASCIIArt();
      std::cout << "-------------------------------------------------------------------------------------------" << std::endl;
      std::cout << "Pandemic Sim version " << VERSION << std::endl;
      std::cout << "Author: Alan Jose <alanjsdelima@gmail.com>"<< std::endl;
    }
 };