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

    GSVoid GS_Starter::runWithTimer(std::function<GSVoid()> &function, GSString messageForProfiling) {
        GS_Timer timer;

        timer.start();

        function();

        timer.stop();

        _timer.addResult(messageForProfiling + std::to_string(timer.result().count()) + " microseconds\n");
    }

    GSVoid GS_Starter::startReader() {
        auto reader = std::make_shared<GS_Reader>(_compilerData.argumentsOptions.getInputFilename());

        std::function<GSVoid()> function = [reader] () -> GSVoid {
            _compilerData.inputSource = reader->readFile();
        };

        if (_compilerData.argumentsOptions.getIsEnableProfiling()) {
            runWithTimer(function, "Reading input time: \t\t\t\t");
        } else {
            function();
        }
    }

    GSVoid GS_Starter::startLexer() {
        auto lexer = std::make_shared<GS_Lexer>(_compilerData.inputSource);

        std::function<GSVoid()> function = [lexer] () -> GSVoid {
            _compilerData.lexerTokens = lexer->tokenize();
        };

        if (_compilerData.argumentsOptions.getIsEnableProfiling()) {
            runWithTimer(function, "Lexer analyzing time: \t\t\t\t");
        } else {
            function();
        }
    }

    GSVoid GS_Starter::startParser() {
        auto parser = std::make_shared<GS_Parser>(_compilerData.lexerTokens);

        std::function<GSVoid()> function = [parser] () -> GSVoid {
            _compilerData.parserStatements = parser->parse();
        };

        if (_compilerData.argumentsOptions.getIsEnableProfiling()) {
            runWithTimer(function, "Parsing tokens time: \t\t\t\t");
        } else {
            function();
        }
    }

    GSVoid GS_Starter::startOptimizer() {
        auto optimizer = std::make_shared<GS_Optimizer>(_compilerData.parserStatements);

        std::function<GSVoid()> function = [optimizer] () -> GSVoid {
            _compilerData.optimizedParserStatements = optimizer->optimize();
        };

        if (_compilerData.argumentsOptions.getIsEnableProfiling()) {
            runWithTimer(function, "Optimizing parser statements time: \t\t");
        } else {
            function();
        }
    }

    GSVoid GS_Starter::generateCode() {
        auto codeGenerator = std::make_shared<GS_CodeGenerator>(_compilerData.optimizedParserStatements);

        std::function<GSVoid()> function = [codeGenerator] () -> GSVoid {
            _compilerData.codeGeneratorVMImage = codeGenerator->codegen();
        };

        if (_compilerData.argumentsOptions.getIsEnableProfiling()) {
            runWithTimer(function, "Code generation time: \t\t\t\t");
        } else {
            function();
        }

        std::ofstream out(_compilerData.argumentsOptions.getOutputGSVMFilename(), std::ios::binary);

        if (out.is_open()) {
            for (auto &byte : _compilerData.codeGeneratorVMImage.getByteCode()) {
                out << byte;
            }
        }

        out.close();
    }

    GSVoid GS_Starter::parseArguments(GSInt argc, GSChar *argv[]) {
        auto argumentsParser = std::make_shared<GS_Arguments>(argc, argv);

        _compilerData.argumentsOptions = argumentsParser->parseArguments();

        if (argc < 3 || _compilerData.argumentsOptions.getInputFilename().empty()) {
            argumentsParser->printUsage();

            _compilerData.argumentsOptions.setIsInvalidArguments(true);
        }
    }

    GSVoid GS_Starter::startDebugMode() {
        std::function<GSVoid()> function = [] () -> GSVoid {
            GS_Debug::printDebugInformation("\n----------READER OUT START----------\n", "\n----------READER OUT END----------\n",
                                            &GS_DebugFunctions::printReaderDebugInfo, _compilerData.inputSource);

            GS_Debug::printDebugInformation("\n----------LEXER OUT START----------\n", "\n----------LEXER OUT END----------\n",
                                            &GS_DebugFunctions::printLexerDebugInfo, _compilerData.lexerTokens);

            GS_Debug::printDebugInformation("\n----------PARSER OUT START----------\n", "\n----------PARSER OUT END----------\n",
                                            &GS_DebugFunctions::printParserDebugInfo, _compilerData.parserStatements);

            GS_Debug::printDebugInformation("\n----------OPTIMIZATION OUT START----------\n", "\n----------OPTIMIZATION OUT END----------\n",
                                            &GS_DebugFunctions::printOptimizerDebugInfo, _compilerData.optimizedParserStatements);
        };

        runWithTimer(function, "Printing debug info time: \t\t\t");
    }

}