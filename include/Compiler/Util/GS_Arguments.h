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
            return this->_arguments.filename;
        }

        /**
         * Getter for _arguments.isTestingMode
         * @return Is testing mode
         */
        bool getIsTestingMode() {
            return this->_arguments.isTestingMode;
        }

        /**
         * Getter for _arguments.isTestingModeAll
         * @return Is testing all mode
         */
        bool getIsTestingModeAll() {
            return this->_arguments.isTestingModeAll;
        }

        /**
         * Getter for _arguments.isTestingModeLexer
         * @return Is testing lexer mode
         */
        bool getIsTestingModeLexer() {
            return this->_arguments.isTestingLexer;
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
            std::string filename;

            /**
            * Is testing compiling mode (for developers GSLanguageCompiler)
            */
            bool isTestingMode    = false;

            /**
             * Is testing all mode (for developers GSLanguageCompiler)
             */
            bool isTestingModeAll = false;

            /**
             * Is the lexer tested (for developers GSLanguageCompiler)
             */
            bool isTestingLexer   = false;

        };

    private:

        /**
         * Arguments for compiler, before analyzing command line arguments
         */
        _Arguments _arguments;

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
