#include "../../include/Starter/GS_Starter.h"

namespace Starter {

    int GS_Starter::start(int argc, char **argv) {
        try {
            GSArgumentsPointer arguments = parseArguments(argc, argv);

            if (arguments == nullptr) {
                return 1;
            } else if (arguments->getIsProfilingEnable()) {
                std::function<void(GSArgumentsPointer&)> startFunction = startCompiling;

                Debug::GS_Timer<void(GSArgumentsPointer&)> totalTimer(startFunction);

                totalTimer.runtime("Total time", arguments);

                Debug::GS_TimerResults::printTimerResults();
            } else {
                startCompiling(arguments);
            }

        } catch (Exceptions::_GS_Exception &exception) {
            exception._printErrorMessage();

            return 1;
        } catch (std::exception &exception) {
            std::cerr << "System error!\n" << exception.what() << std::endl;

            return 1;
        }
        return 0;
    }

    void GS_Starter::startCompiling(GSArgumentsPointer &arguments) {
        if (arguments->getIsProfilingEnable()) {
            std::function<GSText(GS_Reader&)> readerFunction = &GS_Reader::readFile;
            std::function<GSTokenArray(GS_Lexer&)> lexerFunction = &GS_Lexer::tokenize;
            std::function<GSStatementPointerArray(GS_Parser&)> parserFunction = &GS_Parser::parse;

            Debug::GS_Timer<GSText(GS_Reader&)> readerTimer(readerFunction);
            Debug::GS_Timer<GSTokenArray(GS_Lexer&)> lexerTimer(lexerFunction);
            Debug::GS_Timer<GSStatementPointerArray(GS_Parser&)> parserTimer(parserFunction);

            // reading input file
            GSReaderPointer reader(new GS_Reader(arguments->getFilename()));
            GSText input = readerTimer.runtime("Reading input time", *reader);

            // lexer analyzing
            GSLexerPointer lexer(new GS_Lexer(input));
            GSTokenArray tokens = lexerTimer.runtime("Lexer analyzing time", *lexer);

            // parsing tokens to statements and statements
            GSParserPointer parser(new GS_Parser(tokens, input));
            GSStatementPointerArray statements = parserTimer.runtime("Parsing tokens time", *parser);

            // testing
            if (arguments->getIsTestingEnable()) {
                Debug::GS_Debug::printInput(input);
                Debug::GS_Debug::printLexerOutput(tokens);
                Debug::GS_Debug::printParserOutput(statements);
            }
        } else {
            // reading input file
            GSReaderPointer reader(new GS_Reader(arguments->getFilename()));
            GSText input = reader->readFile();

            // lexer analyzing
            GSLexerPointer lexer(new GS_Lexer(input));
            GSTokenArray tokens = lexer->tokenize();

            // parsing tokens to statements and statements
            GSParserPointer parser(new GS_Parser(tokens, input));
            GSStatementPointerArray statements = parser->parse();

            // testing
            if (arguments->getIsTestingEnable()) {
                Debug::GS_Debug::printInput(input);
                Debug::GS_Debug::printLexerOutput(tokens);
                Debug::GS_Debug::printParserOutput(statements);
            }
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