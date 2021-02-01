#include "../../include/Starter/GS_Starter.h"
#include "../../test/Tests.h"

namespace Starter {

    int GS_Starter::startCompiler(int argc, char **argv) {
        try {
            GSArgumentsPointer arguments = parseArguments(argc, argv);

            if (arguments == nullptr) {
                return 1;
            }

            startCompiling(arguments);

        } catch (Exceptions::_GS_Exception &exception) {
            std::cerr << exception._getErrorMessage() << std::endl;

            return 1;
        } catch (std::exception &exception) {
            std::cerr << exception.what() << std::endl;

            return 1;
        }
        return 0;
    }

    void GS_Starter::startCompiling(GSArgumentsPointer &arguments) {

        // reading input file
        GSReaderPointer reader(new GS_Reader(arguments->getFilename()));
        GSText input = reader->readFile();

        // lexer analyzing
        GSLexerPointer lexer(new GS_Lexer(input));
        GSTokenArray tokens = lexer->tokenize();

        // lexer testing
        if (arguments->getIsTestingMode()) {
            Testing::printTokenTypes(tokens);
        }
    }

    GSArgumentsPointer GS_Starter::parseArguments(int argc, char *argv[]) {
        GSArgumentsPointer arguments(new GS_Arguments(argc, argv));

        if (argc < 3) {
            arguments->printUsage();
            return nullptr;
        }

        arguments->parseArguments();

        if (arguments->getFilename().empty()) {
            arguments->printUsage();
            return nullptr;
        }

        return arguments;
    }

}