#ifndef GSLANGUAGE_GS_LEXER_H
#define GSLANGUAGE_GS_LEXER_H

#include <Reader/GS_TextStream.h>

#include <Lexer/GS_Token.h>

namespace GSLanguageCompiler::Lexer {

    /**
     * Class for analyzing source code
     */
    class GS_Lexer {
    public:

        /**
         *
         * @param cursor
         */
        explicit GS_Lexer(Ptr<Reader::GS_TextStream> stream);

    public:

        /**
         *
         * @return
         */
        GSTokenPtr getToken();

    private:

        /**
         *
         * @return
         */
        GSTokenPtr _tokenizeWord();

        /**
         *
         * @return
         */
        GSTokenPtr _tokenizeNumber();

    private:

        /**
         *
         */
        Ptr<Reader::GS_TextStream> _stream;

        /**
         *
         */
        Reader::SymbolT _symbol;
    };

}

#endif //GSLANGUAGE_GS_LEXER_H
