#include "../../include/Starter/GS_Starter.h"

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
        std::function<GSStatementPointerArray(GS_Parser&)> parserFunction = &GS_Parser::parse;
//        std::function<GSExpressionPointerArray(GS_Parser&)> parserFunction = &GS_Parser::parse;

        Debug::GS_Timer<GSText(GS_Reader&)> readerTimer(readerFunction);
        Debug::GS_Timer<GSTokenArray(GS_Lexer&)> lexerTimer(lexerFunction);
        Debug::GS_Timer<GSStatementPointerArray(GS_Parser&)> parserTimer(parserFunction);
//        Debug::GS_Timer<GSExpressionPointerArray(GS_Parser&)> parserTimer(parserFunction);

        // reading input file
        GSReaderPointer reader(new GS_Reader(arguments->getFilename()));
//        GSText input = readerTimer.runtime("Reading time", *reader);
        GSText input = reader->readFile();

        // lexer analyzing
        GSLexerPointer lexer(new GS_Lexer(input));
        GSTokenArray tokens = lexerTimer.runtime("Lexer analyzing time", *lexer);
//        GSTokenArray tokens = lexer->tokenize();

        // parsing tokens to statements and statements
        GSParserPointer parser(new GS_Parser(tokens));
        GSStatementPointerArray statements = parserTimer.runtime("Parsing tokens time", *parser);
//        GSExpressionPointerArray expressions = parserTimer.runtime("Parsing tokens time", *parser);
//        GSStatementPointerArray statements = parser->parse();

        // testing
        if (arguments->getIsTestingMode()) {
            Debug::GS_Debug::printInput(input);
            Debug::GS_Debug::printLexerOutput(tokens);
            Debug::GS_Debug::printParserOutput(statements);
//            Debug::GS_Debug::printParserOutput(expressions);
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

//        arguments->parseArguments();

        argumentsTimer.runtime("Parsing arguments time", *arguments);


        if (arguments->getFilename().empty()) {
            arguments->printUsage();
            return nullptr;
        }

        return arguments;
    }

}