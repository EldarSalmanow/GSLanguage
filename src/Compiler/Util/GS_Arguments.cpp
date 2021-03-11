#include "../../../include/Compiler/Util/GS_Arguments.h"

namespace GSLanguageCompiler {

    void GS_Arguments::parseArguments() {
        for (int index = 1; index < this->_argc; ++index) {
            std::string argument = this->_argv[index];
            if (argument == "-f" || argument == "--file") {
                ++index;
                if (this->_argc < index) {
                    throw Exceptions::GS_ArgumentException("Invalid argument \"" + argument + "\"!");
                }

                _Arguments::filename = _argv[index];

                continue;
            } else if (argument == "-h" || argument == "--help") {
                this->printUsage();

                break;
            } else if (argument == "-t" || argument == "--test") {
                _Arguments::isTestingEnable = true;

                continue;
            } else if (argument == "-p" || argument == "--profiling") {
                _Arguments::isProfilingEnable = true;

                continue;
            } else {
                    throw Exceptions::GS_ArgumentException("Invalid arguments!");
            }
        }
    }

    void GS_Arguments::printUsage() {
        std::cout
        << "Usage: \n"
        << "\t-f --file \tMain filename to compiling\n"
        << "\t-t --test \tPrinting information because compiling\n"
        << "\t-h --help \tInformation about flags and compiler\n"
        << std::endl;
    }

}