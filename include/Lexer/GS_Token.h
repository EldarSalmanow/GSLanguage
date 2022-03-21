#ifndef GSLANGUAGE_GS_TOKEN_H
#define GSLANGUAGE_GS_TOKEN_H

#include <GSCrossPlatform/CrossPlatform.h>

#include <Lexer/GS_Keywords.h>

namespace GSLanguageCompiler::Lexer {

    /**
     * Class for representation token in lexer
     */
    class GS_Token {
    public:

        /**
         * Constructor for token
         * @param type Type
         * @param value Value
         */
        GS_Token(TokenType type, UString value);

    public:

        /**
         * Creating token
         * @param type Type
         * @param value Value
         * @return Token
         */
        static GS_Token Create(TokenType type, UString value);

        /**
         * Creating token
         * @param type Type
         * @return Token
         */
        static GS_Token Create(TokenType type);

    public:

        /**
         * Getter for type
         * @return Type
         */
        TokenType GetType() const;

        /**
         * Getter for value
         * @return Value
         */
        UString GetValue() const;

    private:

        /**
         * Token type
         */
        TokenType _type;

        /**
         * Token value
         */
        UString _value;
    };

    /**
     * Token ptr array type
     */
    using GSTokenArray = Vector<GS_Token>;

    /**
     * Token ptr array iterator type
     */
    using GSTokenArrayIterator = GSTokenArray::iterator;

}

#endif //GSLANGUAGE_GS_TOKEN_H
