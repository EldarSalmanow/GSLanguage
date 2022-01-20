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
        explicit GS_TextStream(Ptr<GS_Reader> reader);

    public:

        /**
         *
         * @return
         */
        SymbolT getSymbol();

    public:

        /**
         *
         * @param symbol
         * @return
         */
        LRef<GS_TextStream> operator>>(LRef<SymbolT> symbol);

    private:

        /**
         *
         */
        Ptr<GS_Reader> _reader;
    };

}

#endif //GSLANGUAGE_GS_TEXTSTREAM_H
