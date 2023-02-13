#ifndef GSLANGUAGE_GS_LEXER_H
#define GSLANGUAGE_GS_LEXER_H

#include <Driver/Driver.h>

#include <Lexer/GS_Token.h>

namespace GSLanguageCompiler::Lexer {

    /**
     * Class for tokenizing source code
     * @todo Update all
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
         * Setting cursor to next symbol in content
         * @return
         */
        Void NextSymbol();

        /**
         * Setting cursor to previous symbol in content
         * @return
         */
        Void PrevSymbol();

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
