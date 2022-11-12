#ifndef GSLANGUAGE_GS_TOKEN_H
#define GSLANGUAGE_GS_TOKEN_H

#include <IO/GS_Source.h>

namespace GSLanguageCompiler::Lexer {

    /**
     * Type of token
     */
    enum class TokenType {
        #include <Lexer/GS_TokenTypes.def>
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
        GS_Token(TokenType type,
                 UString value,
                 IO::GS_SourceLocation location);

    public:

        /**
         * Create token
         * @param type Type
         * @param value Value
         * @param location Location
         * @return Token
         */
        static GS_Token Create(TokenType type,
                               UString value,
                               IO::GS_SourceLocation location);

        /**
         * Creating token
         * @param type Type
         * @param value Value
         * @return Token
         */
        static GS_Token Create(TokenType type,
                               UString value);

        /**
         * Creating token
         * @param type Type
         * @param location Location
         * @return Token
         */
        static GS_Token Create(TokenType type,
                               IO::GS_SourceLocation location);

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
        IO::GS_SourceLocation GetLocation() const;

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
        IO::GS_SourceLocation _location;
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
