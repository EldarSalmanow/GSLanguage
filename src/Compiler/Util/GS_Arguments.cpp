#include <GS_Arguments.h>

namespace GSLanguageCompiler {

    GS_Arguments::GS_Arguments(GSInt argc, GSChar *argv[]) {
        this->_argc = argc;
        this->_argv = argv;
    }

    GS_ArgumentsOptions GS_Arguments::parseArguments() {
        GSString inputFilename;
        GSString outputFilename;
        GSBool isEnableTesting;
        GSBool isEnableProfiling;

        for (GSInt index = 1; index < this->_argc; ++index) {
            GSString argument = this->_argv[index];
            if (argument == "-f" || argument == "--file") {
                ++index;
                if (this->_argc < index) {
                    throw Exceptions::GS_ArgumentException("Invalid argument \"" + argument + "\"!");
                }

                inputFilename = _argv[index];

                continue;
            } else if (argument == "-o" || argument == "--out") {
                ++index;
                if (this->_argc < index) {
                    throw Exceptions::GS_ArgumentException("Invalid argument \"" + argument + "\"!");
                }

                outputFilename = _argv[index];

                continue;
            } else if (argument == "-h" || argument == "--help") {
                this->printUsage();

                break;
            } else if (argument == "-t" || argument == "--test") {
                isEnableTesting = true;

                continue;
            } else if (argument == "-p" || argument == "--profiling") {
                isEnableProfiling = true;

                continue;
            } else {
                    throw Exceptions::GS_ArgumentException("Invalid arguments!");
            }
        }

        return GS_ArgumentsOptions(inputFilename, outputFilename, isEnableTesting, isEnableProfiling);
    }

    GSVoid GS_Arguments::printUsage() {
        std::cout
        << "Usage: GSLanguage -f [input] (-o [output] [params...])\n"
        << "\t-f --file      Main filename to compiling\n"
        << "\t-o --out       Output filename for executing\n"
        << "\t-t --test      Printing information because compiling\n"
        << "\t-p --profiling Printing information about time of compiling\n"
        << "\t-h --help      Information about flags and compiler\n"
        << std::endl;
    }

    GS_ArgumentsOptions::GS_ArgumentsOptions(const GSString &inputFilename,
                                             const GSString &outputFilename,
                                             const GSBool isEnableTesting,
                                             const GSBool isEnableProfiling,
                                             const GSBool isInvalidArguments) {
        this->_inputFilename = inputFilename;

        if (outputFilename.empty()) {
            this->_outputAsmFilename = this->_inputFilename + ".asm";
            this->_outputObjFilename = this->_inputFilename + ".obj";
            this->_outputExeFilename = this->_inputFilename + ".exe";
        } else {
            this->_outputAsmFilename = outputFilename + ".asm";
            this->_outputObjFilename = outputFilename + ".obj";
            this->_outputExeFilename = outputFilename + ".exe";
        }

        this->_isEnableTesting = isEnableTesting;
        this->_isEnableProfiling = isEnableProfiling;

        this->_isInvalidArguments = isInvalidArguments;
    }

    GSString GS_ArgumentsOptions::getInputFilename() {
        return this->_inputFilename;
    }

    GSString GS_ArgumentsOptions::getOutputAsmFilename() {
        return this->_outputAsmFilename;
    }

    GSString GS_ArgumentsOptions::getOutputObjFilename() {
        return this->_outputObjFilename;
    }

    GSString GS_ArgumentsOptions::getOutputExeFilename() {
        return this->_outputExeFilename;
    }

    GSBool GS_ArgumentsOptions::getIsEnableTesting() {
        return this->_isEnableTesting;
    }

    GSBool GS_ArgumentsOptions::getIsEnableProfiling() {
        return this->_isEnableProfiling;
    }

    GSBool GS_ArgumentsOptions::getIsInvalidArguments() {
        return this->_isInvalidArguments;
    }

    GSVoid GS_ArgumentsOptions::setIsInvalidArguments(GSBool isInvalidArguments) {
        this->_isInvalidArguments = isInvalidArguments;
    }

}