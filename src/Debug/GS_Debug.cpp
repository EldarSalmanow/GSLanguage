#include <Debug/GS_Debug.h>

namespace Debug {

    std::string GS_Debug::tokenTypeToString(GSLanguageCompiler::Lexer::TokenType type) {
        switch (type) {
            case GSLanguageCompiler::Lexer::TokenType::WORD:
                return "WORD";
            case GSLanguageCompiler::Lexer::TokenType::LITERAL_STRING:
                return "LITERAL_STRING";
            case GSLanguageCompiler::Lexer::TokenType::LITERAL_NUMBER:
                return "LITERAL_NUMBER";

            case GSLanguageCompiler::Lexer::TokenType::KEYWORD_TYPE_INT:
                return "KEYWORD_TYPE_INT  :  \'Int\'";
            case GSLanguageCompiler::Lexer::TokenType::KEYWORD_TYPE_STRING:
                return "KEYWORD_TYPE_STRING  :  \'String\'";

            case GSLanguageCompiler::Lexer::TokenType::KEYWORD_VAR:
                return "KEYWORD_VAR  :  \'var\'";
            case GSLanguageCompiler::Lexer::TokenType::KEYWORD_IF:
                return "KEYWORD_IF  :  \'if\'";

            case GSLanguageCompiler::Lexer::TokenType::SYMBOL_LEFT_PARENTHESES:
                return "SYMBOL_LEFT_PARENTHESES  :  \'(\'";
            case GSLanguageCompiler::Lexer::TokenType::SYMBOL_RIGHT_PARENTHESES:
                return "SYMBOL_RIGHT_PARENTHESES  :  \')\'";
            case GSLanguageCompiler::Lexer::TokenType::SYMBOL_LBRACE:
                return "SYMBOL_LBRACE  :  \'{\'";
            case GSLanguageCompiler::Lexer::TokenType::SYMBOL_RBRACE:
                return "SYMBOL_RBRACE  :  \'}\'";

            case GSLanguageCompiler::Lexer::TokenType::SYMBOL_LT:
                return "SYMBOL_LT  :  \'<\'";
            case GSLanguageCompiler::Lexer::TokenType::SYMBOL_GT:
                return "SYMBOL_GT  :  \'>\'";

            case GSLanguageCompiler::Lexer::TokenType::SYMBOL_DOT:
                return "SYMBOL_DOT  :  \'.\'";
            case GSLanguageCompiler::Lexer::TokenType::SYMBOL_COLON:
                return "SYMBOL_COLON  :  \':\'";
            case GSLanguageCompiler::Lexer::TokenType::SYMBOL_QUOTES:
                return "SYMBOL_QUOTES  :  \'\'\'";
            case GSLanguageCompiler::Lexer::TokenType::SYMBOL_DOUBLE_QUOTES:
                return "SYMBOL_DOUBLE_QUOTES  :  \'\"\'";

            case GSLanguageCompiler::Lexer::TokenType::SYMBOL_PLUS:
                return "SYMBOL_PLUS  :  \'+\'";
            case GSLanguageCompiler::Lexer::TokenType::SYMBOL_MINUS:
                return "SYMBOL_MINUS  :  \'-\'";
            case GSLanguageCompiler::Lexer::TokenType::SYMBOL_STAR:
                return "SYMBOL_STAR  :  \'*\'";
            case GSLanguageCompiler::Lexer::TokenType::SYMBOL_SLASH:
                return "SYMBOL_SLASH  :  \'/\'";
            case GSLanguageCompiler::Lexer::TokenType::SYMBOL_EQ:
                return "SYMBOL_EQ  :  \'=\'";

            case GSLanguageCompiler::Lexer::TokenType::NEW_LINE:
                return "NEW_LINE";
            case GSLanguageCompiler::Lexer::TokenType::END_OF_FILE:
                return "END_OF_FILE";
        }
        return "!!ERROR!!";
    }
}