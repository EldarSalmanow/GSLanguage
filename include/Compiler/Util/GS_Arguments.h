#ifndef GSLANGUAGE_GS_ARGUMENTS_H
#define GSLANGUAGE_GS_ARGUMENTS_H


#include <string>

#include "../../Exceptions/GS_ArgumentException.h"

namespace GSLanguageCompiler {

    /**
     * Class for parsing command line arguments and generate config of compiling
     */
    class GS_Arguments {
    public:

        /**
         * Constructor for GS_Arguments
         * @param argc Number of command line arguments
         * @param argv Array of command line arguments
         */
        GS_Arguments(int argc, char *argv[]) {
            this->argc = argc;
            this->argv = argv;
        }

    public:

        /**
         * Function for parsing arguments and generate config of project
         */
        void parseArguments();

    public:

        /**
         * Getter for _filename
         * @return Input filename
         */
        std::string &getFilename() {
            return this->_filename;
        }

        /**
         * Function for print usage
         */
        void printUsage();

    private:

        /**
         * Input filename
         */
        std::string _filename;

    private:

        /**
         * Number of command line arguments
         */
        int argc;

        /**
         * Array of command line arguments
         */
        char **argv;
    };

}


#endif //GSLANGUAGE_GS_ARGUMENTS_H
