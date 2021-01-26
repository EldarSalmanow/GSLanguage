#ifndef GSLANGUAGE_TESTS_H
#define GSLANGUAGE_TESTS_H

#include "../include/Compiler/Lexer/GS_Lexer.h"

using namespace GSLanguageCompiler;

namespace Testing {

    /**
    * Function for testing GS_Lexer class<br>
    * Note: Do not use in final version!
    * @param type Enum input type
    * @return String name of enum
    */
    std::string enumToString(TokenType type) {
        switch (type) {
            case WORD:
                return "WORD";
            case TYPE_STRING:
                return "TYPE_STRING";
            case TYPE_NUMBER:
                return "TYPE_NUMBER";
            case KEYWORD_VAR:
                return "KEYWORD_VAR";
            case KEYWORD_IF:
                return "KEYWORD_IF";
            case SYMBOL_LEFT_PARENTHESES:
                return "SYMBOL_LEFT_PARENTHESES";
            case SYMBOL_RIGHT_PARENTHESES:
                return "SYMBOL_RIGHT_PARENTHESES";
            case SYMBOL_DOT:
                return "SYMBOL_DOT";
            case SYMBOL_PLUS:
                return "SYMBOL_PLUS";
            case SYMBOL_MINUS:
                return "SYMBOL_MINUS";
            case SYMBOL_STAR:
                return "SYMBOL_STAR";
            case SYMBOL_SLASH:
                return "SYMBOL_SLASH";
            case NEW_LINE:
                return "NEW_LINE";
            case END_OF_FILE:
                return "END_OF_FILE";
        }
        return "!!ERROR!!";
    }

    /**
     * Function for testing the GS_Reader class<br>
     * Note: Do not use in the final version!
     * @param input The container that holds the code
     */
    void printInput(std::vector<std::string> &input) {
        for (auto &line : input) {
            std::cout << line << std::endl;
        }
    }

    /**
     * Function for testing the GS_Lexer class<br>
     * Note: Do not use in final version!
     * @param tokens The container of tokens, before lexing analyzing
     */
    void printTokenTypes(std::vector<GSLanguageCompiler::GS_Token> &tokens) {
        for (auto &token : tokens) {
            std::cout << enumToString(token.getType()) << std::endl;
        }
    }

}

#endif //GSLANGUAGE_TESTS_H
