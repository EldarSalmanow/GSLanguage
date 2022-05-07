#ifndef GSLANGUAGE_GS_TEXTSTREAM_H
#define GSLANGUAGE_GS_TEXTSTREAM_H

#include <IO/GS_Reader.h>

namespace GSLanguageCompiler::IO {

    /**
     * Stream class for source code
     */
    class GS_TextStream {
    public:

        /**
         * Constructor for text stream
         * @param text Text
         */
        explicit GS_TextStream(UString text);

    public:

        /**
         * Creating text stream
         * @param text Text
         * @return Text stream
         */
        static GS_TextStream Create(UString text);

        /**
         * Creating text stream
         * @param reader Reader
         * @return Text stream
         */
        static GS_TextStream Create(LRef<GS_Reader> reader);

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
