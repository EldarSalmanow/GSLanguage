#ifndef GSLANGUAGE_GS_TOKEN_H
#define GSLANGUAGE_GS_TOKEN_H

#include <vector>
#include <memory>

#include "GS_Keywords.h"
#include "GS_Position.h"

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
//        GS_Token(TokenType type);

        /**
         *
         * @param type
         * @param position
         */
        GS_Token(TokenType type, GS_Position position);

        /**
         * Constructor for GS_Token
         * @param type Type of token
         * @param value String or number value
         */
//        GS_Token(TokenType type, std::string &word);

        /**
         *
         * @param type
         * @param word
         * @param position
         */
        GS_Token(TokenType type, std::string &word, GS_Position position);

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

        /**
         *
         * @return
         */
        GS_Position getPosition();

    private:

        /**
         * Type of token
         */
        TokenType _type;

        /**
         * String value or name
         */
        std::string _value;

        /**
         *
         */
        GS_Position _position;
    };

    typedef std::shared_ptr<GS_Token> GSTokenPointer;

    typedef std::vector<GS_Token> GSTokenArray;

}

#endif //GSLANGUAGE_GS_TOKEN_H
