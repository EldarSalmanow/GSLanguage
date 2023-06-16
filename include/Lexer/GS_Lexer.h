#ifndef GSLANGUAGE_GS_LEXER_H
#define GSLANGUAGE_GS_LEXER_H

#include <Driver/GS_Session.h>

#include <Lexer/GS_Token.h>

namespace GSLanguageCompiler::Lexer {

    /**
     * Class for tokenizing source code
     */
    class GS_Lexer {
    public:

        /*
         *
         * GS_Lexer PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for lexer
         * @param session Session
         * @param source Source
         */
        GS_Lexer(LRef<Driver::GS_Session> session,
                 ConstLRef<IO::GS_Source> source);

    public:

        /*
         *
         * GS_Lexer PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating lexer
         * @param session Session
         * @param source Source
         * @return Lexer
         */
        static GS_Lexer Create(LRef<Driver::GS_Session> session,
                               ConstLRef<IO::GS_Source> source);

    public:

        /*
         *
         * GS_Lexer PUBLIC STATIC METHODS
         *
         */

        /**
         * Creating lexer and tokenizing source
         * @param session Session
         * @param source Source
         * @return Token buffer
         */
        static GS_TokenBuffer Run(LRef<Driver::GS_Session> session,
                                  ConstLRef<IO::GS_Source> source);

    public:

        /*
         *
         * GS_Lexer PUBLIC METHODS
         *
         */

        /**
         * Tokenizing code from source
         * @return Token buffer
         */
        GS_TokenBuffer Tokenize();

    private:

        /*
         *
         * GS_Lexer PRIVATE METHODS
         *
         */

        /**
         * Tokenizing one token
         * @return Token
         */
        GS_Token GetToken();

        /**
         * Tokenizing whitespace
         * @return Tokenized whitespace or error token
         */
        GS_Token TokenizeWhitespace();

        /**
         * Tokenizing word
         * @return Tokenized word or error token
         */
        GS_Token TokenizeWord();

        /**
         * Tokenizing reserved symbol
         * @return Tokenized reserved symbol or error token
         */
        GS_Token TokenizeReservedSymbol();

        /**
         * Tokenizing digit literal
         * @return Tokenized digit literal or error token
         */
        GS_Token TokenizeDigit();

        /**
         * Tokenizing symbol literal
         * @return Tokenized symbol literal or error token
         */
        GS_Token TokenizeSymbol();

        /**
         * Tokenizing string literal
         * @return Tokenized string literal or error token
         */
        GS_Token TokenizeString();

        /**
         * Getting current symbol from cursor
         * @return Current symbol value
         */
        USymbol CurrentSymbol();

        /**
         * Setting cursor to next symbol in source
         * @return Void return
         */
        Void NextSymbol();

        /**
         * Getting current byte source location
         * @return Current byte source location
         */
        IO::GS_ByteSourceLocation CurrentLocation() const;

    private:

        /**
         * Session
         */
        LRef<Driver::GS_Session> _session;

        /**
         * Message queue
         */
        IO::GS_MessageQueue _messageQueue;

        /**
         * Source
         */
        ConstLRef<IO::GS_Source> _source;

        /**
         * Source buffer iterator (source cursor)
         */
        IO::GS_Source::ConstIterator _sourceIterator;

        /**
         * Current position in source (cursor position)
         */
        I64 _currentPosition;
    };

}

#endif //GSLANGUAGE_GS_LEXER_H
