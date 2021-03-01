#ifndef GSLANGUAGE_GS_TOKENIZER_H
#define GSLANGUAGE_GS_TOKENIZER_H

#include "GS_Token.h"
#include "GS_Regex.h"

namespace GSLanguageCompiler {

    /**
     * Class for tokenizing input text for GS_Lexer
     */
    class GS_Tokenizer {
    public:

        /**
         *
         * @return
         */
        static GS_Token tokenizeNumber();

        /**
         *
         * @return
         */
        static GS_Token tokenizeWord();
    };

}

#endif //GSLANGUAGE_GS_TOKENIZER_H
