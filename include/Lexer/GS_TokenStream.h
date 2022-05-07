#ifndef GSLANGUAGE_GS_TOKENSTREAM_H
#define GSLANGUAGE_GS_TOKENSTREAM_H

#include <Lexer/GS_Lexer.h>

namespace GSLanguageCompiler::Lexer {

    /**
     * Stream class for tokens
     */
    class GS_TokenStream {
    public:

        /**
         * Constructor for token stream
         * @param tokens Tokens
         */
        explicit GS_TokenStream(GSTokenArray tokens);

    public:

        /**
         * Creating token stream
         * @param tokens Tokens
         * @return Token stream
         */
        static GS_TokenStream Create(GSTokenArray tokens);

        /**
         * Creating token stream
         * @param lexer Lexer
         * @return Token stream
         */
        static GS_TokenStream Create(LRef<GS_Lexer> lexer);

    public:

        /**
         * Getting current token
         * @return Current token
         */
        GS_Token CurrentToken();

        /**
         * Setting cursor to next token in stream
         * @return
         */
        Void NextToken();

        /**
         * Setting cursor to prev token in stream
         * @return
         */
        Void PrevToken();

    private:

        /**
         * Token array
         */
        GSTokenArray _tokens;

        /**
         * Token array iterator
         */
        GSTokenArrayIterator _tokenIterator;
    };

}

#endif //GSLANGUAGE_GS_TOKENSTREAM_H
