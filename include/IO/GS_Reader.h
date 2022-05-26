#ifndef GSLANGUAGE_GS_READER_H
#define GSLANGUAGE_GS_READER_H

#include <GSCrossPlatform/CrossPlatform.h>

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
        explicit GS_Reader(LRef<std::istream> stream);

    public:

        /**
         * Creating reader
         * @param stream Stream
         * @return Reader
         */
        static GS_Reader Create(LRef<std::istream> stream);

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
        LRef<std::istream> _stream;
    };

}

#endif //GSLANGUAGE_GS_READER_H
