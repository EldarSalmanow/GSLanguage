#ifndef GSLANGUAGE_GS_ARGUMENTS_H
#define GSLANGUAGE_GS_ARGUMENTS_H


#include <string>
#include <memory>
#include <vector>

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
            this->_argc = argc;
            this->_argv = argv;
        }

    public:

        /**
         * Function for parsing arguments and generate config of project
         */
        void parseArguments();

    public:

        /**
         * Getter for _arguments.filename
         * @return Input _filename
         */
        std::string &getFilename() {
            return _Arguments::filename;
        }

        /**
         * Getter for _arguments.isTestingEnable
         * @return Is testing mode
         */
        bool getIsTestingEnable() {
            return _Arguments::isTestingEnable;
        }

        /**
         * Getter for _arguments.isProfilingEnable
         * @return Is timers enable
         */
        bool getIsProfilingEnable() {
            return _Arguments::isProfilingEnable;
        }

        /**
         * Function for print usage
         */
        void printUsage();

    private:

        /**
         * Class for highlighting command line arguments
         */
        class _Arguments {
        public:

            /**
            * Input filename
            */
            inline static std::string filename;

            /**
            * Is testing compiling mode (for developers GSLanguageCompiler)
            */
            inline static bool isTestingEnable = false;

            /**
             * Is timers enable (compiling profiling)
             */
            inline static bool isProfilingEnable = false;
        };

    private:

        /**
         * Number of command line arguments
         */
        int _argc;

        /**
         * Array of command line arguments
         */
        char **_argv;
    };

    typedef std::shared_ptr<GS_Arguments> GSArgumentsPointer;

}


#endif //GSLANGUAGE_GS_ARGUMENTS_H
