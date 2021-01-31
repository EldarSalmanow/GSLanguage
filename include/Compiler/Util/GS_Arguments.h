#ifndef GSLANGUAGE_GS_ARGUMENTS_H
#define GSLANGUAGE_GS_ARGUMENTS_H


#include <string>
#include <memory>

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
         * Getter for filename
         * @return Input filename
         */
        std::string &getFilename() {
            return this->filename;
        }

        /**
         * Getter for isTestingMode
         * @return Is testing mode
         */
        bool getIsTestingMode() {
            return this->isTestingMode;
        }

        /**
         * Function for print usage
         */
        void printUsage();

    private:

        /**
         * Input filename
         */
        std::string filename;

        /**
         * Is testing compiling mode (for developers GSLanguageCompiler)
         */
        bool isTestingMode = false;

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

    typedef std::shared_ptr<GS_Arguments> GSArgumentsPointer;

}


#endif //GSLANGUAGE_GS_ARGUMENTS_H
