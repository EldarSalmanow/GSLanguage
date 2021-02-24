#ifndef GSLANGUAGE_TESTS_H
#define GSLANGUAGE_TESTS_H

#if defined(__WIN32)
#include <windows.h>
#endif

#include "../include/Compiler/Lexer/GS_Lexer.h"

namespace Testing {

    /**
     * Supported console colors
     */
    enum ConsoleColor {
        BLACK = 0,
        BLUE = 1,
        GREEN = 2,
        CYAN = 3,
        RED = 4,
        MAGENTA = 5,
        BROWN = 6,
        LIGHT_GRAY = 7,
        DARK_GRAY = 8,
        LIGHT_BLUE = 9,
        LIGHT_GREEN = 10,
        LIGHT_CYAN = 11,
        LIGHT_RED = 12,
        LIGHT_MAGENTA = 13,
        YELLOW = 14,
        WHITE = 15
    };

    /**
     * Setting console color
     * @param background Background color
     * @param text Text color
     */
    void setConsoleColor(ConsoleColor background, ConsoleColor text) {
#if defined(__WIN32)
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, (WORD) ((background << 4) | text));
#else
#error Platform not supported!
#endif
    }

    /**
    * Function for testing GS_Lexer class<br>
    * Note: Do not use in final version!
    * @param type Enum input _type
    * @return String name of enum
    */
    std::string enumToString(GSLanguageCompiler::TokenType type) {
        switch (type) {
            case GSLanguageCompiler::TokenType::WORD:
                return "WORD";
            case GSLanguageCompiler::TokenType::TYPE_STRING:
                return "TYPE_STRING";
            case GSLanguageCompiler::TokenType::TYPE_NUMBER:
                return "TYPE_NUMBER";
            case GSLanguageCompiler::TokenType::KEYWORD_VAR:
                return "KEYWORD_VAR";
            case GSLanguageCompiler::TokenType::KEYWORD_IF:
                return "KEYWORD_IF";
            case GSLanguageCompiler::TokenType::SYMBOL_LEFT_PARENTHESES:
                return "SYMBOL_LEFT_PARENTHESES";
            case GSLanguageCompiler::TokenType::SYMBOL_RIGHT_PARENTHESES:
                return "SYMBOL_RIGHT_PARENTHESES";
            case GSLanguageCompiler::TokenType::SYMBOL_DOT:
                return "SYMBOL_DOT";
            case GSLanguageCompiler::TokenType::SYMBOL_COLON:
                return "SYMBOL_COLON";
            case GSLanguageCompiler::TokenType::SYMBOL_PLUS:
                return "SYMBOL_PLUS";
            case GSLanguageCompiler::TokenType::SYMBOL_MINUS:
                return "SYMBOL_MINUS";
            case GSLanguageCompiler::TokenType::SYMBOL_STAR:
                return "SYMBOL_STAR";
            case GSLanguageCompiler::TokenType::SYMBOL_SLASH:
                return "SYMBOL_SLASH";
            case GSLanguageCompiler::TokenType::SYMBOL_EQ:
                return "SYMBOL_EQ";
            case GSLanguageCompiler::TokenType::NEW_LINE:
                return "NEW_LINE";
            case GSLanguageCompiler::TokenType::END_OF_FILE:
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
    void printTokenTypes(GSLanguageCompiler::GSTokenArray &tokens) {
        setConsoleColor(BLACK, RED);
        std::cerr << "----------LEXER OUT START----------" << std::endl;
        for (auto &token : tokens) {
            std::cerr << enumToString(token.getType()) << std::endl;
        }
        std::cerr << "----------LEXER OUT END----------" << std::endl;
        setConsoleColor(BLACK, LIGHT_GRAY);
    }

}

#endif //GSLANGUAGE_TESTS_H
