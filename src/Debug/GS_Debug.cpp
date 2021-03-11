#include "../../include/Debug/GS_Debug.h"

namespace Debug {

    void GS_Debug::printInput(GSLanguageCompiler::GSText &input) {
        std::cout << std::endl;

        GS_CrossPlatform::setConsoleColor(GS_CrossPlatform::BLACK, GS_CrossPlatform::RED);

        for (auto &line : input) {
            std::cout << line << std::endl;
        }

        GS_CrossPlatform::setConsoleColor(GS_CrossPlatform::BLACK, GS_CrossPlatform::LIGHT_GRAY);
    }

    void GS_Debug::printLexerOutput(GSLanguageCompiler::GSTokenArray &tokens) {
        GS_CrossPlatform::setConsoleColor(GS_CrossPlatform::BLACK, GS_CrossPlatform::RED);

        std::cerr << "\n----------LEXER OUT START----------\n" << std::endl;

        for (auto &token : tokens) {
            std::cerr << tokenTypeToString(token.getType()) << std::endl;
        }

        std::cerr << "\n----------LEXER OUT END----------\n" << std::endl;

        GS_CrossPlatform::setConsoleColor(GS_CrossPlatform::BLACK, GS_CrossPlatform::LIGHT_GRAY);
    }

    void GS_Debug::printParserOutput(GSLanguageCompiler::GSStatementPointerArray &statements) {
        GS_CrossPlatform::setConsoleColor(GS_CrossPlatform::BLACK, GS_CrossPlatform::RED);

        std::cerr << "\n----------PARSER OUT START----------\n" << std::endl;

        for (auto &statement : statements) {
            std::cerr << statement->toString() << std::endl;
        }

        std::cerr << "\n----------PARSER OUT END----------\n" << std::endl;

        GS_CrossPlatform::setConsoleColor(GS_CrossPlatform::BLACK, GS_CrossPlatform::LIGHT_GRAY);
    }

    std::string GS_Debug::tokenTypeToString(GSLanguageCompiler::TokenType type) {
        switch (type) {
            case GSLanguageCompiler::TokenType::WORD:
                return "WORD";
            case GSLanguageCompiler::TokenType::LITERAL_STRING:
                return "LITERAL_STRING";
            case GSLanguageCompiler::TokenType::LITERAL_NUMBER:
                return "LITERAL_NUMBER";

            case GSLanguageCompiler::TokenType::KEYWORD_INT:
                return "KEYWORD_INT  :  \'Int\'";
            case GSLanguageCompiler::TokenType::KEYWORD_STRING:
                return "KEYWORD_STRING  :  \'String\'";

            case GSLanguageCompiler::TokenType::KEYWORD_VAR:
                return "KEYWORD_VAR  :  \'var\'";
            case GSLanguageCompiler::TokenType::KEYWORD_IF:
                return "KEYWORD_IF  :  \'if\'";

            case GSLanguageCompiler::TokenType::SYMBOL_LEFT_PARENTHESES:
                return "SYMBOL_LEFT_PARENTHESES  :  \'(\'";
            case GSLanguageCompiler::TokenType::SYMBOL_RIGHT_PARENTHESES:
                return "SYMBOL_RIGHT_PARENTHESES  :  \')\'";
            case GSLanguageCompiler::TokenType::SYMBOL_LBRACE:
                return "SYMBOL_LBRACE  :  \'{\'";
            case GSLanguageCompiler::TokenType::SYMBOL_RBRACE:
                return "SYMBOL_RBRACE  :  \'}\'";

            case GSLanguageCompiler::TokenType::SYMBOL_LT:
                return "SYMBOL_LT  :  \'<\'";
            case GSLanguageCompiler::TokenType::SYMBOL_GT:
                return "SYMBOL_GT  :  \'>\'";

            case GSLanguageCompiler::TokenType::SYMBOL_DOT:
                return "SYMBOL_DOT  :  \'.\'";
            case GSLanguageCompiler::TokenType::SYMBOL_COLON:
                return "SYMBOL_COLON  :  \':\'";
            case GSLanguageCompiler::TokenType::SYMBOL_QUOTES:
                return "SYMBOL_QUOTES  :  \'\'\'";
            case GSLanguageCompiler::TokenType::SYMBOL_DOUBLE_QUOTES:
                return "SYMBOL_DOUBLE_QUOTES  :  \'\"\'";

            case GSLanguageCompiler::TokenType::SYMBOL_PLUS:
                return "SYMBOL_PLUS  :  \'+\'";
            case GSLanguageCompiler::TokenType::SYMBOL_MINUS:
                return "SYMBOL_MINUS  :  \'-\'";
            case GSLanguageCompiler::TokenType::SYMBOL_STAR:
                return "SYMBOL_STAR  :  \'*\'";
            case GSLanguageCompiler::TokenType::SYMBOL_SLASH:
                return "SYMBOL_SLASH  :  \'/\'";
            case GSLanguageCompiler::TokenType::SYMBOL_EQ:
                return "SYMBOL_EQ  :  \'=\'";

            case GSLanguageCompiler::TokenType::NEW_LINE:
                return "NEW_LINE";
            case GSLanguageCompiler::TokenType::END_OF_FILE:
                return "END_OF_FILE";
        }
        return "!!ERROR!!";
    }
}