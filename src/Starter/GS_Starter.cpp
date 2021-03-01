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
            std::cerr << "System error!\n" << exception.what() << std::endl;

            return 1;
        }
        return 0;
    }

    void GS_Starter::startCompiling(GSArgumentsPointer &arguments) {
        std::function<GSText(GS_Reader&)> readerFunction = &GS_Reader::readFile;
        std::function<GSTokenArray(GS_Lexer&)> lexerFunction = &GS_Lexer::tokenize;

        Debug::GS_Timer<GSText(GS_Reader&)> readerTimer(readerFunction);
        Debug::GS_Timer<GSTokenArray(GS_Lexer&)> lexerTimer(lexerFunction);

        // reading input file
        GSReaderPointer reader(new GS_Reader(arguments->getFilename()));
        GSText input = readerTimer.runtime("Reading time", *reader);

        // lexer analyzing
        GSLexerPointer lexer(new GS_Lexer(input));
        GSTokenArray tokens = lexerTimer.runtime("Lexer analyzing time", *lexer);

        // lexer testing
        if (arguments->getIsTestingMode()) {
            Testing::printTokenTypes(tokens);
        }
    }

    GSArgumentsPointer GS_Starter::parseArguments(int argc, char *argv[]) {
        std::function<void(GS_Arguments&)> argumentsFunction = &GS_Arguments::parseArguments;

        Debug::GS_Timer<void(GS_Arguments&)> argumentsTimer(argumentsFunction);

        GSArgumentsPointer arguments(new GS_Arguments(argc, argv));

        if (argc < 3) {
            arguments->printUsage();
            return nullptr;
        }

        argumentsTimer.runtime("Parsing arguments time", *arguments);


        if (arguments->getFilename().empty()) {
            arguments->printUsage();
            return nullptr;
        }

        return arguments;
    }

}