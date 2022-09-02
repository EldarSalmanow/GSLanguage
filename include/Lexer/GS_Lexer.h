#ifndef GSLANGUAGE_GS_LEXER_H
#define GSLANGUAGE_GS_LEXER_H

#include <Driver/GS_Context.h>

#include <Lexer/GS_Token.h>

namespace GSLanguageCompiler::Lexer {

    /**
     * Class for tokenizing source code
     */
    class GS_Lexer {
    public:

        /**
         * Constructor for lexer
         * @param content Content
         * @param context Context
         */
        GS_Lexer(UString content, Driver::GSContextPtr context);

    public:

        /**
         * Creating lexer
         * @param content Content
         * @param context Context
         * @return Lexer
         */
        static GS_Lexer Create(UString content, Driver::GSContextPtr context);

    public:

        /**
         * Tokenizing all source code
         * @return Tokens
         */
        GSTokenArray Tokenize();

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
         * Context
         */
        Driver::GSContextPtr _context;

        /**
         * Content
         */
        UString _content;

        /**
         * Content iterator
         */
        UString::Iterator _contentIterator;
    };

}

#endif //GSLANGUAGE_GS_LEXER_H
