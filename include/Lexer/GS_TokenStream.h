#ifndef GSLANGUAGE_GS_TOKENSTREAM_H
#define GSLANGUAGE_GS_TOKENSTREAM_H

#include <Lexer/GS_Lexer.h>

namespace GSLanguageCompiler::Lexer {

    /**
     *
     */
    class GS_TokenStream {
    public:

        /**
         *
         * @param tokens
         */
        explicit GS_TokenStream(GSTokenPtrArray tokens);

        /**
         *
         * @param lexer
         */
        explicit GS_TokenStream(Ptr<GS_Lexer> lexer);

    public:

        /**
         *
         * @return
         */
        GSTokenPtr getToken();

    public:

        /**
         *
         * @param token
         * @return
         */
        GS_TokenStream &operator>>(GSTokenPtr &token);

    private:

        /**
         *
         */
        Ptr<GS_Lexer> _lexer;

        /**
         *
         */
        GSTokenPtrArray _tokens;

        /**
         *
         */
        GSTokenPtrArrayIterator _tokenIterator;
    };

}

#endif //GSLANGUAGE_GS_TOKENSTREAM_H
