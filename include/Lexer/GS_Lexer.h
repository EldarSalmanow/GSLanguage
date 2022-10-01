#ifndef GSLANGUAGE_GS_LEXER_H
#define GSLANGUAGE_GS_LEXER_H

#include <Driver/GS_CompilationUnit.h>

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

        /**
         * Tokenizing code from source
         * @param compilationUnit Compilation unit
         * @return Tokens
         */
        GSTokenArray Tokenize(LRef<Driver::GS_CompilationUnit> compilationUnit);

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
         * Content
         */
        UString _content;

        /**
         * Content iterator
         */
        UString::Iterator _contentIterator;

        /**
         * Current source hash
         */
        U64 _sourceHash;

        /**
         * Current position in source
         */
        I64 _currentPosition;
    };

}

#endif //GSLANGUAGE_GS_LEXER_H
