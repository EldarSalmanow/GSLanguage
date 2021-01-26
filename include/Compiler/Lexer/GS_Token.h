#ifndef GSLANGUAGE_GS_TOKEN_H
#define GSLANGUAGE_GS_TOKEN_H

#include <string>
#include <map>

#include "GS_Keywords.h"

namespace GSLanguageCompiler {

    /**
     * Token class
     */
    class GS_Token {
    public:

        /**
         * Constructor for GS_Token
         * @param type Type of token
         */
        GS_Token(TokenType type) {
            this->type = type;
        }

        /**
         * Constructor for GS_Token
         * @param type Type of token
         * @param number Integer value
         */
        GS_Token(TokenType type, int number) {
            this->type = type;
            this->number = number;
        }

        /**
         * Constructor for GS_Token
         * @param type Type of token
         * @param word String value or name
         */
        GS_Token(TokenType type, std::string &word) {
            this->type = type;
            this->word = word;
        }

    public:

        /**
         * Getter for TokenType
         * @return Token type
         */
        TokenType getType() {
            return this->type;
        }

        int getNumber() {
            return this->number;
        }

        std::string getWord() {
            return this->word;
        }

    private:

        /**
         * Type of token
         */
        TokenType type;

        /**
         * Integer value
         */
        int number;

        /**
         * String value or name
         */
        std::string word;
    };

}

#endif //GSLANGUAGE_GS_TOKEN_H
