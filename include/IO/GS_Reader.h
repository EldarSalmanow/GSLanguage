#ifndef GSLANGUAGE_GS_READER_H
#define GSLANGUAGE_GS_READER_H

#include <IO/GS_Stream.h>

namespace GSLanguageCompiler::IO {

    /**
     * Reader for reading text
     */
    class GS_Reader {
    public:

        /*
         *
         * GS_Reader PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for reader
         * @param stream Input stream
         */
        explicit GS_Reader(LRef<InputStream> stream);

    public:

        /*
         *
         * GS_Reader PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating reader
         * @param stream Input stream
         * @return Reader
         */
        static GS_Reader Create(LRef<InputStream> stream);

    public:

        /*
         *
         * GS_Reader PUBLIC STATIC METHODS
         *
         */

        /**
         * Creating reader and reading text from stream
         * @param stream Input stream
         * @return Text from stream
         */
        static UString Run(LRef<InputStream> stream);

    public:

        /*
         *
         * GS_Reader PUBLIC METHODS
         *
         */

        /**
         * Reading text from stream
         * @return Text from stream
         */
        UString Read();

    private:

        /*
         *
         * GS_Reader PRIVATE FIELDS
         *
         */

        /**
         * Input stream for reading text
         */
        LRef<InputStream> _stream;
    };

}

#endif //GSLANGUAGE_GS_READER_H
