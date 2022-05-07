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
         * @param file Input file
         */
        explicit GS_Reader(LRef<UniquePtr<File>> file);

    public:

        /**
         * Creating reader
         * @param file File
         * @return Reader
         */
        static GS_Reader Create(LRef<UniquePtr<File>> file);

        /**
         * Creating reader
         * @param name File name
         * @return Reader
         */
        static GS_Reader Create(UString name);

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
         * file for reading code
         */
        UniquePtr<File> _file;
    };

}

#endif //GSLANGUAGE_GS_READER_H
