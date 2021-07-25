#ifndef GSLANGUAGE_GS_KEYWORDS_H
#define GSLANGUAGE_GS_KEYWORDS_H

#include <map>

#include <CrossPlatform/GS_PlatformTypes.h>

namespace GSLanguageCompiler::Lexer {

    /**
     * Type of token
     */
    enum class TokenType {
        END_OF_FILE,
        NEW_LINE,

        WORD,                     // main

        LITERAL_STRING,           // "hello"
        LITERAL_NUMBER,           // 12

//        KEYWORD_TYPE_INT,         // Int
//        KEYWORD_TYPE_STRING,      // String

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
    extern std::map<TokenType, GSString> tokenTypeToString;

    /**
     * Reserved letters and symbols
     */
    extern std::map<GSString, TokenType> reserved;

}

#endif //GSLANGUAGE_GS_KEYWORDS_H
