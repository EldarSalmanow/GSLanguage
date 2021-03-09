#ifndef GSLANGUAGE_GS_TOKEN_H
#define GSLANGUAGE_GS_TOKEN_H

#include <string>
#include <map>
#include <memory>

#include "GS_Keywords.h"

namespace GSLanguageCompiler {

    /**
     * Token class
     */
    class GS_Token {
    public:

        GS_Token() = default;

        /**
         * Constructor for GS_Token
         * @param type Type of token
         */
        GS_Token(TokenType type) {
            this->_type = type;
        }

        /**
         * Constructor for GS_Token
         * @param type Type of token
         * @param value String or number _value
         */
        GS_Token(TokenType type, std::string &word) {
            this->_type = type;
            this->_value = word;
        }

    public:

        /**
         * Getter for _type
         * @return Token type
         */
        TokenType getType() {
            return this->_type;
        }

        /**
         * Getter for _value
         * @return Token value
         */
        std::string getValue() {
            return this->_value;
        }

    private:

        /**
         * Type of token
         */
        TokenType _type;

        /**
         * String _value or name
         */
        std::string _value;
    };

    typedef std::shared_ptr<GS_Token> GSTokenPointer;

    typedef std::vector<GS_Token> GSTokenArray;

}

#endif //GSLANGUAGE_GS_TOKEN_H
