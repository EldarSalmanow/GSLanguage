#ifndef GSLANGUAGE_GS_TEXTSTREAM_H
#define GSLANGUAGE_GS_TEXTSTREAM_H

#include <Reader/GS_Reader.h>

namespace GSLanguageCompiler::Reader {

    /**
     *
     */
    class TextStream : public BufferedDataStream<SymbolT> {
    public:

        /**
         *
         * @param reader
         */
        explicit TextStream(Ptr<GS_Reader> reader);

        /**
         *
         * @param symbols
         */
        explicit TextStream(Vector<SymbolT> symbols);

    public:

        /**
         *
         * @return
         */
        DataT Get() override;

        /**
         *
         * @param data
         * @return
         */
        Void Put(DataT data) override;

    public:

        /**
         *
         * @return
         */
        StreamPosition GetPosition() override;

        /**
         *
         * @param position
         * @return
         */
        Bool SetPosition(StreamPosition position) override;

    private:

        /**
         *
         */
        Vector<SymbolT> _symbols;

        /**
         *
         */
        U64 _index;
    };

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
