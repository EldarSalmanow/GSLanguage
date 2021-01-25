#ifndef GSLANGUAGE_GS_ARGUMENTS_H
#define GSLANGUAGE_GS_ARGUMENTS_H


#include <string>

#include "../../Exceptions/GS_ArgumentException.h"

namespace GSLanguageCompiler {

    class GS_Arguments {
    public:
        GS_Arguments(int argc, char *argv[]) {
            this->argc = argc;
            this->argv = argv;
        }

    public:
        void parseArguments();

    public:
        std::string &getFilename() {
            return this->_filename;
        }

    private:
        std::string _filename;

    private:
        int argc;
        char **argv;
    };

}


#endif //GSLANGUAGE_GS_ARGUMENTS_H
