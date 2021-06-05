#include <Starter/GS_Starter.h>

namespace Starter {

    // TODO update and move this function to class
    GSString execute(const GSChar* cmd) {
        GSInt tempBufferSize = 128;
        GSChar tempBuffer[tempBufferSize];

        GSString result;

        FILE* pipe = popen(cmd, "r");

        if (!pipe) {
            throw std::runtime_error("popen() failed! \nLocation: src/GS_Starter.cpp exec(const char*)");
        }

        try {
            while (!feof(pipe)) {
                if (fgets(tempBuffer, tempBufferSize, pipe) != nullptr) {
                    result += tempBuffer;
                }
            }
        } catch (std::exception &exception) {
            pclose(pipe);

            throw exception;
        }

        pclose(pipe);

        return result;
    }

    GSVoid GS_DebugFunctions::printReaderDebugInfo(GSString &string) {
        static GSInt line = 1;

        std::cerr << line << ": " << string << std::endl;

        ++line;
    }

    GSVoid GS_DebugFunctions::printLexerDebugInfo(GS_Token &token) {
        std::cerr << GS_Debug::tokenTypeToString(token.getType()) << std::endl;
    }

    GSVoid GS_DebugFunctions::printParserDebugInfo(GSStatementPointer &statement) {
        std::cerr << statement->toStringForDebug() << std::endl;
    }

    GSInt GS_Starter::start(GSInt argc, GSChar **argv) {
        try {
            parseArguments(argc, argv);

            if (_compilerData.argumentsOptions.getIsInvalidArguments()) {
                return 1;
            } else if (_compilerData.argumentsOptions.getIsEnableProfiling()) {
                GS_Timer totalTimer;

                totalTimer.start();

                startCompiling();

                totalTimer.stop();

                _timer.addResult("Total time: \t\t\t" + std::to_string(totalTimer.result().count()) + " microseconds\n");

                _timer.printResults();
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

    GSVoid GS_Starter::startCompiling() {
        // reading source from file
        startReader();

        // tokenizing source
        startLexer();

        // parsing tokens to AST
        startParser();

        // generating code from AST
        generateCode();

        if (_compilerData.argumentsOptions.getIsEnableTesting()) {
            // start debug mode
            startDebugMode();
        }
    }

    GSVoid GS_Starter::startReader() {
        GSReaderPointer reader(new GS_Reader(_compilerData.argumentsOptions.getInputFilename()));

        if (_compilerData.argumentsOptions.getIsEnableProfiling()) {
            GS_Timer readerTimer;

            readerTimer.start();

            _compilerData.inputSource = reader->readFile();

            readerTimer.stop();

            _timer.addResult("Reading input time: \t\t" + std::to_string(readerTimer.result().count()) + " microseconds\n");
        } else {
            _compilerData.inputSource = reader->readFile();
        }
    }

    GSVoid GS_Starter::startLexer() {
        GSLexerPointer lexer(new GS_Lexer(_compilerData.inputSource));

        if (_compilerData.argumentsOptions.getIsEnableProfiling()) {
            GS_Timer lexerTimer;

            lexerTimer.start();

            _compilerData.lexerTokens = lexer->tokenize();

            lexerTimer.stop();

            _timer.addResult("Lexer analyzing time: \t\t" + std::to_string(lexerTimer.result().count()) + " microseconds\n");
        } else {
            _compilerData.lexerTokens = lexer->tokenize();
        }
    }

    GSVoid GS_Starter::startParser() {
        GSParserPointer parser(new GS_Parser(_compilerData.lexerTokens));

        if (_compilerData.argumentsOptions.getIsEnableProfiling()) {
            GS_Timer parserTimer;

            parserTimer.start();

            _compilerData.parserStatements = parser->parse();

            parserTimer.stop();

            _timer.addResult("Parsing tokens time: \t\t" + std::to_string(parserTimer.result().count()) + " microseconds\n");
        } else {
            _compilerData.parserStatements = parser->parse();
        }
    }

    GSVoid GS_Starter::generateCode() {
        GSCodeGeneratorPointer codeGenerator = GSCodeGeneratorPointer(new GS_CodeGenerator(_compilerData.parserStatements));

        if (_compilerData.argumentsOptions.getIsEnableProfiling()) {
            GS_Timer codeGeneratorTimer;

            codeGeneratorTimer.start();

            _compilerData.codeGeneratorCode = codeGenerator->generateCode();

            codeGeneratorTimer.stop();

            _timer.addResult("Code generation time: \t\t" + std::to_string(codeGeneratorTimer.result().count()) + " microseconds\n");
        } else {
            _compilerData.codeGeneratorCode = codeGenerator->generateCode();
        }

        std::ofstream out;

        out.open(_compilerData.argumentsOptions.getOutputAsmFilename(), std::ios::out);

        if (out.is_open()) {
            out << _compilerData.codeGeneratorCode;
        }

        out.close();

        execute(("nasm -f win32 " + _compilerData.argumentsOptions.getOutputAsmFilename()).c_str());
        execute(("golink /console /entry _Fmain4 "
                 + _compilerData.argumentsOptions.getOutputObjFilename()
                 + " kernel32.dll").c_str());
        // TODO add OOP writing generated code to file
    }

    GSVoid GS_Starter::parseArguments(GSInt argc, GSChar *argv[]) {
        GSArgumentsPointer argumentsParser = GSArgumentsPointer(new GS_Arguments(argc, argv));

        _compilerData.argumentsOptions = argumentsParser->parseArguments();

        if (argc < 3 || _compilerData.argumentsOptions.getInputFilename().empty()) {
            argumentsParser->printUsage();

            _compilerData.argumentsOptions.setIsInvalidArguments(true);
        }
    }

    GSVoid GS_Starter::startDebugMode() {
        GS_Timer debugTimer;

        debugTimer.start();

        GS_Debug::printDebugInformation("\n----------READER OUT START----------\n", "\n----------READER OUT END----------\n",
                                        &GS_DebugFunctions::printReaderDebugInfo, _compilerData.inputSource);

        GS_Debug::printDebugInformation("\n----------LEXER OUT START----------\n", "\n----------LEXER OUT END----------\n",
                                        &GS_DebugFunctions::printLexerDebugInfo, _compilerData.lexerTokens);

        GS_Debug::printDebugInformation("\n----------PARSER OUT START----------\n", "\n----------PARSER OUT END----------\n",
                                        &GS_DebugFunctions::printParserDebugInfo, _compilerData.parserStatements);

        debugTimer.stop();

        _timer.addResult("Printing debug info time: \t" + std::to_string(debugTimer.result().count()) + " microseconds\n");
    }

}