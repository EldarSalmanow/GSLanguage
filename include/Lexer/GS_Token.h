#ifndef GSLANGUAGE_GS_TOKEN_H
#define GSLANGUAGE_GS_TOKEN_H

#include <GSCrossPlatform/CrossPlatform.h>

#include <Lexer/GS_Keywords.h>

namespace GSLanguageCompiler::Lexer {

    /**
     * Class for containing token information about location
     */
    class GS_TokenLocation {
    public:

        /**
         * Constructor for token location
         * @param sourceName Source name
         * @param line Line
         * @param column Column
         * @return Token location
         */
        GS_TokenLocation(UString sourceName, U64 line, U64 column);

    public:

        /**
         * Creating token location
         * @param sourceName Source name
         * @param line Line
         * @param column Column
         * @return Token location
         */
        static GS_TokenLocation Create(UString sourceName, U64 line, U64 column);

        /**
         * Creating token location
         * @param line Line
         * @param column Column
         * @return Token location
         */
        static GS_TokenLocation Create(U64 line, U64 column);

        /**
         * Creating token location
         * @return Token location
         */
        static GS_TokenLocation Create();

    public:

        /**
         * Getter for source name
         * @return Source name
         */
        UString GetSourceName() const;

        /**
         * Getter for line
         * @return Line
         */
        U64 GetLine() const;

        /**
         * Getter for column
         * @return Column
         */
        U64 GetColumn() const;

    private:

        /**
         * Source name
         */
        UString _sourceName;

        /**
         * Line
         */
        U64 _line;

        /**
         * Column
         */
        U64 _column;
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
    using GSTokenArray = Vector<GS_Token>;

    /**
     * Token ptr array iterator type
     */
    using GSTokenArrayIterator = GSTokenArray::iterator;

}

#endif //GSLANGUAGE_GS_TOKEN_H
