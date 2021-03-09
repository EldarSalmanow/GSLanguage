#include "../../../include/Compiler/Lexer/GS_Lexer.h"

namespace GSLanguageCompiler {

    std::vector<GS_Token> GS_Lexer::tokenize() {
        // setting the iterator to the beginning of the text
        this->codeIterator = this->input.begin();
        this->line = 1;

        // text tokenization process
        while (this->codeIterator != this->input.end()) {
            this->lineIterator = this->codeIterator[0].begin();
            analyzeLine();
            ++this->codeIterator;
            ++this->line;
        }

        // putting a file end token
        this->tokens.emplace_back(GS_Token(TokenType::END_OF_FILE));

        return this->tokens;
    }

    void GS_Lexer::analyzeLine() {
        while (this->lineIterator != this->codeIterator[0].end()) {
            this->symbol = this->lineIterator[0];
            this->column = 1;

            // 0..9 number
            if (this->isSupportedCharacter(RegexType::NUMBER_SIMPLE)) {
//                GS_Tokenizer::tokenizeNumber();
                this->tokenizeNumber();
                continue;
            }

            // A..Z a..z english alphabet
            else if (this->isSupportedCharacter(RegexType::ALPHABET_ENGLISH)) {
//                GS_Tokenizer::tokenizeWord();
                this->tokenizeWord();
                continue;
            }

            else if (this->symbol == "\"") {
                this->tokenizeString();
                continue;
            }

            // special symbols
            else if (this->isReservedWord(symbol)) {
                this->tokens.emplace_back(GS_Token(analyzeReservedWord(this->symbol)));
                ++this->lineIterator;
                continue;
            }

            ++this->lineIterator;
        }

        this->tokens.emplace_back(GS_Token(TokenType::NEW_LINE));
    }

//---------------------------------------------------------

    void GS_Lexer::tokenizeNumber() {
        std::string number;

        while (isSupportedCharacter(RegexType::NUMBER_SIMPLE)) {
            number += this->symbol;
            ++lineIterator;
            this->symbol = lineIterator[0];
            ++column;
        }

        tokens.emplace_back(GS_Token(TokenType::LITERAL_NUMBER, number));
    }

    void GS_Lexer::tokenizeWord() {
        std::string word;

        while (this->isSupportedCharacter(RegexType::ALPHABET_ENGLISH)) {
            word += this->symbol;
            ++this->lineIterator;
            this->symbol = this->lineIterator[0];
            ++this->column;
        }

        if (isReservedWord(word)) {
            this->tokens.emplace_back(GS_Token(analyzeReservedWord(word)));
            return;
        }

        this->tokens.emplace_back(GS_Token(TokenType::WORD, word));

        return;
    }

    void GS_Lexer::tokenizeString() {
        std::string string;

        // scip "
        ++this->lineIterator;

        this->symbol = this->lineIterator[0];

        while (this->lineIterator != this->input[this->line - 1].end()) {
            this->symbol = this->lineIterator[0];

            if (symbol == "\"") {
                this->tokens.emplace_back(GS_Token(TokenType::LITERAL_STRING, string));
                break;
            }

            string += this->symbol;

            ++this->lineIterator;
        }

        return;
    }

//-----------------------------------------------------------------

    inline bool GS_Lexer::isReservedWord(std::string &word) {
        return reserved.find(word) != reserved.end();
    }

    inline TokenType GS_Lexer::analyzeReservedWord(std::string &word) {
        return reserved.at(word);
    }

    bool GS_Lexer::isSupportedCharacter(RegexType type) {
        std::smatch match;
        std::vector<std::regex> regexps;
        switch (type) {
            case RegexType::NUMBER_SIMPLE:
                regexps = {
                        _numberExpression
                };
                break;
            case RegexType::ALPHABET_ENGLISH:
                regexps = {
                        _wordEnglishLowerCaseExpression,
                        _wordEnglishUpperCaseExpression
                };
                break;
            case RegexType::UNSUPPORTED:
                return false;
        }

        for (auto & regex : regexps) {
            if (std::regex_match(this->symbol, match, regex)) {
                return true;
            }
        }
        return false;
    }

}