#ifndef GSLANGUAGE_GS_TOKEN_H
#define GSLANGUAGE_GS_TOKEN_H

#include <vector>
#include <memory>

#include "GS_Keywords.h"

namespace GSLanguageCompiler::Lexer {

    /**
     * Class for issuing information about the token
     */
    class GS_Token {
    public:

        /**
         * Default constructor for GS_Token
         */
        GS_Token() = default;

        /**
         * Constructor for GS_Token
         * @param type Type of token
         */
        GS_Token(TokenType type);

        /**
         * Constructor for GS_Token
         * @param type Type of token
         * @param value String or number value
         */
        GS_Token(TokenType type, std::string &word);

    public:

        /**
         * Getter for type
         * @return Token type
         */
        TokenType getType();

        /**
         * Getter for value
         * @return Token value
         */
        std::string getValue();

    private:

        /**
         * Type of token
         */
        TokenType _type;

        /**
         * String value or name
         */
        std::string _value;
    };

    typedef std::shared_ptr<GS_Token> GSTokenPointer;

    typedef std::vector<GS_Token> GSTokenArray;

}

#endif //GSLANGUAGE_GS_TOKEN_H
