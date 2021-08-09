#include <GS_Arguments.h>

namespace GSLanguageCompiler {

    GS_Arguments::GS_Arguments(GSInt argc, GSChar *argv[])
            : _argc(argc), _argv(argv) {}

    GS_ArgumentsOptions GS_Arguments::parseArguments() {
        GSString inputFilename;
        GSString outputFilename;
        GSBool isInterpret;
        GSBool isEnableTesting;
        GSBool isEnableProfiling;

        for (GSInt index = 1; index < this->_argc; ++index) {
            GSString argument = this->_argv[index];
            if (argument == "-f" || argument == "--file") {
                ++index;
                if (this->_argc < index) {
                    throw Exceptions::GS_Exception(("Invalid argument \"" + argument + "\"!").c_str());
                }

                inputFilename = _argv[index];

                continue;
            } else if (argument == "-o" || argument == "--out") {
                ++index;
                if (this->_argc < index) {
                    throw Exceptions::GS_Exception(("Invalid argument \"" + argument + "\"!").c_str());
                }

                outputFilename = _argv[index];

                continue;
            } else if (argument == "-i" || argument == "--interpret") {
                isInterpret = true;

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
                    throw Exceptions::GS_Exception("Invalid arguments!");
            }
        }

        return GS_ArgumentsOptions(inputFilename, outputFilename, isInterpret, isEnableTesting, isEnableProfiling);
    }

    GSVoid GS_Arguments::printUsage() {
        std::cout
        << "Usage: GSLanguage -f [input] (-o [output] [params...])\n"
        << "\t-f  --file      Main filename to compiling\n"
        << "\t-o  --out       Output filename for executing\n"
        << "\t-i  --interpret Interpreting code\n"
        << "\t-t  --test      Printing information because compiling\n"
        << "\t-p  --profiling Printing information about time of compiling\n"
        << "\t-h  --help      Information about flags and compiler\n"
        << std::endl;
    }

    GS_ArgumentsOptions::GS_ArgumentsOptions(GSString inputFilename,
                                             GSString outputFilename,
                                             GSBool isInterpret,
                                             GSBool isEnableTesting,
                                             GSBool isEnableProfiling,
                                             GSBool isInvalidArguments) {
        _inputFilename = std::move(inputFilename);

        if (outputFilename.empty()) {
            _outputGSVMFilename = _inputFilename + ".gsvm";
        } else {
            _outputGSVMFilename = std::move(outputFilename) + ".gsvm";
        }

        _isInterpret = isInterpret;

        _isEnableTesting = isEnableTesting;
        _isEnableProfiling = isEnableProfiling;

        _isInvalidArguments = isInvalidArguments;
    }

    GSString GS_ArgumentsOptions::getInputFilename() {
        return this->_inputFilename;
    }

    GSString GS_ArgumentsOptions::getOutputGSVMFilename() {
        return this->_outputGSVMFilename;
    }

    GSBool GS_ArgumentsOptions::getIsInterpret() {
        return _isInterpret;
    }

    GSBool GS_ArgumentsOptions::getIsEnableTesting() {
        return _isEnableTesting;
    }

    GSBool GS_ArgumentsOptions::getIsEnableProfiling() {
        return _isEnableProfiling;
    }

    GSBool GS_ArgumentsOptions::getIsInvalidArguments() {
        return _isInvalidArguments;
    }

    GSVoid GS_ArgumentsOptions::setIsInvalidArguments(GSBool isInvalidArguments) {
        _isInvalidArguments = isInvalidArguments;
    }

}