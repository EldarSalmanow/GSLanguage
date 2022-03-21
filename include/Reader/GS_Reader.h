#ifndef GSLANGUAGE_GS_READER_H
#define GSLANGUAGE_GS_READER_H

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::Reader {

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
         * Reading text from source
         * @return Text
         */
        UString ReadText();

    private:

        /**
         * file for reading code
         */
        UniquePtr<File> _file;
    };

}

#endif //GSLANGUAGE_GS_READER_H
