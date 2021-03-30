#ifndef GSLANGUAGE_GS_DEBUG_H
#define GSLANGUAGE_GS_DEBUG_H

#include "../Compiler/Lexer/GS_Lexer.h"
#include "../Compiler/Parser/GS_Parser.h"
#include "../Compiler/Reader/GS_Reader.h"
#include "../Compiler/Parser/GS_TableOfSymbols.h"
#include "../Compiler/Util/GS_CrossPlatform.h"

namespace Debug {

    using namespace Platform;

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

        /**
         *
         */
        static void printTableOfSymbols();

    private:

        /**
         * Converting TokenType to std::string
         * @param type Token type
         * @return Converted type
         */
        static std::string tokenTypeToString(GSLanguageCompiler::TokenType type);
    };

}

#endif //GSLANGUAGE_GS_DEBUG_H
