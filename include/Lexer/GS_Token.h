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
    class GS_TokenBuffer {
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
         * Constructor for token buffer
         * @param tokens Tokens
         */
        explicit GS_TokenBuffer(GSTokenArray tokens);

    public:

        /**
         * Creating token buffer
         * @param tokens Tokens
         * @return Token buffer
         */
        static GS_TokenBuffer Create(GSTokenArray tokens);

    public:

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
