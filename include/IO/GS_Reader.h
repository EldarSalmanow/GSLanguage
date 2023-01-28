#ifndef GSLANGUAGE_GS_READER_H
#define GSLANGUAGE_GS_READER_H

#include <IO/GS_Stream.h>

namespace GSLanguageCompiler::IO {

    /**
     * Reader for read text
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
        explicit GS_Reader(LRef<std::istream> stream);

    public:

        /*
         *
         * GS_Reader PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating reader
         * @param stream Stream
         * @return Reader
         */
        static GS_Reader Create(LRef<std::istream> stream);

    public:

        /*
         *
         * GS_Reader PUBLIC STATIC METHODS
         *
         */

        /**
         * Creating reader and reading text from stream
         * @param stream Stream
         * @return Text
         */
        static UString Run(LRef<std::istream> stream);

    public:

        /*
         *
         * GS_Reader PUBLIC METHODS
         *
         */

        /**
         * Reading text from stream
         * @return Text
         */
        UString Read();

    private:

        /*
         *
         * GS_Reader PRIVATE FIELDS
         *
         */

        /**
         * Stream for reading text
         */
        LRef<std::istream> _stream;
    };

}

#endif //GSLANGUAGE_GS_READER_H
