#include "../../../include/Compiler/Lexer/GS_Keywords.h"

namespace GSLanguageCompiler {

    std::map<std::string, TokenType> reserved = {
            {"Int",   TokenType::KEYWORD_INT},
            {"String",TokenType::KEYWORD_STRING},

            {"var",   TokenType::KEYWORD_VAR},
            {"if",    TokenType::KEYWORD_IF},

            {"(",     TokenType::SYMBOL_LEFT_PARENTHESES},
            {")",     TokenType::SYMBOL_RIGHT_PARENTHESES},
            {"{",     TokenType::SYMBOL_LBRACE},
            {"}",     TokenType::SYMBOL_RBRACE},

            {"<",     TokenType::SYMBOL_LT},
            {">",     TokenType::SYMBOL_GT},

            {".",     TokenType::SYMBOL_DOT},
            {":",     TokenType::SYMBOL_COLON},
            {"\'",    TokenType::SYMBOL_QUOTES},
            {"\"",    TokenType::SYMBOL_DOUBLE_QUOTES},

            {"+",     TokenType::SYMBOL_PLUS},
            {"-",     TokenType::SYMBOL_MINUS},
            {"*",     TokenType::SYMBOL_STAR},
            {"/",     TokenType::SYMBOL_SLASH},
            {"=",     TokenType::SYMBOL_EQ}
    };

}