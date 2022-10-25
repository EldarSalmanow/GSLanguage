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
         * @param context Context
         */
        explicit GS_Lexer(Driver::GSContextPtr context);

    public:

        /**
         * Creating lexer
         * @param context Context
         * @return Lexer
         */
        static GS_Lexer Create(Driver::GSContextPtr context);

    public:

        // TODO: remove or update
        static GSTokenArray Run(Driver::GSContextPtr context, IO::GSSourcePtr source);

    public:

        /**
         * Tokenizing code from source
         * @param source Source
         * @return Tokens
         */
        GSTokenArray Tokenize(IO::GSSourcePtr source);

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

    public:

        /**
         * Creating text message
         * @param message Message
         * @param messageLevel Message level
         * @return
         */
        Void Message(UString message, IO::MessageLevel messageLevel);

        /**
         * Creating located text message
         * @param message Message
         * @param messageLevel Message level
         * @param messageLocation Message location
         * @return
         */
        Void LocatedMessage(UString message, IO::MessageLevel messageLevel, IO::GS_SourceLocation messageLocation);

    private:

        /**
         * Context
         */
        Driver::GSContextPtr _context;

        /**
         * Messages
         */
        IO::GSMessagePtrArray _messages;

        /**
         * Source
         */
        IO::GSSourcePtr _source;

        /**
         * Content
         */
        UString _content;

        /**
         * Content iterator
         */
        UString::Iterator _contentIterator;

        /**
         * Current position in source
         */
        I64 _currentPosition;
    };

}

#endif //GSLANGUAGE_GS_LEXER_H
