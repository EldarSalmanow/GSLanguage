#ifndef GSLANGUAGE_GS_STARTER_H
#define GSLANGUAGE_GS_STARTER_H

#include <Debug/GS_Timer.h>
#include <Debug/GS_Debug.h>

#include <ArgumentsParser/GS_Arguments.h>
#include <Reader/GS_Reader.h>
#include <Lexer/GS_Lexer.h>
#include <Parser/GS_Parser.h>
#include <Optimizer/GS_Optimizer.h>
#include <CodeGenerator/GS_CodeGenerator.h>
#include <Interpreter/GS_Interpreter.h>

namespace Starter {

    using namespace GSLanguageCompiler;

    using namespace Lexer;
    using namespace Parser;
    using namespace Optimizer;
    using namespace CodeGenerator;
    using namespace Interpreter;

    using namespace Debug;

    /**
     *
     */
    class GS_DebugFunctions {
    public:

        /**
         *
         * @param string
         * @return
         */
        static GSVoid printReaderDebugInfo(GSString &string);

        /**
         *
         * @param token
         * @return
         */
        static GSVoid printLexerDebugInfo(GS_Token &token);

        /**
         *
         * @param nodePtr
         * @return
         */
        static GSVoid printParserDebugInfo(GSNodePtr &nodePtr);

        /**
         *
         * @param nodePtr
         * @return
         */
        static GSVoid printOptimizerDebugInfo(GSNodePtr &nodePtr);
    };

    /**
     * Class for containing compiler data
     */
    class GS_CompilerData {
    public:

        /**
         * Default constructor
         */
        GS_CompilerData() = default;

    public:

        /**
         * Command line arguments
         */
        GS_ArgumentsOptions argumentsOptions;

        /**
         * Source from file
         */
        GSText inputSource;

        /**
         * Tokens before lexer analyzing
         */
        GSTokenArray lexerTokens;

        /**
         * Statements before parser analyzing
         */
        GSNodePtrArray parserStatements;

        /**
         * Optimized statements
         */
        GSNodePtrArray optimizedParserStatements;

        /**
         * Bytecode for GSVirtualMachine before code generator
         */
        GSByteCode codeGeneratorByteCode;
    };

    /**
     * Class for starting GSLanguageCompiler
     */
    class GS_Starter {
    public:

        /**
         * Starting compiler, error handlers and timers
         * @param argc Number of arguments
         * @param argv Array of arguments
         * @return Status number for operation system
         */
        static GSInt start(GSInt argc, GSChar **argv);

    private:

        /**
        * Start compiling function
        * @param arguments Command line arguments before argument analyzing
        */
        static GSVoid startCompiling();

        /**
        * Function for parsing command line arguments and generating config for compiling
        * @param argc Number of arguments
        * @param argv Array of arguments
        * @return Configs for compiling
        */
        static GSVoid parseArguments(GSInt argc, GSChar **argv);

        /**
         * Function for run any function with profiling and writing profiling result
         * @param function Function for running with profiling
         * @param messageForProfiling Message for adding profiling result
         * @return
         */
        static GSVoid runWithTimer(std::function<GSVoid()> &function, GSString messageForProfiling);

        /**
         * Start reading source from file
         */
        static GSVoid startReader();

        /**
         * Start lexer analyzing source
         */
        static GSVoid startLexer();

        /**
         * Start parser analyzing tokens
         */
        static GSVoid startParser();

        /**
         * Start optimizer for optimize AST
         */
        static GSVoid startOptimizer();

        /**
         * Start code generator for generating output code
         */
        static GSVoid generateCode();

        /**
         * Starting interpreter
         */
        static GSVoid startInterpreter();

        /**
         * Start debug functions
         */
        static GSVoid startDebugMode();

    private:

        /**
         * Compiler data
         */
        inline static GS_CompilerData _compilerData;

        /**
         * Timer for profiling
         */
        inline static GS_Timer _timer;
    };

}

#endif //GSLANGUAGE_GS_STARTER_H
