#include "../../../include/Compiler/Lexer/GS_Keywords.h"

namespace GSLanguageCompiler {

    std::map<std::string, TokenType> reserved = {
            {"var", KEYWORD_VAR},
            {"if",  KEYWORD_IF},

            {"(",   SYMBOL_LEFT_PARENTHESES},
            {")",   SYMBOL_RIGHT_PARENTHESES},
            {".",   SYMBOL_DOT},
            {"+",   SYMBOL_PLUS},
            {"-",   SYMBOL_MINUS},
            {"*",   SYMBOL_STAR},
            {"/",   SYMBOL_SLASH}
    };

}