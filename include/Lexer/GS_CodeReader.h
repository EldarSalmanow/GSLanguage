#ifndef GSLANGUAGE_GS_CODEREADER_H
#define GSLANGUAGE_GS_CODEREADER_H

#include <Reader/GS_Code.h>

#include <Lexer/GS_Token.h>

namespace GSLanguageCompiler::Lexer {

    using IndexT = U64;

    class GS_CodeReader {
    public:

        /**
         * Constructor for GS_CodeReader
         * @param code Source code
         */
        explicit GS_CodeReader(Reader::GS_Code code);

    public:

        /**
         * Current line in source code
         * @return Line in source code
         */
        Reader::GS_Line currentLine();

        /**
         * Current symbol in source code
         * @return Symbol in source code
         */
        Reader::GS_Symbol currentSymbol();

        /**
         * Current position
         * @return Current position
         */
        GS_Position currentPosition();

        /**
         * Next line
         * @return
         */
        Void nextLine();

        /**
         * Next symbol
         * @return
         */
        Void nextSymbol();

        /**
         * Prev symbol
         * @return
         */
        Void prevSymbol();

        /**
         * Is not end in source code
         * @return Is not end in source code
         */
        Bool codeIteratorInBounds();

        /**
         * Is not end in source code line
         * @return Is not end in source code line
         */
        Bool lineIteratorInBounds();

        /**
         * Getter for current line number
         * @return Current line number
         */
        IndexT getLineNumber();

        /**
         * Getter for current column number
         * @return Current column number
         */
        IndexT getColumnNumber();

    private:

        /**
         * Source code
         */
        Reader::GS_Code _code;

        /**
         * Source code iterator
         */
        VectorIterator<Reader::GS_Line> _codeIterator;

        /**
         * Source code line iterator
         */
        VectorIterator<Reader::GS_Symbol> _lineIterator;
    };

}

#endif //GSLANGUAGE_GS_CODEREADER_H
