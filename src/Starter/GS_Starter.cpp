#include "../../include/Starter/GS_Starter.h"

namespace Starter {

    int GS_Starter::start(int argc, char **argv) {
        try {
            parseArguments(argc, argv);

            if (_CompilerData::arguments == nullptr) {
                return 1;
            } else if (_CompilerData::arguments->getIsProfilingEnable()) {
                _Timers::totalTimer.runtime("Total time");

                Debug::GS_TimerResults::printTimerResults();
            } else {
                startCompiling();
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

    void GS_Starter::startCompiling() {

        // reading source from file
        startReader();

        // tokenizing source
        startLexer();

        // parsing tokens to AST
        startParser();

        if (_CompilerData::arguments->getIsTestingEnable()) {
            // start debug mode
            startDebugMode();
        }
    }

    void GS_Starter::startReader() {
        GSReaderPointer reader(new GS_Reader(_CompilerData::arguments->getFilename()));

        if (_CompilerData::arguments->getIsProfilingEnable()) {
            _CompilerData::inputSource = _Timers::readerTimer.runtime("Reading input time", *reader);
        } else {
            _CompilerData::inputSource = reader->readFile();
        }
    }

    void GS_Starter::startLexer() {
        GSLexerPointer lexer(new GS_Lexer(_CompilerData::inputSource));

        if (_CompilerData::arguments->getIsProfilingEnable()) {
            _CompilerData::tokens = _Timers::lexerTimer.runtime("Lexer analyzing time", *lexer);
        } else {
            _CompilerData::tokens = lexer->tokenize();
        }
    }

    void GS_Starter::startParser() {
        GSParserPointer parser(new GS_Parser(_CompilerData::tokens, _CompilerData::inputSource));

        if (_CompilerData::arguments->getIsProfilingEnable()) {
            _CompilerData::statements = _Timers::parserTimer.runtime("Parsing tokens time", *parser);
        } else {
            _CompilerData::statements = parser->parse();
        }
    }

    void GS_Starter::parseArguments(int argc, char *argv[]) {
        _CompilerData::arguments = GSArgumentsPointer(new GS_Arguments(argc, argv));

        _CompilerData::arguments->parseArguments();

        if (argc < 3 || _CompilerData::arguments->getFilename().empty()) {
            _CompilerData::arguments->printUsage();

            // setting arguments to null
            _CompilerData::arguments = nullptr;
        }
    }

    void GS_Starter::startDebugMode() {
        Debug::GS_Debug::printInput(_CompilerData::inputSource);
        Debug::GS_Debug::printLexerOutput(_CompilerData::tokens);
        Debug::GS_Debug::printParserOutput(_CompilerData::statements);
        Debug::GS_Debug::printTableOfSymbols();
    }

}