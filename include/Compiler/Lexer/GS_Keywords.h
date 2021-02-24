#ifndef GSLANGUAGE_GS_KEYWORDS_H
#define GSLANGUAGE_GS_KEYWORDS_H

#include <map>

namespace GSLanguageCompiler {

    /**
     * Type of token
     */
    enum class TokenType {
        END_OF_FILE,
        NEW_LINE,

        WORD,                     // main

        TYPE_STRING,              // "hello"
        TYPE_NUMBER,              // 12

        KEYWORD_VAR,              // var
        KEYWORD_IF,               // if

        SYMBOL_LEFT_PARENTHESES,  // (
        SYMBOL_RIGHT_PARENTHESES, // )
        SYMBOL_DOT,               // .
        SYMBOL_COLON,             // :
        SYMBOL_PLUS,              // +
        SYMBOL_MINUS,             // -
        SYMBOL_STAR,              // *
        SYMBOL_SLASH,             // /
        SYMBOL_EQ                 // =
    };

    /**
     * Reserved letters and symbols
     */
    extern std::map<std::string, TokenType> reserved;

}

#endif //GSLANGUAGE_GS_KEYWORDS_H
