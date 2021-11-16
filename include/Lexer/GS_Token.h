#ifndef GSLANGUAGE_GS_TOKEN_H
#define GSLANGUAGE_GS_TOKEN_H

#include <Lexer/GS_Keywords.h>

namespace GSLanguageCompiler::Lexer {

    /**
     * Class for issuing information about the token
     */
    class GS_Token {
    public:

        /**
         * Default constructor for GS_Token
         */
        GS_Token();

        /**
         *
         * @param type
         */
        explicit GS_Token(TokenType type);

        /**
         *
         * @param type
         * @param value
         */
        GS_Token(TokenType type, String value);

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
        String getValue();

    private:

        /**
         * Type of token
         */
        TokenType _type;

        /**
         * String value or name
         */
        String _value;
    };

    /**
     * Token array type
     */
    using GSTokenArray = Vector<GS_Token>;

    /**
     * Token array iterator type
     */
    using GSTokenArrayIterator = Vector<GS_Token>::iterator;

}

#endif //GSLANGUAGE_GS_TOKEN_H
