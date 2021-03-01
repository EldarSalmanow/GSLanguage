#ifndef GSLANGUAGE_GS_LEXER_H
#define GSLANGUAGE_GS_LEXER_H

#include <vector>

#include "GS_Token.h"
#include "GS_Regex.h"
//#include "GS_Tokenizer.h"
#include "../../Exceptions/GS_LexerException.h"

namespace GSLanguageCompiler {

    /**
     * Class for analyzing source code
     */
    class GS_Lexer {
    public:

        /**
         * Constructor for GS_Lexer
         * @param input Lines of code from input file
         */
        GS_Lexer(std::vector<std::string> &input) {
            this->input = input;
        }

    public:

        /**
         * Function for tokenize input code
         * @return Tokens for parser analyze
         */
        std::vector<GS_Token> tokenize();

    private:

        /**
         * Analysis of each line in turn
         */
        void analyzeLine();

        /**
         * Tokenizing number
         */
        void tokenizeNumber();

        /**
         * Tokenizing word
         */
        void tokenizeWord();

        /**
         * Analyzing reserved word or symbol
         * @param word Input word for analyzing
         * @return Type of reserved word or symbol
         */
        inline TokenType analyzeReservedWord(std::string &word);

        /**
         * Search for a string in reserved words and symbols
         * @param basicString input string to analyze
         * @return Is reserved word or symbol
         */
        inline bool isReservedWord(std::string &basicString);

        /**
         * Function to check if a character is supported by the compiler
         * @param character Symbol to check
         * @param type Regular expression _type
         * @return Is supported character
         */
        bool isSupportedCharacter(RegexType type);

    private:

        /**
         * Input code from reader
         */
        std::vector<std::string> input;

        /**
         * Tokens before lexer analyzing
         */
        std::vector<GS_Token> tokens;

        /**
         * Position in lexer analyzing
         */
        int line, column;

        /**
         * An iterator to read code from a file
         */
        std::vector<std::string>::iterator codeIterator;

        /**
         * Iterator for reading a line of code
         */
        std::string::iterator lineIterator;

        /**
         * Current symbol
         */
        std::string symbol;
    };

    typedef std::shared_ptr<GS_Lexer> GSLexerPointer;

}

#endif //GSLANGUAGE_GS_LEXER_H
