#include "../../../include/Compiler/Lexer/GS_Keywords.h"

namespace GSLanguageCompiler {

    std::map<std::string, TokenType> reserved = {
            {"var", TokenType::KEYWORD_VAR},
            {"if",  TokenType::KEYWORD_IF},

            {"(",   TokenType::SYMBOL_LEFT_PARENTHESES},
            {")",   TokenType::SYMBOL_RIGHT_PARENTHESES},
            {".",   TokenType::SYMBOL_DOT},
            {":",   TokenType::SYMBOL_COLON},
            {"+",   TokenType::SYMBOL_PLUS},
            {"-",   TokenType::SYMBOL_MINUS},
            {"*",   TokenType::SYMBOL_STAR},
            {"/",   TokenType::SYMBOL_SLASH},
            {"=",   TokenType::SYMBOL_EQ}
    };

}