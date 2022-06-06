#ifndef GSLANGUAGE_GS_READER_H
#define GSLANGUAGE_GS_READER_H

#include <IO/GS_Stream.h>

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
        explicit GS_Reader(std::unique_ptr<GS_InStream> stream);

    public:

        /**
         * Creating reader
         * @param stream Stream
         * @return Reader
         */
        static GS_Reader Create(std::unique_ptr<GS_InStream> stream);

    public:

        /**
         * Reading text from source
         * @return Text
         */
        UString ReadText();

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
        std::unique_ptr<GS_InStream> _stream;
    };

}

#endif //GSLANGUAGE_GS_READER_H
