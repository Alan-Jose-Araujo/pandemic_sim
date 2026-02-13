#include <iostream>
#include "pandemic_sim/cli/cliparser.hpp"

int main(int argc, char* argv[])
{
    Cli::CliParser parser("MyApp");
    parser.parse(argc, argv);
    return EXIT_SUCCESS;
}