#ifndef GSLANGUAGE_GS_LEXER_H
#define GSLANGUAGE_GS_LEXER_H

#include <Driver/Driver.h>

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
         * @todo Add source check (is source from this session)
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
         * @todo Lexing space symbol in token ?
         * @todo Update messages flushing
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
         * @todo Add detecting end of file or unknown symbol
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
         * Setting cursor to previous symbol in source
         * @return
         */
        Void PrevSymbol();

        /**
         * Setting cursor to next symbol in source
         * @return
         */
        Void NextSymbol();

        /**
         * Getting current byte source location
         * @return Current byte source location
         */
        IO::GS_ByteSourceLocation CurrentLocation() const;

        /**
         * Getting previous byte source location
         * @return Previous byte source location
         */
        IO::GS_ByteSourceLocation PrevLocation() const;

        /**
         * Getting next byte source location
         * @return Next byte source location
         */
        IO::GS_ByteSourceLocation NextLocation() const;

        /**
         * Getting byte source location with position
         * @param position Byte position
         * @return Byte source location with position
         */
        IO::GS_ByteSourceLocation Location(I64 position) const;

        /**
         * Getting invalid byte source location
         * @return Invalid byte source location
         */
        IO::GS_ByteSourceLocation Location() const;

    private:

        /**
         * Session
         */
        LRef<Driver::GS_Session> _session;

        /**
         * Messages
         */
        IO::GSMessageArray _messages;

        /**
         * Source
         */
        ConstLRef<IO::GS_Source> _source;

        /**
         * Source buffer iterator (cursor)
         */
        IO::GS_Source::ConstIterator _sourceIterator;

        /**
         * Current position in source (cursor position)
         */
        I64 _currentPosition;
    };

}

#endif //GSLANGUAGE_GS_LEXER_H
