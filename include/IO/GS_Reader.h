#ifndef GSLANGUAGE_GS_READER_H
#define GSLANGUAGE_GS_READER_H

#include <Driver/GS_CompilerSessionConfig.h>

#include <IO/GS_Stream.h>

namespace GSLanguageCompiler::IO {

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
        UString Read();

    private:

        /**
         * Stream for reading text
         */
        GSInStreamPtr _stream;
    };

}

#endif //GSLANGUAGE_GS_READER_H
