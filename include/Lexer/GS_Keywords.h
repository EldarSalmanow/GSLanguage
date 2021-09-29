#ifndef GSLANGUAGE_GS_KEYWORDS_H
#define GSLANGUAGE_GS_KEYWORDS_H

#include <GSCrossPlatform/GS_CrossPlatformTypes.h>

namespace GSLanguageCompiler::Lexer {

    using SymbolT = CharType;

    /**
     * Type of token
     */
    enum class TokenType {
        END_OF_FILE,
        NEW_LINE,

        WORD,                     // main

        LITERAL_STRING,           // "hello"
        LITERAL_NUMBER,           // 12

        KEYWORD_VAR,              // var
        KEYWORD_IF,               // if
        KEYWORD_PRINT,            // print

        SYMBOL_LEFT_PARENTHESES,  // (
        SYMBOL_RIGHT_PARENTHESES, // )
        SYMBOL_LBRACE,            // {
        SYMBOL_RBRACE,            // }

        SYMBOL_LT,                // <
        SYMBOL_GT,                // >

        SYMBOL_DOT,               // .
        SYMBOL_COLON,             // :
        SYMBOL_QUOTES,            // '
        SYMBOL_DOUBLE_QUOTES,     // "

        SYMBOL_PLUS,              // +
        SYMBOL_MINUS,             // -
        SYMBOL_STAR,              // *
        SYMBOL_SLASH,             // /
        SYMBOL_EQ                 // =
    };

    /**
     * Token type to string
     */
    extern Map<TokenType, String> tokenTypeToString;

    /**
     * Reserved letters
     */
    extern Map<String, TokenType> reservedWords;

    /**
     * Reserved symbols
     */
    extern Map<SymbolT, TokenType> reservedSymbols;

}

#endif //GSLANGUAGE_GS_KEYWORDS_H
