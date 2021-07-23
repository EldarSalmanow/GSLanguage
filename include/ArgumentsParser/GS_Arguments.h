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
        GS_ArgumentsOptions(const GSString &inputFilename,
                            const GSString &outputFilename = "",
                            const GSBool isForVM = false,
                            const GSBool isEnableTesting = false,
                            const GSBool isEnableProfiling = false,
                            const GSBool isInvalidArguments = false);

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
        GSString getOutputAsmFilename();

        /**
         *
         * @return
         */
        GSString getOutputObjFilename();

        /**
         *
         * @return
         */
        GSString getOutputExeFilename();

        /**
         *
         * @return
         */
        GSString getOutputGSVMFilename();

        /**
         *
         * @return
         */
        GSBool getIsForVM();

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
        GSString _outputAsmFilename;

        /**
         *
         */
        GSString _outputObjFilename;

        /**
         *
         */
        GSString _outputExeFilename;

        /**
         *
         */
        GSString _outputGSVMFilename;

        /**
         *
         */
        GSBool _isForVM;

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
