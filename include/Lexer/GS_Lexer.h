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
         * Getting current source location
         * @return Current source location
         */
        IO::GS_SourceLocation CurrentLocation() const;

    private:

        /*
         *
         * GS_Lexer PRIVATE FIELDS
         *
         */

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
