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

                this->_arguments.filename = _argv[index];

                continue;
            } else if (argument == "-h" || argument == "--help") {
                this->printUsage();

                break;
            } else if (argument == "-t" || argument == "--test") {
                this->_arguments.isTestingMode = true;

                ++index;
                if (this->_argc < index) {
                    throw Exceptions::GS_ArgumentException("Invalid argument \"" + argument + "\"!");
                }

                if (this->_argv[index] == "-tModeAll") {
                    this->_arguments.isTestingLexer = true;
                } else if (this->_argv[index] == "-tModeLexer") {
                    this->_arguments.isTestingLexer = true;
                }

                continue;
            } else {
                throw Exceptions::GS_ArgumentException("Invalid arguments!");
            }
        }
    }

    void GS_Arguments::printUsage() {
        std::cout
        << "Usage: \n"
        << "\t-f --file \tMain _filename to compiling\n"
        << "\t-t --test \tPrinting information because compiling\n"
        << "\t-h --help \tInformation about flags and compiler\n"
        << std::endl;
    }

}