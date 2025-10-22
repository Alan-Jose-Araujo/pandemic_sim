#include <getopt.h>
#include <memory>
#include <string>
#include "Headers/RandomWalkModel.hh"
#include "Headers/RandomWalkModelParallel.hh"
#include "Headers/State.hh"
#include "Headers/ProgramInfoViewer.hh"
#include "Headers/Config.hh"
#include "Headers/DirectoryHandler.hh"

#define STATE_COUNT 5

using namespace std;

int main(int argc, char* argv[])
{
    //Default params.
    int numberOfRuns = NUMBER_OF_RUNS;
    int populationMatrixSize = POPULATION_MATRIX_SIZE;
    int numberOfGenerations = NUMBER_OF_GENERATIONS;
    double contagionFactor = CONTAGION_FACTOR;
    int requestedStateCount = REQUESTED_STATE_COUNT;
    bool applySocialDistanceEffect = APPLY_SOCIAL_DISTANCE_EFFECT;
    int threadCount = THREAD_COUNT;
    bool generateImage = GENERATE_IMAGE;
    string imagesDirectory = "./";
    int imageFramesInterval = 0;
    Config config;
    
    //Parse CLI options.
    //Don't move.
    const char* shortOptions = "r:p:g:st:c:o:f:ihv";
    const option longOptions[] = {
        {"runs", optional_argument, nullptr, 'r'},
        {"population", optional_argument, nullptr, 'p'},
        {"generations", optional_argument, nullptr, 'g'},
        {"social-distance-effect", no_argument, nullptr, 's'},
        {"threads", optional_argument, nullptr, 't'},
        {"contagion-factor", optional_argument, nullptr, 'c'},
        {"output-state", optional_argument, nullptr, 'o'},
        {"config-file", optional_argument, nullptr, 'f'},
        {"image", no_argument, nullptr, 'i'},
        {"output-image-path", optional_argument, nullptr, 0},
        {"image-frames-interval", optional_argument, nullptr, 0},
        {"version", no_argument, nullptr, 'v'},
        {"help", no_argument, nullptr, 'h'},
        {nullptr, no_argument, nullptr, 0}
    };
    int cliOption;
    int optionIndex = 0;
    while ((cliOption = getopt_long(argc, argv, shortOptions, longOptions, &optionIndex)) != -1) {
    switch (cliOption) {
        case 'r': {
            if (optarg == nullptr && optind < argc && argv[optind][0] != '-') {
                optarg = argv[optind++];
            }
            numberOfRuns = stoi(optarg);
        } break;
        case 'p': {
            if (optarg == nullptr && optind < argc && argv[optind][0] != '-') {
                optarg = argv[optind++];
            }
            populationMatrixSize = stoi(optarg);
        } break;
        case 'g': {
            if (optarg == nullptr && optind < argc && argv[optind][0] != '-') {
                optarg = argv[optind++];
            }
            numberOfGenerations = stoi(optarg);
        } break;
        case 's': {
            applySocialDistanceEffect = true;
        } break;
        case 't': {
            if (optarg == nullptr && optind < argc && argv[optind][0] != '-') {
                optarg = argv[optind++];
            }
            try {
                int requestedThreadCount = stoi(optarg);
                if (requestedThreadCount < 1) {
                    throw out_of_range("ERROR: THE REQUESTED THREADS COUNT IS LESS THAN 1.");
                }
                threadCount = requestedThreadCount;
            } catch (const out_of_range& exception) {
                cerr << exception.what() << endl;
                exit(EXIT_FAILURE);
            }
        } break;
        case 'c': {
            if (optarg == nullptr && optind < argc && argv[optind][0] != '-') {
                optarg = argv[optind++];
            }
            try {
                const double MIN_CONTAGION_FACTOR = 0.0;
                const double MAX_CONTAGION_FACTOR = 1.0;
                double givenContagionFactor = stod(optarg);
                if (givenContagionFactor < MIN_CONTAGION_FACTOR || givenContagionFactor > MAX_CONTAGION_FACTOR) {
                    throw out_of_range("ERROR: The contagion factor must be between " +
                                       to_string(MIN_CONTAGION_FACTOR) + " and " +
                                       to_string(MAX_CONTAGION_FACTOR) + ".");
                }
                contagionFactor = givenContagionFactor;
            } catch (const invalid_argument&) {
                cerr << "Error: Invalid argument for -c. Expected a double.\n" << endl;
            } catch (const out_of_range& exception) {
                cerr << exception.what() << endl;
                exit(EXIT_FAILURE);
            }
        } break;
        case 'o': {
            if (optarg == nullptr && optind < argc && argv[optind][0] != '-') {
                optarg = argv[optind++];
            }
            try {
                int requestedStateValue = stoi(optarg);
                int stateEnumValuesCount = 5;
                if (requestedStateValue < 0 || requestedStateValue > stateEnumValuesCount) {
                    throw out_of_range("ERROR: Invalid state: " + to_string(requestedStateValue) + ".");
                }
                requestedStateCount = requestedStateValue;
            } catch (const out_of_range& exception) {
                cerr << exception.what() << endl;
                exit(EXIT_FAILURE);
            }
        } break;
        case 'f': {
            if (optarg == nullptr && optind < argc && argv[optind][0] != '-') {
                optarg = argv[optind++];
            }
            try {
                string configFilePath = string(optarg);
                config = Config::buildFromConfigFile(configFilePath);

                numberOfRuns = config.numberOfRuns;
                populationMatrixSize = config.populationMatrixSize;
                numberOfGenerations = config.numberOfGenerations;
                contagionFactor = config.contagionFactor;
                requestedStateCount = config.requestedStateCount;
                applySocialDistanceEffect = config.applySocialDistanceEffect;
                threadCount = config.threadCount;
                generateImage = config.generateImage;
            }
            catch(const runtime_error& exception)
            {
                cerr << exception.what() << endl;
                exit(EXIT_FAILURE);
            }
            
        } break;
        case 'i': {
            generateImage = true;
        } break;
        case 'h':
            printHelp();
            exit(EXIT_SUCCESS);
        case 'v':
            printVersion();
            exit(EXIT_SUCCESS);
        case 0:
            if(string(longOptions[optionIndex].name) == "output-image-path") {
                if(optarg) {
                    imagesDirectory = string(optarg);
                } else {
                    imagesDirectory = "./";
                }
            }

            if (string(longOptions[optionIndex].name) == "image-frames-interval") {
                imageFramesInterval = optarg ? stoi(optarg) : 0;
                cout << "Frame interval set to: " << imageFramesInterval << endl;
            }
        break;
        default:
            cerr << "Unknown option. Use -h for usage information.\n";
            exit(EXIT_FAILURE);
    }
}

    vector<vector<double>> transitionProbabilities = TRANSITION_PROBABILITIES;
    bool isMultiThreading = threadCount > 1;

    printHeaders(
        new int[4]{numberOfRuns, populationMatrixSize, numberOfGenerations, threadCount},
        new bool[2]{applySocialDistanceEffect, generateImage},
        new double[1]{contagionFactor}
    );

    /**
     * Executes the model.
     */
    try
    {
        int transitionProbabilitiesSize = transitionProbabilities.size();
        if(transitionProbabilitiesSize != STATE_COUNT) {
            throw new runtime_error("ERROR: THE TRANSITION PROBABILITIES PROVIDED DIFFER FROM THE NUMBER OF INDIVIDUAL STATES.");
        }

        if(isMultiThreading) {
            unique_ptr<RandomWalkModelParallel> model;
            for(int i = 0; i < numberOfRuns; ++i) {
                model = make_unique<RandomWalkModelParallel>(populationMatrixSize, contagionFactor, applySocialDistanceEffect, threadCount);
                model->setTransitionProbabilities(transitionProbabilities);
                model->parallelSimulation(numberOfGenerations);
                //Print the individuals count based on current state.
                cout << model->getStateCount(State(requestedStateCount)) << endl;
                if (generateImage && imageFramesInterval > 0 && ((i + 1) % imageFramesInterval == 0)) {
                    DirectoryHandler::createDirectoryIfNotExists(imagesDirectory);
                    model->generateImage(imagesDirectory);
                }
            }
            if(generateImage && imageFramesInterval == 0) {
                DirectoryHandler::createDirectoryIfNotExists(imagesDirectory);
                model->generateImage(imagesDirectory);
                cout << "Final visual example saved at: " << imagesDirectory << endl;
            }
        }
        else {
            unique_ptr<RandomWalkModel> model;
            for(int i = 0; i < numberOfRuns; ++i) {
                model = make_unique<RandomWalkModel>(populationMatrixSize, contagionFactor, applySocialDistanceEffect);
                model->setTransitionProbabilities(transitionProbabilities);
                model->simulation(numberOfGenerations);
                //Print the individuals count based on current state.
                cout << model->getStateCount(State(requestedStateCount)) << endl;
                if (generateImage && imageFramesInterval > 0 && ((i + 1) % imageFramesInterval == 0)) {
                    DirectoryHandler::createDirectoryIfNotExists(imagesDirectory);
                    model->generateImage(imagesDirectory);
                }
            }
            if(generateImage && imageFramesInterval == 0) {
                DirectoryHandler::createDirectoryIfNotExists(imagesDirectory);
                model->generateImage(imagesDirectory);
                cout << "Final visual example saved at: " << imagesDirectory << endl;
            }
        }

        return EXIT_SUCCESS;
    }
    catch(invalid_argument& exception)
    {
        cerr << exception.what() << endl;
        abort();
    }
    catch(out_of_range& exception)
    {
        cerr << exception.what() << endl;
        abort();
    }
    catch(exception& exception)
    {
        cerr << exception.what() << endl;
        abort();
    }
}