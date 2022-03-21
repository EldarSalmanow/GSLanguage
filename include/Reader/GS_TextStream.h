#ifndef GSLANGUAGE_GS_TEXTSTREAM_H
#define GSLANGUAGE_GS_TEXTSTREAM_H

#include <Reader/GS_Reader.h>

namespace GSLanguageCompiler::Reader {

    /**
     * Stream class for source code
     */
    class GS_TextStream {
    public:

        /**
         * Constructor for text stream
         * @param reader Reader
         */
        explicit GS_TextStream(LRef<GS_Reader> reader);

    public:

        /**
         * Getting symbol from stream
         * @return Current symbol
         */
        USymbol CurrentSymbol();

        /**
         * Setting cursor to next symbol in stream
         * @return
         */
        Void NextSymbol();

        /**
         * Setting cursor to prev symbol in stream
         * @return
         */
        Void PrevSymbol();

    private:

        /**
         * Source code string
         */
        UString _string;

        /**
         * Source code string iterator
         */
        UString::Iterator _stringIterator;
    };

}

#endif //GSLANGUAGE_GS_TEXTSTREAM_H
