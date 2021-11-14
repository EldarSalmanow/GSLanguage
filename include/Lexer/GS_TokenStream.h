#ifndef GSLANGUAGE_GS_TOKENSTREAM_H
#define GSLANGUAGE_GS_TOKENSTREAM_H

#include <Lexer/GS_Lexer.h>

namespace GSLanguageCompiler::Lexer {

    class GS_TokenStream {
    public:

        /**
         *
         * @param lexer
         */
        explicit GS_TokenStream(GS_Lexer lexer);

    public:

        GS_Token getToken();

    public:

        GS_TokenStream &operator>>(GS_Token &token);

    private:

        /**
         *
         */
        GS_Lexer _lexer;
    };

}

#endif //GSLANGUAGE_GS_TOKENSTREAM_H
