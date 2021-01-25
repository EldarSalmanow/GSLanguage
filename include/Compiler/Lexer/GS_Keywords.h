#ifndef GSLANGUAGE_GS_KEYWORDS_H
#define GSLANGUAGE_GS_KEYWORDS_H

#include <map>

namespace GSLanguageCompiler {
    enum TokenType {
        END_OF_FILE,
        NEW_LINE,

        WORD,
        TYPE_STRING,
        TYPE_NUMBER,
        KEYWORD_VAR,
        KEYWORD_IF,
        SYMBOL_LEFT_PARENTHESES,
        SYMBOL_RIGHT_PARENTHESES
    };

    extern std::map<std::string, TokenType> reserved;
}

#endif //GSLANGUAGE_GS_KEYWORDS_H
