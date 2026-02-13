#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>
#include "pandemic_sim/cli/cliparser.hpp"

struct ArgsWrapper {
    std::vector<std::string> args;
    std::vector<char*> argv;

    ArgsWrapper(const std::vector<std::string>& inputArgs) : args(inputArgs) {
        if (args.empty()) args.push_back("test_runner");

        for (const auto& arg : args) {
            argv.push_back(const_cast<char*>(arg.c_str()));
        }
        argv.push_back(nullptr);
    }

    int argc() const { return static_cast<int>(argv.size()) - 1; }
    int real_argc() const { return static_cast<int>(argv.size()) - 1; }
    char** argvPtr() { return argv.data(); }
};

TEST_CASE("CliParser: Flag type arguments (None)", "[cli][flags]")
{
    Cli::CliParser parser("Test App");
    bool verboseCalled = false;
    bool debugCalled = false;

    parser.addOption('v', "verbose", Cli::ArgType::None, "Verbose mode",
    [&](const std::optional<std::string>&) {
        verboseCalled = true;
    });

    parser.addOption('d', "debug", Cli::ArgType::None, "Debug mode",
    [&](const std::optional<std::string>&) {
        debugCalled = true;
    });

    SECTION("Must detect a short flag")
    {
        ArgsWrapper wrapper({"programa_teste", "-v"});
        parser.parse(wrapper.real_argc(), wrapper.argvPtr());
        REQUIRE(verboseCalled == true);
    }

    SECTION("Must detect a long flag")
    {
        ArgsWrapper wrapper({"programa_teste", "--debug"});
        parser.parse(wrapper.real_argc(), wrapper.argvPtr());
        REQUIRE(debugCalled == true);
    }

    SECTION("Must detect multiple flags together")
    {
        ArgsWrapper wrapper({"programa_teste", "-d", "-v"});
        parser.parse(wrapper.real_argc(), wrapper.argvPtr());
        REQUIRE(verboseCalled == true);
        REQUIRE(debugCalled == true);
    }
}

TEST_CASE("CliParser: Required type arguments (Required)", "[cli][required]")
{
    Cli::CliParser parser("Test App");
    std::string outputValue;

    parser.addOption('o', "output", Cli::ArgType::Required, "Output file",
    [&](const std::optional<std::string>& val) {
        if (val) outputValue = *val;
    });

    SECTION("Must capture the value with short flag")
    {
        ArgsWrapper wrapper({"prog", "-o", "data.txt"});
        parser.parse(wrapper.real_argc(), wrapper.argvPtr());
        REQUIRE(outputValue == "data.txt");
    }

    SECTION("Must capture the value with long flag and equals")
    {
        ArgsWrapper wrapper({"prog", "--output=result.json"});
        parser.parse(wrapper.real_argc(), wrapper.argvPtr());
        REQUIRE(outputValue == "result.json");
    }
}

TEST_CASE("CliParser: Optional type arguments (Optional)", "[cli][optional]")
{
    Cli::CliParser parser("Test App");
    bool callbackCalled = false;
    std::optional<std::string> capturedValue;

    parser.addOption('l', "log", Cli::ArgType::Optional, "Log file",
    [&](const std::optional<std::string>& val) {
        callbackCalled = true;
        capturedValue = val;
    });

    SECTION("Must works without provide value (just flag)")
    {
        ArgsWrapper wrapper({"prog", "--log"});
        parser.parse(wrapper.real_argc(), wrapper.argvPtr());
        REQUIRE(callbackCalled == true);
        REQUIRE(capturedValue.has_value() == false);
    }

    SECTION("Must works providing value (long syntax with =)")
    {
        ArgsWrapper wrapper({"prog", "--log=sys.log"});
        parser.parse(wrapper.real_argc(), wrapper.argvPtr());
        REQUIRE(callbackCalled == true);
        REQUIRE(capturedValue.has_value() == true);
        REQUIRE(*capturedValue == "sys.log");
    }

    SECTION("Must works providing value (short syntax without blank space)")
    {
        ArgsWrapper wrapper({"prog", "-lsys.log"});
        parser.parse(wrapper.real_argc(), wrapper.argvPtr());
        REQUIRE(callbackCalled == true);
        REQUIRE(capturedValue.has_value() == true);
        REQUIRE(*capturedValue == "sys.log");
    }
}