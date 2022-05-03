#ifndef GSLANGUAGE_GS_LEXER_H
#define GSLANGUAGE_GS_LEXER_H

#include <Reader/Reader.h>

#include <Lexer/GS_Token.h>

namespace GSLanguageCompiler::Lexer {

    /**
     * Class for tokenizing source code
     */
    class GS_Lexer {
    public:

        /**
         * Constructor for lexer
         * @param textStream Text stream
         */
        explicit GS_Lexer(LRef<Reader::GS_TextStream> textStream);

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
         * Getting current symbol from stream
         * @return Current symbol
         */
        USymbol CurrentSymbol();

        /**
         * Setting cursor to next symbol in stream
         * @return
         */
        Void NextSymbol();

    private:

        /**
         * Text stream
         */
        Reader::GS_TextStream _stream;
    };

}

#endif //GSLANGUAGE_GS_LEXER_H
