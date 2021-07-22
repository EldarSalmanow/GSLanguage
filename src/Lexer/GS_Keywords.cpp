#include <GS_Keywords.h>

namespace GSLanguageCompiler::Lexer {

    std::map<TokenType, GSString> tokenTypeToString = {
            {TokenType::END_OF_FILE,             "END_OF_FILE"},
            {TokenType::NEW_LINE,                "NEW_LINE"},

            {TokenType::WORD,                     "WORD"},

            {TokenType::LITERAL_STRING,           "LITERAL_STRING"},
            {TokenType::LITERAL_NUMBER,           "LITERAL_NUMBER"},

            {TokenType::KEYWORD_TYPE_INT,         "KEYWORD_TYPE_INT"},
            {TokenType::KEYWORD_TYPE_STRING,      "KEYWORD_TYPE_STRING"},

            {TokenType::KEYWORD_VAR,              "KEYWORD_VAR"},
            {TokenType::KEYWORD_IF,               "KEYWORD_IF"},

            {TokenType::SYMBOL_LEFT_PARENTHESES,  "SYMBOL_LEFT_PARENTHESES"},
            {TokenType::SYMBOL_RIGHT_PARENTHESES, "SYMBOL_RIGHT_PARENTHESES"},
            {TokenType::SYMBOL_LBRACE,            "SYMBOL_LBRACE"},
            {TokenType::SYMBOL_RBRACE,            "SYMBOL_RBRACE"},

            {TokenType::SYMBOL_LT,                "SYMBOL_LT"},
            {TokenType::SYMBOL_GT,                "SYMBOL_GT"},

            {TokenType::SYMBOL_DOT,               "SYMBOL_DOT"},
            {TokenType::SYMBOL_COLON,             "SYMBOL_COLON"},
            {TokenType::SYMBOL_QUOTES,            "SYMBOL_QUOTES"},
            {TokenType::SYMBOL_DOUBLE_QUOTES,     "SYMBOL_DOUBLE_QUOTES"},

            {TokenType::SYMBOL_PLUS,              "SYMBOL_PLUS"},
            {TokenType::SYMBOL_MINUS,             "SYMBOL_MINUS"},
            {TokenType::SYMBOL_STAR,              "SYMBOL_STAR"},
            {TokenType::SYMBOL_SLASH,             "SYMBOL_SLASH"},
            {TokenType::SYMBOL_EQ,                "SYMBOL_EQ"}
    };

    std::map<GSString, TokenType> reserved = {
            {"Int",   TokenType::KEYWORD_TYPE_INT},
            {"String",TokenType::KEYWORD_TYPE_STRING},

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