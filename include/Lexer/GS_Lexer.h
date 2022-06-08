#ifndef GSLANGUAGE_GS_LEXER_H
#define GSLANGUAGE_GS_LEXER_H

#include <IO/IO.h>

#include <Lexer/GS_Token.h>

namespace GSLanguageCompiler::Lexer {

    /**
     * Declaring token stream
     */
    class GS_TokenStream;

    /**
     * Class for tokenizing source code
     */
    class GS_Lexer {
    public:

        /**
         * Constructor for lexer
         * @param textStream Text stream
         */
        explicit GS_Lexer(LRef<IO::GS_TextStream> textStream);

    public:

        /**
         * Creating lexer
         * @param textStream Text stream
         * @return Lexer
         */
        static GS_Lexer Create(LRef<IO::GS_TextStream> textStream);

    public:

        /**
         * Tokenizing all source code
         * @return Tokens
         */
        GSTokenArray Tokenize();

    public:

        /**
         * Create token stream for reading tokens
         * @return Token stream
         */
        GS_TokenStream CreateStream();

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
        IO::GS_Symbol CurrentSymbol();

        /**
         * Getting current unicode symbol from stream
         * @return Current unicode symbol
         */
        USymbol CurrentUSymbol();

        /**
         * Getting current symbol location from stream
         * @return Current symbol location
         */
        IO::GS_SymbolLocation CurrentSymbolLocation();

        /**
         * Setting cursor to next symbol in stream
         * @return
         */
        Void NextSymbol();

    private:

        /**
         * Text stream
         */
        IO::GS_TextStream _stream;
    };

}

#endif //GSLANGUAGE_GS_LEXER_H
