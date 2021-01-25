#include "../../../include/Compiler/Lexer/GS_Lexer.h"

namespace GSLanguageCompiler {

    std::vector<GS_Token> GS_Lexer::tokenize() {
        this->codeIterator = this->input.begin();
        this->line = 1;

        while (this->codeIterator != this->input.end()) {
            this->lineIterator = this->codeIterator[0].begin();
            analyzeLine();
            ++this->codeIterator;
            ++this->line;
        }

        this->tokens.emplace_back(GS_Token(END_OF_FILE));

        return this->tokens;
    }

    void GS_Lexer::analyzeLine() {
        while (this->lineIterator != this->codeIterator[0].end()) {
            this->symbol = this->lineIterator[0];
            this->column = 1;

            // 0..9 number
            if (this->isSupportedCharacter(NUMBER_SIMPLE)) {
                tokenizeNumber();
                continue;
            }

            // A..Z a..z english alphabet
            else if (this->isSupportedCharacter(ALPHABET_ENGLISH)) {
                this->tokenizeWord();
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

        this->tokens.emplace_back(GS_Token(NEW_LINE));
    }

//---------------------------------------------------------

    void GS_Lexer::tokenizeNumber() {
        std::string number;

        while (isSupportedCharacter(NUMBER_SIMPLE)) {
            number += this->symbol;
            ++lineIterator;
            this->symbol = lineIterator[0];
            ++column;
        }

        tokens.emplace_back(GS_Token(TYPE_NUMBER, std::stoi(number)));
    }

    void GS_Lexer::tokenizeWord() {
        std::string word;

        while (this->isSupportedCharacter(ALPHABET_ENGLISH)) {
            word += this->symbol;
            ++this->lineIterator;
            this->symbol = this->lineIterator[0];
            ++this->column;
        }

        if (isReservedWord(word)) {
            this->tokens.emplace_back(GS_Token(analyzeReservedWord(word)));
            return;
        }

        this->tokens.emplace_back(WORD, word);

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
            case NUMBER_SIMPLE:
                regexps = {
                        _numberExpression
                };
                break;
            case ALPHABET_ENGLISH:
                regexps = {
                        _wordEnglishLowerCaseExpression,
                        _wordEnglishUpperCaseExpression
                };
                break;
        }

        for (auto & regex : regexps) {
            if (std::regex_match(this->symbol, match, regex)) {
                return true;
            }
        }
        return false;
    }
}