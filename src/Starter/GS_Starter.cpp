#include <Starter/GS_Starter.h>

namespace GSLanguageCompiler::Starter {

    static llvm::cl::opt<std::string> inputFilename("f",
                                                    llvm::cl::Required,
                                                    llvm::cl::ValueRequired,
                                                    llvm::cl::desc("Input filename"),
                                                    llvm::cl::value_desc("filename"));

    static llvm::cl::opt<std::string> outputFilename("o",
                                                     llvm::cl::ValueRequired,
                                                     llvm::cl::desc("Output filename"),
                                                     llvm::cl::value_desc("filename"));

    static llvm::cl::opt<bool> testingFlag("t",
                                           llvm::cl::desc("Testing mode"));

    GSInt GS_Starter::start(GSInt argc, GSChar **argv) {
        try {
            llvm::cl::ParseCommandLineOptions(argc, argv);

            GS_Context context;
//            startCompiling();
        } catch (Exceptions::GS_Exception &exception) {
            return 1;
        } catch (std::exception &exception) {
            Exceptions::errorHandler.print(GSLanguageCompiler::Exceptions::ErrorLevel::FATAL_LVL,
                                           exception.what());

            Exceptions::errorHandler.print(Exceptions::ErrorLevel::NOTE_LVL,
                                           "Please, report this fatal error to GSLanguageCompiler repository.");

            Exceptions::errorHandler.throw_();

            return 2;
        } catch (...) {
            Exceptions::errorHandler.print(GSLanguageCompiler::Exceptions::ErrorLevel::FATAL_LVL,
                                           "Unknown fatal error!");

            Exceptions::errorHandler.print(Exceptions::ErrorLevel::NOTE_LVL,
                                           "Please, report this fatal error to GSLanguageCompiler repository.");

            Exceptions::errorHandler.throw_();

            return 3;
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

        // semantic analyzing AST
        startSemanticAnalyzer();

        // optimizing parser AST
        startOptimizer();

        // generating code from AST
        generateCode();

        if (testingFlag.getValue()) {
            // start debug mode
            startDebugMode();
        }
    }

    GSVoid GS_Starter::startReader() {
        auto reader = std::make_shared<GS_Reader>(inputFilename.getValue());

        _compilerData.inputSource = reader->readFile();
    }

    GSVoid GS_Starter::startLexer() {
        auto lexer = std::make_shared<GS_Lexer>(_compilerData.inputSource);

        _compilerData.lexerTokens = lexer->tokenize();
    }

    GSVoid GS_Starter::startParser() {
        auto parser = std::make_shared<GS_Parser>(_compilerData.lexerTokens);

        _compilerData.parserStatements = parser->parse();
    }

    GSVoid GS_Starter::startSemanticAnalyzer() {
        GSSemanticPassPtrArray passes = {
                std::make_shared<GS_TypePlaceholderPass>(),
                std::make_shared<GS_TypeCheckerPass>(),
                std::make_shared<GS_VariablesPlaceholderPass>()
        };

        auto semanticAnalyzer = std::make_shared<GS_Semantic>(_compilerData.parserStatements, passes);

        semanticAnalyzer->analyze();
    }

    GSVoid GS_Starter::startOptimizer() {
        GSOptimizerPassPtrArray passes = {
                std::make_shared<GS_ConstantFoldingPass>()
        };

        auto optimizer = std::make_shared<GS_Optimizer>(_compilerData.parserStatements, passes);

        _compilerData.optimizedParserStatements = optimizer->optimize();
    }

    GSVoid GS_Starter::generateCode() {
        auto codeGenerator = std::make_shared<GS_CodeGenerator>(_compilerData.optimizedParserStatements);

        codeGenerator->codegen();
    }

    GSVoid GS_Starter::startDebugMode() {
        GS_CrossPlatform::setFgConsoleColor(ConsoleColor::RED);
        GS_CrossPlatform::setConsoleStyle(ConsoleStyle::BOLD);

        _debug.printMessage("\n!Reader debug info!\n");

        _debug.startReaderDebugMode(_compilerData.inputSource);

        _debug.printMessage("\n!Lexer debug info!\n");

        _debug.startLexerDebugMode(_compilerData.lexerTokens);

        _debug.printMessage("\n!Parser debug info!\n");

        _debug.startParserDebugMode(_compilerData.parserStatements);

        _debug.printMessage("\n!Optimizer debug info!\n");

        _debug.startOptimizerDebugMode(_compilerData.optimizedParserStatements);

        GS_CrossPlatform::resetConsoleStyle();
        GS_CrossPlatform::resetFgConsoleColor();
    }

}