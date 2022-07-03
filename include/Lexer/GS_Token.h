#ifndef GSLANGUAGE_GS_TOKEN_H
#define GSLANGUAGE_GS_TOKEN_H

#include <vector>

#include <GSCrossPlatform/CrossPlatform.h>

#include <Lexer/GS_Keywords.h>

namespace GSLanguageCompiler::Lexer {

    // TODO update location system
    /**
     * Class for containing token information about location
     */
    class GS_TokenLocation {
    public:

        /**
         * Constructor for token location
         * @return Token location
         */
        GS_TokenLocation();

    public:

        /**
         * Creating token location
         * @return Token location
         */
        static GS_TokenLocation Create();
    };

    /**
     * Class for representation token in lexer
     */
    class GS_Token {
    public:

        /**
         * Constructor for token
         * @param type Type
         * @param value Value
         * @param location Location
         */
        GS_Token(TokenType type, UString value, GS_TokenLocation location);

    public:

        /**
         * Create token
         * @param type Type
         * @param value Value
         * @param location Location
         * @return Token
         */
        static GS_Token Create(TokenType type, UString value, GS_TokenLocation location);

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
         * @param location Location
         * @return Token
         */
        static GS_Token Create(TokenType type, GS_TokenLocation location);

        /**
         * Creating token
         * @param type Type
         * @return Token
         */
        static GS_Token Create(TokenType type);

        /**
         * Creating token
         * @return Token
         */
        static GS_Token Create();

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

        /**
         * Getter for location
         * @return Location
         */
        GS_TokenLocation GetLocation() const;

    private:

        /**
         * Token type
         */
        TokenType _type;

        /**
         * Token value
         */
        UString _value;

        /**
         * Token location
         */
        GS_TokenLocation _location;
    };

    /**
     * Token ptr array type
     */
    using GSTokenArray = std::vector<GS_Token>;

    /**
     * Token ptr array iterator type
     */
    using GSTokenArrayIterator = GSTokenArray::iterator;

}

#endif //GSLANGUAGE_GS_TOKEN_H
