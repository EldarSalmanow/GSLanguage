#ifndef GSLANGUAGE_GS_READER_H
#define GSLANGUAGE_GS_READER_H

#include <fstream>
#include <vector>
#include <memory>

#include "../../Exceptions/GS_ReaderException.h"

namespace GSLanguageCompiler {

    typedef std::vector<std::string> GSText;

    /**
     * Reader for read files
     */
    class GS_Reader {
    public:

        /**
         * Constructor for GS_Reader
         * @param filename Name of the main file to read
         */
        GS_Reader(std::string &filename) {
            this->filename = filename;
        }

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
        GSText input;

        /**
         * The name of the file being read
         */
        std::string filename;
    };

    typedef std::shared_ptr<GS_Reader> GSReaderPointer;

}

#endif //GSLANGUAGE_GS_READER_H
