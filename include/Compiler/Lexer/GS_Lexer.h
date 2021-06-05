#ifndef GSLANGUAGE_GS_LEXER_H
#define GSLANGUAGE_GS_LEXER_H

#include <vector>

#include <Compiler/Lexer/GS_Token.h>
#include <Compiler/Lexer/GS_Regex.h>

#include <Exceptions/GS_LexerException.h>

namespace GSLanguageCompiler::Lexer {

    typedef std::vector<GSString> GSText;

    /**
     * Class for analyzing source code
     */
    class GS_Lexer {
    public:

        /**
         * Constructor for GS_Lexer
         * @param input Lines of code from _input file
         */
        GS_Lexer(GSText &input);

    public:

        /**
         * Function for tokenize _input code
         * @return Tokens for parser analyze
         */
        GSTokenArray tokenize();

    private:

        /**
         * Analysis of each line in turn
         */
        GSVoid _analyzeLine();

        /**
         * Tokenizing number
         */
        GSVoid _tokenizeNumber();

        /**
         * Tokenizing word
         */
        GSVoid _tokenizeWord();

        /**
         * Tokenizing string
         */
        GSVoid _tokenizeString();

        /**
         * Analyzing reserved word or symbol
         * @param word Input word for analyzing
         * @return Type of reserved word or symbol
         */
        inline TokenType _analyzeReservedWord(GSString &word);

        /**
         * Search for a string in reserved words and symbols
         * @param word Input string to analyze
         * @return Is reserved word or symbol
         */
        inline GSBool _isReservedWord(GSString &word);

        /**
         * Function to check if a character is supported by the compiler
         * @param character Symbol to check
         * @param type Regular expression type
         * @return Is supported character
         */
        GSBool _isValidRegexForSymbol(RegexType type);

        /**
         * Setting start position of token value
         */
        inline GSVoid _setStartPositionOfToken();

        /**
         * Adding token
         * @param type Token type
         */
        inline GSVoid _addToken(TokenType type);

        /**
         * Adding token with value
         * @param type Token type
         * @param value Token value
         */
        inline GSVoid _addToken(TokenType type, GSString value);

        /**
         * Updating line iterator to next symbol in line
         */
        inline GSVoid _nextSymbol();

        /**
         * Updating code iterator to next line in source
         */
        inline GSVoid _nextLine();

        /**
         * Getting current symbol in line iterator
         * @return Current symbol in line iterator
         */
        inline GSChar _currentSymbol();

        /**
         * Is end of line in line iterator
         * @return Is end of line
         */
        inline GSBool _isEndOfLine();

        /**
         * Is end of source in code iterator
         * @return Is end of source
         */
        inline GSBool _isEndOfSource();

    private:

        /**
         * Input code from reader
         */
        GSText _input;

        /**
         * Tokens before lexer analyzing
         */
        GSTokenArray _tokens;

        /**
         * Current position in lexer analyzing
         */
        GSULongLong _line, _column;

        /**
         * Start token value position
         */
        GSULongLong _startLine, _startColumn;

        /**
         * An iterator to read code from a file
         */
        GSText::iterator _codeIterator;

        /**
         * Iterator for reading a line of code
         */
        GSString::iterator _lineIterator;

        /**
         * Current symbol
         */
        GSString _symbol;
    };

    typedef std::shared_ptr<GS_Lexer> GSLexerPointer;

}

#endif //GSLANGUAGE_GS_LEXER_H
