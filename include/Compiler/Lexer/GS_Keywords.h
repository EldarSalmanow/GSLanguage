#ifndef GSLANGUAGE_GS_KEYWORDS_H
#define GSLANGUAGE_GS_KEYWORDS_H

#include <map>
#include <string>

namespace GSLanguageCompiler {

    /**
     * Type of token
     */
    enum class TokenType {
        END_OF_FILE,
        NEW_LINE,

        WORD,                     // main

        LITERAL_STRING,           // "hello"
        LITERAL_NUMBER,           // 12

        KEYWORD_INT,              // Int
        KEYWORD_STRING,           // String

        KEYWORD_VAR,              // var
        KEYWORD_IF,               // if

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
     * Reserved letters and symbols
     */
    extern std::map<std::string, TokenType> reserved;

}

#endif //GSLANGUAGE_GS_KEYWORDS_H
