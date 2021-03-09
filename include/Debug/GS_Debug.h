#ifndef GSLANGUAGE_GS_DEBUG_H
#define GSLANGUAGE_GS_DEBUG_H

#if defined(__WIN32)
#include <windows.h>
#else
#error Platform not supported!
#endif

#include "../Compiler/Lexer/GS_Lexer.h"
#include "../Compiler/Parser/GS_Parser.h"
#include "../Compiler/Reader/GS_Reader.h"

namespace Debug {

    /**
     * Class for debugging and testing input and output compilation parameters GSLanguageCompiler
     */
    class GS_Debug {
    public:

        /**
         * Printing input code from file
         * @param input Container with std::string
         */
        static void printInput(GSLanguageCompiler::GSText &input);

        /**
         * Printing tokens before lexer analyzing
         * @param tokens Container with GS_Token
         */
        static void printLexerOutput(GSLanguageCompiler::GSTokenArray &tokens);

        /**
         * Printing statements before parsing analyzing
         * @param statements Container with GSStatementPointer
         */
        static void printParserOutput(GSLanguageCompiler::GSStatementPointerArray &statements);

    private:

        /**
         * Available console colors for Windows
         */
        enum ConsoleColor {
            BLACK = 0,
            BLUE = 1,
            GREEN = 2,
            CYAN = 3,
            RED = 4,
            MAGENTA = 5,
            BROWN = 6,
            LIGHT_GRAY = 7,
            DARK_GRAY = 8,
            LIGHT_BLUE = 9,
            LIGHT_GREEN = 10,
            LIGHT_CYAN = 11,
            LIGHT_RED = 12,
            LIGHT_MAGENTA = 13,
            YELLOW = 14,
            WHITE = 15
        };

    private:

        /**
         * Setting console color
         * @param background Background color
         * @param text Text color
         */
        static void setConsoleColor(ConsoleColor background, ConsoleColor text);

        /**
         * Converting TokenType to std::string
         * @param type Token type
         * @return Converted type
         */
        static std::string tokenTypeToString(GSLanguageCompiler::TokenType type);
    };

}

#endif //GSLANGUAGE_GS_DEBUG_H
