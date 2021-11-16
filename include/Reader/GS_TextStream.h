#ifndef GSLANGUAGE_GS_TEXTSTREAM_H
#define GSLANGUAGE_GS_TEXTSTREAM_H

#include <Reader/GS_Reader.h>

namespace GSLanguageCompiler::Reader {

    /**
     *
     */
    class GS_TextStream {
    public:

        /**
         *
         * @param reader
         */
        explicit GS_TextStream(GS_Reader reader);

    public:

        /**
         *
         * @return
         */
        SymbolT getSymbol();

        /**
         *
         * @return
         */
        SymbolT nextSymbol();

        /**
         *
         * @return
         */
        SymbolT prevSymbol();

    public:

        /**
         *
         * @param symbol
         * @return
         */
        GS_TextStream &operator>>(SymbolT &symbol);

    private:

        /**
         *
         */
        GS_Reader _reader;
    };

}

#endif //GSLANGUAGE_GS_TEXTSTREAM_H
