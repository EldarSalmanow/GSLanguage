#ifndef GSLANGUAGE_GS_TOKENSTREAM_H
#define GSLANGUAGE_GS_TOKENSTREAM_H

#include <Lexer/GS_Token.h>

namespace GSLanguageCompiler::Lexer {

    class GS_TokenStream {
    public:

        /**
         *
         * @param tokenIterator
         */
        explicit GS_TokenStream(GSTokenArrayIterator &tokenIterator);

    public:

        GS_Token currentToken();

        TokenType tokenType(I32 offset = 0);

        String tokenValue(I32 offset = 0);

        Void next();

        Void prev();

        Bool isEqualTypes(TokenType type, I32 offset = 0);

    private:

        /**
         *
         */
        GSTokenArrayIterator _tokenIterator;
    };

}

#endif //GSLANGUAGE_GS_TOKENSTREAM_H
