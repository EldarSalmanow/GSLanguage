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
         * @param locationRange Source location range
         */
        GS_Token(TokenType type,
                 UString value,
                 IO::GSByteSourceRange locationRange);

    public:

        /**
         * Create token
         * @param type Type
         * @param value Value
         * @param locationRange Source location range
         * @return Token
         */
        static GS_Token Create(TokenType type,
                               UString value,
                               IO::GSByteSourceRange locationRange);

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
         * @param locationRange Source location range
         * @return Token
         */
        static GS_Token Create(TokenType type,
                               IO::GSByteSourceRange locationRange);

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
        ConstLRef<UString> GetValue() const;

        /**
         * Getter for source location range
         * @return Source location range
         */
        IO::GSByteSourceRange GetLocationRange() const;

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
         * Token source location range
         */
        IO::GSByteSourceRange _locationRange;
    };

    /**
     * Token ptr array type
     */
    using GSTokenArray = std::vector<GS_Token>;

    /**
     * Class for containing tokens
     */
    class GS_TokensBuffer {
    public:

        /**
         * Iterator type
         */
        using Iterator = GSTokenArray::iterator;

        /**
         * Const iterator type
         */
        using ConstIterator = GSTokenArray::const_iterator;

    public:

        /**
         * Constructor for tokens buffer
         * @param tokens Tokens
         */
        explicit GS_TokensBuffer(GSTokenArray tokens);

    public:

        /**
         * Creating tokens buffer
         * @param tokens Tokens
         * @return Tokens buffer
         */
        static GS_TokensBuffer Create(GSTokenArray tokens);

    public:

        /**
         * Getting begin tokens buffer iterator
         * @return Begin tokens buffer iterator
         */
        Iterator begin();

        /**
         * Getting end tokens buffer iterator
         * @return End tokens buffer iterator
         */
        Iterator end();

        /**
         * Getting begin tokens buffer const iterator
         * @return Begin tokens buffer const iterator
         */
        ConstIterator begin() const;

        /**
         * Getting end tokens buffer const iterator
         * @return End tokens buffer const iterator
         */
        ConstIterator end() const;

        /**
         * Getting begin tokens buffer const iterator
         * @return Begin tokens buffer const iterator
         */
        ConstIterator cbegin() const;

        /**
         * Getting end tokens buffer const iterator
         * @return End tokens buffer const iterator
         */
        ConstIterator cend() const;

    public:

        /**
         * Getter for tokens
         * @return Tokens
         */
        ConstLRef<GSTokenArray> GetTokens() const;

    private:

        /**
         * Tokens
         */
        GSTokenArray _tokens;
    };

}

#endif //GSLANGUAGE_GS_TOKEN_H
