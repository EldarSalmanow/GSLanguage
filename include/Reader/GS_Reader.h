#ifndef GSLANGUAGE_GS_READER_H
#define GSLANGUAGE_GS_READER_H

#include <GSCrossPlatform/GS_CrossPlatformTypes.h>

namespace GSLanguageCompiler::Reader {

    /**
     * Symbol type
     */
    using SymbolT = CharType;

    /**
     * Stream type
     */
    using StreamT = IStream*;

    /**
     * Reader for read files
     */
    class GS_Reader {
    public:

        /**
         * Constructor for GS_Reader
         * @param stream Input stream
         */
        explicit GS_Reader(StreamT stream);

    public:

        /**
         * Reading symbol from input stream
         * @return Symbol
         */
        SymbolT getSymbol();

        /**
         * Reading next symbol from input stream
         * @return Symbol
         */
        SymbolT nextSymbol();

        /**
         * Reading prev symbol from input stream
         * @return Symbol
         */
        SymbolT prevSymbol();

    private:

        /**
         * Stream for reading code
         */
        StreamT _stream;
    };

}

#endif //GSLANGUAGE_GS_READER_H
