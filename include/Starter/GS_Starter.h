#ifndef GSLANGUAGE_GS_STARTER_H
#define GSLANGUAGE_GS_STARTER_H

#include "../../include/Debug/GS_Timer.h"
#include "../../include/Debug/GS_Debug.h"

#include "../../include/Compiler/Util/GS_Arguments.h"
#include "../../include/Compiler/Reader/GS_Reader.h"
#include "../../include/Compiler/Lexer/GS_Lexer.h"
#include "../../include/Compiler/Parser/GS_Parser.h"
#include "../../include/Compiler/CodeGenerator/GS_CodeGenerator.h"

namespace Starter {

    using namespace GSLanguageCompiler;

    using namespace Lexer;
    using namespace Parser;
    using namespace CodeGenerator;

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
         * @param statement
         * @return
         */
        static GSVoid printParserDebugInfo(GSStatementPointer &statement);
    };

    /**
     *
     */
    class GS_CompilerData {
    public:

        /**
         *
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
        GSStatementPointerArray parserStatements;

        /**
         * Code before code generator
         */
        GSGeneratedCode codeGeneratorCode;
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
         * Start code generator for generating output code
         */
        static GSVoid generateCode();

        /**
         * Start debug functions
         */
        static GSVoid startDebugMode();

    private:

        /**
         *
         */
        inline static GS_CompilerData _compilerData;

        /**
         *
         */
        inline static GS_Timer _timer;
    };

}

#endif //GSLANGUAGE_GS_STARTER_H
