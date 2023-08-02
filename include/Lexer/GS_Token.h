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

        /*
         *
         * GS_Token PUBLIC CONSTRUCTORS
         *
         */

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

        /*
         *
         * GS_Token PUBLIC STATIC CREATE METHODS
         *
         */

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

        /*
         *
         * GS_Token PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for type
         * @return Type
         */
        TokenType GetType() const;

        /**
         * Getter for value
         * @return Value
         */
        ConstLRef<UString> GetValue() const;

        /**
         * Getter for location
         * @return Location
         */
        IO::GS_SourceLocation GetLocation() const;

    private:

        /*
         *
         * GS_Token PRIVATE FIELDS
         *
         */

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
     * Token array type
     */
    using GSTokenArray = std::vector<GS_Token>;

    /**
     * Class for containing tokens
     */
    class GS_TokenBuffer {
    public:

        /*
         *
         * GS_TokenBuffer PUBLIC TYPES
         *
         */

        /**
         * Iterator type
         */
        using Iterator = GSTokenArray::iterator;

        /**
         * Const iterator type
         */
        using ConstIterator = GSTokenArray::const_iterator;

    public:

        /*
         *
         * GS_TokenBuffer PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for token buffer
         * @param tokens Tokens
         */
        explicit GS_TokenBuffer(GSTokenArray tokens);

    public:

        /*
         *
         * GS_TokenBuffer PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating token buffer
         * @param tokens Tokens
         * @return Token buffer
         */
        static GS_TokenBuffer Create(GSTokenArray tokens);

    public:

        /*
         *
         * GS_TokenBuffer PUBLIC ITERATOR METHODS
         *
         */

        /**
         * Getting begin token buffer iterator
         * @return Begin token buffer iterator
         */
        Iterator begin();

        /**
         * Getting end token buffer iterator
         * @return End token buffer iterator
         */
        Iterator end();

        /**
         * Getting begin token buffer const iterator
         * @return Begin token buffer const iterator
         */
        ConstIterator begin() const;

        /**
         * Getting end token buffer const iterator
         * @return End token buffer const iterator
         */
        ConstIterator end() const;

        /**
         * Getting begin token buffer const iterator
         * @return Begin token buffer const iterator
         */
        ConstIterator cbegin() const;

        /**
         * Getting end token buffer const iterator
         * @return End token buffer const iterator
         */
        ConstIterator cend() const;

    public:

        /*
         *
         * GS_TokenBuffer PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for tokens
         * @return Tokens
         */
        ConstLRef<GSTokenArray> GetTokens() const;

    private:

        /*
         *
         * GS_TokenBuffer PRIVATE FIELDS
         *
         */

        /**
         * Tokens
         */
        GSTokenArray _tokens;
    };

    /**
     * Class for smart creating tokens
     */
    class GS_TokenBuilder {
    public:

        /*
         *
         * GS_TokenBuilder PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for token builder
         * @param tokenType Token type
         * @param tokenValue Token value
         * @param tokenLocation Token location
         */
        GS_TokenBuilder(TokenType tokenType,
                        UString tokenValue,
                        IO::GS_SourceLocation tokenLocation);

    public:

        /*
         *
         * GS_TokenBuilder PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating token builder
         * @param tokenType Token type
         * @param tokenValue Token value
         * @param tokenLocation Token location
         * @return Token builder
         */
        static GS_TokenBuilder Create(TokenType tokenType,
                                      UString tokenValue,
                                      IO::GS_SourceLocation tokenLocation);

        /**
         * Creating token builder
         * @param tokenType Token type
         * @param tokenValue Token value
         * @return Token builder
         */
        static GS_TokenBuilder Create(TokenType tokenType,
                                      UString tokenValue);

        /**
         * Creating token builder
         * @param tokenType Token type
         * @param tokenLocation Token location
         * @return Token builder
         */
        static GS_TokenBuilder Create(TokenType tokenType,
                                      IO::GS_SourceLocation tokenLocation);

        /**
         * Creating token builder
         * @param tokenType Token type
         * @return Token builder
         */
        static GS_TokenBuilder Create(TokenType tokenType);

        /**
         * Creating token builder
         * @return Token builder
         */
        static GS_TokenBuilder Create();

    public:

        /*
         *
         * GS_TokenBuilder PUBLIC METHODS
         *
         */

        /**
         * Setting token type in token
         * @param tokenType Token type
         * @return Token builder
         */
        LRef<GS_TokenBuilder> Type(TokenType tokenType);

        /**
         * Setting token value in token
         * @param tokenValue Token value
         * @return Token builder
         */
        LRef<GS_TokenBuilder> Value(UString tokenValue);

        /**
         * Setting token location in token
         * @param tokenLocation Token location
         * @return Token builder
         */
        LRef<GS_TokenBuilder> Location(IO::GS_SourceLocation tokenLocation);

        /**
         * Creating token
         * @return Token
         */
        GS_Token Token();

    public:

        /*
         *
         * GS_TokenBuilder PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for token type
         * @return Token type
         */
        TokenType GetTokenType() const;

        /**
         * Getter for token value
         * @return Token value
         */
        ConstLRef<UString> GetTokenValue() const;

        /**
         * Getter for token location
         * @return Token location
         */
        IO::GS_SourceLocation GetTokenLocation() const;

    private:

        /*
         *
         * GS_TokenBuilder PRIVATE FIELDS
         *
         */

        /**
         * Token type
         */
        TokenType _tokenType;

        /**
         * Token value
         */
        UString _tokenValue;

        /**
         * Token location
         */
        IO::GS_SourceLocation _tokenLocation;
    };

}

#endif //GSLANGUAGE_GS_TOKEN_H
