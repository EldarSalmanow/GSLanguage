#ifndef GSLANGUAGE_GS_READER_H
#define GSLANGUAGE_GS_READER_H

#include <Reader/GS_Code.h>

namespace GSLanguageCompiler::Reader {

    /**
     * Stream type
     */
    using StreamT = IFStream;

    /**
     * Reader for read files
     */
    class GS_Reader {
    public:

        /**
         * Constructor for GS_Reader
         * @param stream Input stream
         */
        explicit GS_Reader(StreamT stream);

    public:

        /**
         * Reading source code and converting code to GS_Code
         * @return Code from stream
         */
        GS_Code read();

    private:

        /**
         * Read line from stream
         * @return Line from stream
         */
        GS_Line _getLine();

        /**
         * Read symbol from stream
         * @return Symbol from stream
         */
        GS_Symbol _getSymbol();

        /**
         * Next line from stream
         * @return
         */
        Void _nextLine();

        /**
         * Next symbol from stream
         * @return
         */
        Void _nextSymbol();

    private:

        /**
         * Stream for reading code
         */
        StreamT _stream;

        /**
         * Line and column in source code
         */
        IndexT _line, _column;
    };

}

#endif //GSLANGUAGE_GS_READER_H
