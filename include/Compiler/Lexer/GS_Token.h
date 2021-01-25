#ifndef GSLANGUAGE_GS_TOKEN_H
#define GSLANGUAGE_GS_TOKEN_H

#include <string>
#include <map>

#include "GS_Keywords.h"

namespace GSLanguageCompiler {

    class GS_Token {
    public:
        GS_Token(TokenType type) {
            this->type = type;
        }

        GS_Token(TokenType type, int number) {
            this->type = type;
            this->number = number;
        }

        GS_Token(TokenType type, std::string &word) {
            this->type = type;
            this->word = word;
        }

        TokenType getType() {
            return this->type;
        }

    private:
        TokenType type;
        int number;
        std::string word;
    };
}

#endif //GSLANGUAGE_GS_TOKEN_H
