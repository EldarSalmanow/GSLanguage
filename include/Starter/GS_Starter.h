#ifndef GSLANGUAGE_GS_STARTER_H
#define GSLANGUAGE_GS_STARTER_H

#include "../../include/Debug/GS_Timer.h"
#include "../../include/Debug/GS_Debug.h"

#include "../../include/Compiler/Util/GS_Arguments.h"
#include "../../include/Compiler/Reader/GS_Reader.h"
#include "../../include/Compiler/Lexer/GS_Lexer.h"
#include "../../include/Compiler/Parser/GS_Parser.h"

namespace Starter {

    using namespace GSLanguageCompiler;

    using namespace Lexer;

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
        static int start(int argc, char **argv);

    private:

        /**
        * Start compiling function
        * @param arguments Command line arguments before argument analyzing
        */
        static void startCompiling();

        /**
        * Function for parsing command line arguments and generating config for compiling
        * @param argc Number of arguments
        * @param argv Array of arguments
        * @return Configs for compiling
        */
        static void parseArguments(int argc, char **argv);

        /**
         * Start reading source from file
         */
        static void startReader();

        /**
         * Start lexer analyzing source
         */
        static void startLexer();

        /**
         * Start parser analyzing tokens
         */
        static void startParser();

        /**
         * Start debug functions
         */
        static void startDebugMode();

    private:

        /**
         * Class for functions for timers and timers
         */
        class _Timers {
        private:

            /**
             * Initialized functions for timers
             */
            inline static std::function<void()> startFunction = startCompiling;
            inline static std::function<GSText(GS_Reader&)> readerFunction = &GS_Reader::readFile;
            inline static std::function<GSTokenArray(GS_Lexer&)> lexerFunction = &GS_Lexer::tokenize;
            inline static std::function<GSStatementPointerArray(GS_Parser&)> parserFunction = &GS_Parser::parse;

        public:

            /**
             * Timers for profiling compiler
             */
            inline static Debug::GS_Timer<void()> totalTimer = startFunction;
            inline static Debug::GS_Timer<GSText(GS_Reader&)> readerTimer = readerFunction;
            inline static Debug::GS_Timer<GSTokenArray(GS_Lexer&)> lexerTimer = lexerFunction;
            inline static Debug::GS_Timer<GSStatementPointerArray(GS_Parser&)> parserTimer = parserFunction;
        };

        class _CompilerData {
        public:

            /**
             * Command line arguments
             */
            inline static GSArgumentsPointer arguments;

            /**
             * Source from file
             */
            inline static GSText inputSource;

            /**
             * Tokens before lexer analyzing
             */
             inline static GSTokenArray tokens;

             /**
              * Statements before parser analyzing
              */
             inline static GSStatementPointerArray statements;
        };
    };

}

#endif //GSLANGUAGE_GS_STARTER_H
