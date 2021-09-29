#ifndef GSLANGUAGE_GS_LEXER_H
#define GSLANGUAGE_GS_LEXER_H

#include <Lexer/GS_InputTextAnalyzer.h>
#include <Lexer/GS_CodeReader.h>

namespace GSLanguageCompiler::Lexer {

    /**
     * Class for analyzing source code
     */
    class GS_Lexer {
    public:

        /**
         * Constructor for GS_Lexer
         * @param code Input code
         */
        explicit GS_Lexer(Reader::GS_Code code);

    public:

        /**
         * Tokenizing input code
         * @return Tokens array
         */
        GSTokenArray tokenize();

    private:

        /**
         * Interface for getting symbols from source code
         */
        GS_CodeReader _codeReader;
    };

}

#endif //GSLANGUAGE_GS_LEXER_H
