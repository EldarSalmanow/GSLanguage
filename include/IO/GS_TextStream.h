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
         * @param symbols Symbols
         */
        explicit GS_TextStream(GSSymbolArray symbols);

    public:

        /**
         * Creating text stream
         * @param symbols Symbols
         * @return Text stream
         */
        static GS_TextStream Create(GSSymbolArray symbols);

        /**
         * Creating text stream
         * @param reader Reader
         * @return Text stream
         */
        static GS_TextStream Create(LRef<GS_Reader> reader);

        /**
         * Creating text stream
         * @param text Text
         * @return Text stream
         */
        static GS_TextStream Create(UString text);

    public:

        /**
         * Getting symbol from stream
         * @return Current symbol
         */
        GS_Symbol CurrentSymbol();

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
         * Source code symbols
         */
        GSSymbolArray _symbols;

        /**
         * Source code symbols iterator
         */
        GSSymbolArray::iterator _symbolsIterator;
    };

}

#endif //GSLANGUAGE_GS_TEXTSTREAM_H
