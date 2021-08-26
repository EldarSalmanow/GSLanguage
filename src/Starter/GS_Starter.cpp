#include <Starter/GS_Starter.h>

namespace Starter {

    GSVoid GS_DebugFunctions::printReaderDebugInfo(GSString &string) {
        static GSInt line = 1;

        std::cout << line << ": " << string << std::endl;

        ++line;
    }

    GSVoid GS_DebugFunctions::printLexerDebugInfo(GS_Token &token) {
        std::cout << tokenTypeToString[token.getType()] << std::endl;
    }

    GSInt GS_Starter::start(GSInt argc, GSChar **argv) {
        try {
            parseArguments(argc, argv);

            RunningFunction function = startCompiling;

            if (_compilerData.argumentsOptions.getIsInvalidArguments()) {
                return 1;
            } else if (_compilerData.argumentsOptions.getIsEnableProfiling()) {
                runWithTimer(function, "Total time: \t\t\t\t\t");

                _timer.printResults();
            } else {
                function();
            }

        } catch (Exceptions::GS_Exception &exception) {
            return 1;
        } catch (std::exception &exception) {
            Exceptions::errorHandler.print(GSLanguageCompiler::Exceptions::ErrorLevel::FATAL_LVL,
                                                 exception.what());

            Exceptions::errorHandler.print(Exceptions::ErrorLevel::NOTE_LVL,
                                           "Please, report this fatal error to GSLanguageCompiler repository.");

            Exceptions::errorHandler.throw_();

            return 1;
        } catch (...) {
            Exceptions::errorHandler.print(GSLanguageCompiler::Exceptions::ErrorLevel::FATAL_LVL,
                                           "Unknown fatal error!");

            Exceptions::errorHandler.print(Exceptions::ErrorLevel::NOTE_LVL,
                                           "Please, report this fatal error to GSLanguageCompiler repository.");

            Exceptions::errorHandler.throw_();
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

        if (_compilerData.argumentsOptions.getIsInterpret()) {
            // start interpreter
            startInterpreter();
        } else {
            // generating code from AST
            generateCode();
        }

        if (_compilerData.argumentsOptions.getIsEnableTesting()) {
            // start debug mode
            startDebugMode();
        }
    }

    GSVoid GS_Starter::runWithTimer(RunningFunction &function, GSString messageForProfiling) {
        GS_Timer timer;

        timer.start();

        function();

        timer.stop();

        _timer.addResult(std::move(messageForProfiling) + std::to_string(timer.result().count()) + " microseconds\n");
    }

    GSVoid GS_Starter::startReader() {
        auto reader = std::make_shared<GS_Reader>(_compilerData.argumentsOptions.getInputFilename());

        RunningFunction function = [reader] () -> GSVoid {
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

        RunningFunction function = [lexer] () -> GSVoid {
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

        RunningFunction function = [parser] () -> GSVoid {
            _compilerData.parserStatements = parser->parse();
        };

        if (_compilerData.argumentsOptions.getIsEnableProfiling()) {
            runWithTimer(function, "Parsing tokens time: \t\t\t\t");
        } else {
            function();
        }
    }

    GSVoid GS_Starter::startOptimizer() {
        GSOptimizerPassPtrArray passes = {
                std::make_shared<GS_ConstantFoldingPass>()
        };

        auto optimizer = std::make_shared<GS_Optimizer>(_compilerData.parserStatements, passes);

        RunningFunction function = [optimizer] () -> GSVoid {
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

        RunningFunction function = [codeGenerator] () -> GSVoid {
            _compilerData.codeGeneratorByteCode = codeGenerator->codegen();
        };

        if (_compilerData.argumentsOptions.getIsEnableProfiling()) {
            runWithTimer(function, "Code generation time: \t\t\t\t");
        } else {
            function();
        }

        GSBCCodeGen::GS_BCWriter writer(_compilerData.argumentsOptions.getOutputGSVMFilename());

        writer.write(_compilerData.codeGeneratorByteCode);
    }

    GSVoid GS_Starter::startInterpreter() {
        auto interpreter = std::make_shared<GS_Interpreter>(_compilerData.optimizedParserStatements);

        RunningFunction function = [interpreter] () -> GSVoid {
            interpreter->startInterpret();
        };

        if (_compilerData.argumentsOptions.getIsEnableProfiling()) {
            runWithTimer(function, "Running program time: \t\t\t\t");
        } else {
            function();
        }
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
        GS_CrossPlatform::setConsoleColor(ConsoleColor::RED);

        RunningFunction function = [] () -> GSVoid {
            GS_Debug::printDebugInformation("\n----------READER OUT START----------\n", "\n----------READER OUT END----------\n",
                                            &GS_DebugFunctions::printReaderDebugInfo, _compilerData.inputSource);

            GS_Debug::printDebugInformation("\n----------LEXER OUT START----------\n", "\n----------LEXER OUT END----------\n",
                                            &GS_DebugFunctions::printLexerDebugInfo, _compilerData.lexerTokens);

            GS_Debug::printASTDebugInfo("\n----------PARSER OUT START----------\n", "\n----------PARSER OUT END----------\n",
                                            _compilerData.parserStatements);

            GS_Debug::printASTDebugInfo("\n----------OPTIMIZATION OUT START----------\n", "\n----------OPTIMIZATION OUT END----------\n",
                                            _compilerData.optimizedParserStatements);
//
//            GS_Debug::printCodeGeneratorDebugInfo("\n----------CODE GENERATOR OUT START----------\n", "\n----------CODE GENERATOR OUT END----------\n",
//                                                  _compilerData.codeGeneratorByteCode);
        };

        runWithTimer(function, "Printing debug info time: \t\t\t");

        GS_CrossPlatform::resetConsoleColor();
    }

}