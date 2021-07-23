#ifndef GSLANGUAGE_GS_READER_H
#define GSLANGUAGE_GS_READER_H

#include <fstream>
#include <vector>
#include <memory>

#include <CrossPlatform/GS_PlatformTypes.h>

#include <Exceptions/GS_Exception.h>

namespace GSLanguageCompiler {

    typedef std::vector<GSString> GSText;

    /**
     * Reader for read files
     */
    class GS_Reader {
    public:

        /**
         * Constructor for GS_Reader
         * @param filename Name of the main file to read
         */
        GS_Reader(GSString filename);

        /**
         * The file read function takes the file name from the GS_Reader class object and line by line
         * reads a file through a file I/O stream.
         * @return Lines code from file
         */
        GSText readFile();

    private:

        /**
         * Code from file
         */
        GSText _input;

        /**
         * The name of the file being read
         */
        GSString _filename;
    };

}

#endif //GSLANGUAGE_GS_READER_H
