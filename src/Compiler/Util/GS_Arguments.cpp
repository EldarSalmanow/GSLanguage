#include "../../../include/Compiler/Util/GS_Arguments.h"

namespace GSLanguageCompiler {

    void GS_Arguments::parseArguments() {
        for (int index = 0; index < this->argc; ++index) {
            std::string argument = this->argv[index];
            if (argument == "-f" || argument == "--file") {
                ++index;
                this->_filename = argv[index];
            } else if (argument == "-h" || argument == "--help") {
                this->printUsage();
                break;
            }
        }
    }

    void GS_Arguments::printUsage() {
        std::cout
        << "Usage: \n"
        << "\t-f --file \tMain filename to compiling\n"
        << "\t-h --help \tInformation about flags and compiler\n"
        << std::endl;
    }

}