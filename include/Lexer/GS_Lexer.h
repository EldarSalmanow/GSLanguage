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
