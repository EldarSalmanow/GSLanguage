#include <GS_Arguments.h>

namespace GSLanguageCompiler {

    GS_Arguments::GS_Arguments(GSInt argc, GSChar *argv[])
            : _argc(argc), _argv(argv) {}

    GS_ArgumentsOptions GS_Arguments::parseArguments() {
        GSString inputFilename;
        GSString outputFilename;
        GSBool isForVM;
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
            } else if (argument == "-vm" || argument == "--VM") {
                isForVM = true;

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

        return GS_ArgumentsOptions(inputFilename, outputFilename, isForVM, isEnableTesting, isEnableProfiling);
    }

    GSVoid GS_Arguments::printUsage() {
        std::cout
        << "Usage: GSLanguage -f [input] (-o [output] [params...])\n"
        << "\t-f  --file      Main filename to compiling\n"
        << "\t-o  --out       Output filename for executing\n"
        << "\t-vm --VM        Generating code for GSVirtualMachine\n"
        << "\t-t  --test      Printing information because compiling\n"
        << "\t-p  --profiling Printing information about time of compiling\n"
        << "\t-h  --help      Information about flags and compiler\n"
        << std::endl;
    }

    GS_ArgumentsOptions::GS_ArgumentsOptions(const GSString &inputFilename,
                                             const GSString &outputFilename,
                                             const GSBool isForVM,
                                             const GSBool isEnableTesting,
                                             const GSBool isEnableProfiling,
                                             const GSBool isInvalidArguments) {
        this->_inputFilename = inputFilename;

        if (outputFilename.empty()) {
            this->_outputAsmFilename = this->_inputFilename + ".asm";
            this->_outputObjFilename = this->_inputFilename + ".obj";
            this->_outputExeFilename = this->_inputFilename + ".exe";
            this->_outputGSVMFilename = this->_inputFilename + ".gsvm";
        } else {
            this->_outputAsmFilename = outputFilename + ".asm";
            this->_outputObjFilename = outputFilename + ".obj";
            this->_outputExeFilename = outputFilename + ".exe";
            this->_outputGSVMFilename = outputFilename + ".gsvm";
        }

        this->_isForVM = isForVM;

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

    GSString GS_ArgumentsOptions::getOutputGSVMFilename() {
        return this->_outputGSVMFilename;
    }

    GSBool GS_ArgumentsOptions::getIsForVM() {
        return this->_isForVM;
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