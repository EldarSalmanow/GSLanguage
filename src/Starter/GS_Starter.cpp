#include <Starter/GS_Starter.h>

namespace Starter {

    GSVoid GS_DebugFunctions::printReaderDebugInfo(GSString &string) {
        static GSInt line = 1;

        std::cerr << line << ": " << string << std::endl;

        ++line;
    }

    GSVoid GS_DebugFunctions::printLexerDebugInfo(GS_Token &token) {
        std::cerr << tokenTypeToString[token.getType()] << std::endl;
    }

    GSVoid GS_DebugFunctions::printParserDebugInfo(GSNodePtr &statement) {
        std::cerr << statement->toString() << std::endl;
    }

    GSVoid GS_DebugFunctions::printOptimizerDebugInfo(GSNodePtr &statement) {
        std::cerr << statement->toString() << std::endl;
    }

    void printException(Exceptions::GS_Exception &exception) {
        Platform::GS_CrossPlatform::setConsoleColor(Platform::GS_CrossPlatform::BLACK, Platform::GS_CrossPlatform::RED);

        std::cerr << exception.what() << std::endl;

        Platform::GS_CrossPlatform::setConsoleColor(Platform::GS_CrossPlatform::BLACK, Platform::GS_CrossPlatform::WHITE);
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

                _timer.addResult("Total time: \t\t\t\t\t" + std::to_string(totalTimer.result().count()) + " microseconds\n");

                _timer.printResults();
            } else {
                startCompiling();
            }

        } catch (Exceptions::GS_Exception &exception) {
            printException(exception);

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

        // optimizing parser AST
        startOptimizer();

        // generating code from AST
        generateCode();

        if (_compilerData.argumentsOptions.getIsEnableTesting()) {
            // start debug mode
            startDebugMode();
        }
    }

    GSVoid GS_Starter::startReader() {
        GSReaderPointer reader = std::make_shared<GS_Reader>(_compilerData.argumentsOptions.getInputFilename());

        if (_compilerData.argumentsOptions.getIsEnableProfiling()) {
            GS_Timer readerTimer;

            readerTimer.start();

            _compilerData.inputSource = reader->readFile();

            readerTimer.stop();

            _timer.addResult("Reading input time: \t\t\t\t" + std::to_string(readerTimer.result().count()) + " microseconds\n");
        } else {
            _compilerData.inputSource = reader->readFile();
        }
    }

    GSVoid GS_Starter::startLexer() {
        GSLexerPointer lexer = std::make_shared<GS_Lexer>(_compilerData.inputSource);

        if (_compilerData.argumentsOptions.getIsEnableProfiling()) {
            GS_Timer lexerTimer;

            lexerTimer.start();

            _compilerData.lexerTokens = lexer->tokenize();

            lexerTimer.stop();

            _timer.addResult("Lexer analyzing time: \t\t\t\t" + std::to_string(lexerTimer.result().count()) + " microseconds\n");
        } else {
            _compilerData.lexerTokens = lexer->tokenize();
        }
    }

    GSVoid GS_Starter::startParser() {
        GSParserPointer parser = std::make_shared<GS_Parser>(_compilerData.lexerTokens);

        if (_compilerData.argumentsOptions.getIsEnableProfiling()) {
            GS_Timer parserTimer;

            parserTimer.start();

            _compilerData.parserStatements = parser->parse();

            parserTimer.stop();

            _timer.addResult("Parsing tokens time: \t\t\t\t" + std::to_string(parserTimer.result().count()) + " microseconds\n");
        } else {
            _compilerData.parserStatements = parser->parse();
        }
    }

    GSVoid GS_Starter::startOptimizer() {
        GSOptimizerPointer optimizer = std::make_shared<GS_Optimizer>(_compilerData.parserStatements);

        if (_compilerData.argumentsOptions.getIsEnableProfiling()) {
            GS_Timer optimizerTimer;

            optimizerTimer.start();

            _compilerData.optimizedParserStatements = optimizer->optimize();

            optimizerTimer.stop();

            _timer.addResult("Optimizing parser statements time: \t\t" + std::to_string(optimizerTimer.result().count()) + " microseconds\n");
        } else {
            _compilerData.optimizedParserStatements = optimizer->optimize();
        }
    }

    GSVoid GS_Starter::generateCode() {
        GSCodeGeneratorPointer codeGenerator = std::make_shared<GS_CodeGenerator>(_compilerData.optimizedParserStatements);

        if (_compilerData.argumentsOptions.getIsEnableProfiling()) {
            GS_Timer codeGeneratorTimer;

            codeGeneratorTimer.start();

            _compilerData.codeGeneratorByteCode = codeGenerator->codegen();

            codeGeneratorTimer.stop();

            _timer.addResult("Code generation time: \t\t\t\t" + std::to_string(codeGeneratorTimer.result().count()) + " microseconds\n");
        } else {
            _compilerData.codeGeneratorByteCode = codeGenerator->codegen();
        }

        std::ofstream out(_compilerData.argumentsOptions.getOutputGSVMFilename(), std::ios::binary);

        if (out.is_open()) {
            for (auto &byte : _compilerData.codeGeneratorByteCode) {
                out << byte;
            }
        }

        out.close();
    }

    GSVoid GS_Starter::parseArguments(GSInt argc, GSChar *argv[]) {
        GSArgumentsPointer argumentsParser = std::make_shared<GS_Arguments>(argc, argv);

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

        GS_Debug::printDebugInformation("\n----------OPTIMIZATION OUT START----------\n", "\n----------OPTIMIZATION OUT END----------\n",
                                        &GS_DebugFunctions::printOptimizerDebugInfo, _compilerData.optimizedParserStatements);

        debugTimer.stop();

        _timer.addResult("Printing debug info time: \t\t\t" + std::to_string(debugTimer.result().count()) + " microseconds\n");
    }

}