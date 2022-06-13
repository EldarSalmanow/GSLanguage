#ifndef GSLANGUAGE_GS_READER_H
#define GSLANGUAGE_GS_READER_H

#include <IO/GS_Stream.h>

#include <IO/GS_Symbol.h>

namespace GSLanguageCompiler::IO {

    /**
     * Declaring text stream
     */
    class GS_TextStream;

    /**
     * Reader for read files
     */
    class GS_Reader {
    public:

        /**
         * Constructor for reader
         * @param stream Input stream
         */
        explicit GS_Reader(GSInStreamPtr stream);

    public:

        /**
         * Creating reader
         * @param stream Stream
         * @return Reader
         */
        static GS_Reader Create(GSInStreamPtr stream);

    public:

        /**
         * Reading symbols from source
         * @return Symbols
         */
        GSSymbolArray ReadSymbols();

    public:

        /**
         * Creating text stream for reading text
         * @return Text stream
         */
        GS_TextStream CreateStream();

    private:

        /**
         * Stream for reading text
         */
        GSInStreamPtr _stream;
    };

}

#endif //GSLANGUAGE_GS_READER_H
