#ifndef GSLANGUAGE_GS_ARGUMENTS_H
#define GSLANGUAGE_GS_ARGUMENTS_H

#include <memory>
#include <vector>

#include <CrossPlatform/GS_PlatformTypes.h>

#include <Exceptions/GS_Exception.h>

namespace GSLanguageCompiler {

    /**
     *
     */
    class GS_ArgumentsOptions {
    public:

        /**
         *
         */
        GS_ArgumentsOptions() = default;

        /**
         *
         * @param inputFilename
         * @param outputFilename
         * @param isForVM
         * @param isEnableTesting
         * @param isEnableProfiling
         */
        explicit GS_ArgumentsOptions(GSString inputFilename,
                                     GSString outputFilename = "",
                                     GSBool isForVM = false,
                                     GSBool isEnableTesting = false,
                                     GSBool isEnableProfiling = false,
                                     GSBool isInvalidArguments = false);

    public:

        /**
         *
         * @return
         */
        GSString getInputFilename();

        /**
         *
         * @return
         */
        GSString getOutputGSVMFilename();

        /**
         *
         * @return
         */
        GSBool getIsInterpret();

        /**
         *
         * @return
         */
        GSBool getIsEnableTesting();

        /**
         *
         * @return
         */
        GSBool getIsEnableProfiling();

        /**
         *
         * @return
         */
        GSBool getIsInvalidArguments();

    public:

        /**
         *
         * @param isInvalidArguments
         * @return
         */
        GSVoid setIsInvalidArguments(GSBool isInvalidArguments);

    private:

        /**
         *
         */
        GSString _inputFilename;

        /**
         *
         */
        GSString _outputGSVMFilename;

        /**
         *
         */
        GSBool _isInterpret;

        /**
         *
         */
        GSBool _isEnableTesting;

        /**
         *
         */
        GSBool _isEnableProfiling;

        /**
         *
         */
        GSBool _isInvalidArguments;
    };

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
        GS_Arguments(GSInt argc, GSChar *argv[]);

    public:

        /**
         * Function for parsing arguments and generate config of project
         */
         GS_ArgumentsOptions parseArguments();

        /**
        * Function for print usage
        */
        GSVoid printUsage();

    private:

        /**
         * Number of command line arguments
         */
        GSInt _argc;

        /**
         * Array of command line arguments
         */
        GSChar **_argv;
    };

}

#endif //GSLANGUAGE_GS_ARGUMENTS_H
