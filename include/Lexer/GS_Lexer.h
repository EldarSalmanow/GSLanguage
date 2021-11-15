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
         * @param textStream
         */
        explicit GS_Lexer(Reader::GS_TextStream textStream);

    public:

        /**
         *
         * @return
         */
        GS_Token getToken();

    private:

        /**
         *
         */
        Reader::GS_TextStream _textStream;
    };

}

#endif //GSLANGUAGE_GS_LEXER_H
