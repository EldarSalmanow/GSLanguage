#include "../../../include/Compiler/Util/GS_Arguments.h"

namespace GSLanguageCompiler {
    void GS_Arguments::parseArguments() {
        for (int index = 0; index < this->argc; ++index) {
            std::string argument = this->argv[index];
            if (argument == "-f" || argument == "-file") {
                ++index;
                this->_filename = argv[index];
            }
        }
    }
}