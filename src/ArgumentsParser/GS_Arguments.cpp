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

        for (GSInt index = 1; index < _argc; ++index) {
            GSString argument = _argv[index];

            if (argument == "-f" || argument == "--file") {
                ++index;

                if (_argc <= index) {
                    Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                                   "Invalid param for input filename argument (-f or --file)!");

                    Exceptions::errorHandler.print(Exceptions::ErrorLevel::NOTE_LVL,
                                                   "Specify param for input filename argument.");

                    Exceptions::errorHandler.throw_();
                }

                inputFilename = _argv[index];

                continue;
            } else if (argument == "-o" || argument == "--out") {
                ++index;

                if (_argc <= index) {
                    Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                                   "Invalid param for output filename argument (-o or --out)!");

                    Exceptions::errorHandler.print(Exceptions::ErrorLevel::NOTE_LVL,
                                                   "Specify param for output filename argument.");

                    Exceptions::errorHandler.throw_();
                }

                outputFilename = _argv[index];

                continue;
            } else if (argument == "-i" || argument == "--interpret") {
                isInterpret = true;

                continue;
            } else if (argument == "-h" || argument == "--help") {
                printUsage();

                break;
            } else if (argument == "-t" || argument == "--test") {
                isEnableTesting = true;

                continue;
            } else if (argument == "-p" || argument == "--profiling") {
                isEnableProfiling = true;

                continue;
            } else {
                Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                               "Unknown argument \"" + argument + "\"!");

                Exceptions::errorHandler.print(Exceptions::ErrorLevel::NOTE_LVL,
                                               "Please, read help information about GSLanguageCompiler and arguments (-h or --help).");

                Exceptions::errorHandler.throw_();
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
        return _inputFilename;
    }

    GSString GS_ArgumentsOptions::getOutputGSVMFilename() {
        return _outputGSVMFilename;
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