#ifndef GSLANGUAGE_GS_STARTER_H
#define GSLANGUAGE_GS_STARTER_H

#include <Starter/GS_Context.h>

#include <llvm/Support/CommandLine.h>

#include <Debug/GS_Debug.h>

#include <Reader/GS_Reader.h>
#include <Lexer/GS_Lexer.h>
#include <Parser/GS_Parser.h>
#include <Semantic/GS_Semantic.h>
#include <Optimizer/GS_Optimizer.h>
#include <CodeGenerator/GS_CodeGenerator.h>

#include <CrossPlatform/GS_CrossPlatform.h>

namespace GSLanguageCompiler::Starter {

    using namespace Lexer;
    using namespace Parser;
    using namespace Semantic;
    using namespace Optimizer;
    using namespace CodeGenerator;

    using namespace Debug;

    using namespace Platform;

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
        GSNodePtr parserStatements;

        /**
         * Optimized statements
         */
        GSNodePtr optimizedParserStatements;
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
         *
         */
        static GSVoid startSemanticAnalyzer();

        /**
         * Start optimizer for optimize AST
         */
        static GSVoid startOptimizer();

        /**
         * Start code generator for generating output code
         */
        static GSVoid generateCode();

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
         *
         */
        inline static GS_Debug _debug;

        static GS_Context _context;
    };

}

#endif //GSLANGUAGE_GS_STARTER_H
