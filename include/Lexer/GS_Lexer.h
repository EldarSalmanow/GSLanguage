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

        /**
         * Constructor for lexer
         * @param session Session
         * @param source Source
         */
        GS_Lexer(LRef<Driver::GS_Session> session,
                 ConstLRef<IO::GS_Source> source);

    public:

        /**
         * Creating lexer
         * @param session Session
         * @param source Source
         * @return Lexer
         */
        static GS_Lexer Create(LRef<Driver::GS_Session> session,
                               ConstLRef<IO::GS_Source> source);

    public:

        /**
         * Creating lexer and tokenizing source
         * @param session Session
         * @param source Source
         * @return Tokens
         */
        static GS_TokensBuffer Run(LRef<Driver::GS_Session> session,
                                   ConstLRef<IO::GS_Source> source);

    public:

        /**
         * Tokenizing code from source
         * @return Tokens
         */
        GS_TokensBuffer Tokenize();

    private:

        /**
         * Tokenizing one token
         * @return Token
         */
        GS_Token GetToken();

    private:

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
         * Creating text message
         * @param message Message
         * @param messageLevel Message level
         * @return
         */
//        Void Message(UString message, IO::MessageLevel messageLevel);

        /**
         * Creating located text message
         * @param message Message
         * @param messageLevel Message level
         * @param messageLocation Message location
         * @return
         */
//        Void LocatedMessage(UString message, IO::MessageLevel messageLevel, IO::GS_SourceLocation messageLocation);

    private:

        /**
         * Session
         */
        LRef<Driver::GS_Session> _session;

        /**
         * Messages
         */
//        IO::GSMessagePtrArray _messages;

        /**
         * Source
         */
        ConstLRef<IO::GS_Source> _source;

        /**
         * Source buffer iterator
         */
        IO::GS_Source::ConstIterator _sourceIterator;

        /**
         * Current position in source
         */
        I64 _currentPosition;
    };

}

#endif //GSLANGUAGE_GS_LEXER_H
