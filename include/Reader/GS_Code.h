#ifndef GSLANGUAGE_GS_CODE_H
#define GSLANGUAGE_GS_CODE_H

#include <GSCrossPlatform/GS_CrossPlatformTypes.h>

namespace GSLanguageCompiler::Reader {

    /**
     * Symbol type
     */
    using SymbolT = CharType;

    /**
     * Index type
     */
    using IndexT = U64;

    /**
     * Class for containing symbol and position
     */
    class GS_Symbol {
    public:

        /**
         * Constructor for GS_Symbol
         * @param symbol Char symbol
         * @param line Line in source code
         * @param column Column in source code
         */
        GS_Symbol(SymbolT symbol, IndexT line, IndexT column);

    public:

        /**
         * Getter for char symbol
         * @return Char symbol
         */
        SymbolT getSymbol();

        /**
         * Getter for line in source code
         * @return Line in source code
         */
        IndexT getLine();

        /**
         * Getter for column in source code
         * @return Column in source code
         */
        IndexT getColumn();

    private:

        /**
         * Char symbol
         */
        SymbolT _symbol;

        /**
         * Line and column in source code
         */
        IndexT _line, _column;
    };

    /**
     * Class for containing symbols in line from source code
     */
    class GS_Line {
    public:

        /**
         * Constructor for GS_Line
         * @param symbols Array of symbols
         */
        explicit GS_Line(Vector<GS_Symbol> symbols);

    public:

        /**
         * Getter for symbol in line
         * @param index Index in line
         * @return Symbol from line
         */
        GS_Symbol getSymbol(IndexT index);

        /**
         * Getter for start iterator in line
         * @return Start iterator in line
         */
        VectorIterator<GS_Symbol> getStartIterator();

        /**
         * Getter for end iterator in line
         * @return End iterator in line
         */
        VectorIterator<GS_Symbol> getEndIterator();

        /**
         * Getter for begin iterator in line
         * @return Begin iterator in line
         */
        VectorIterator<GS_Symbol> begin();

        /**
         * Getter for end iterator in line
         * @return End iterator in line
         */
        VectorIterator<GS_Symbol> end();

        /**
         * Getter for line as string
         * @return Line as string
         */
        String getLineAsString();

    private:

        /**
         * Array for containing symbols
         */
        Vector<GS_Symbol> _symbols;
    };

    /**
     * Class for containing code from file
     */
    class GS_Code {
    public:

        /**
         * Constructor for GS_Code
         * @param lines Array of lines from source code
         */
        explicit GS_Code(Vector<GS_Line> lines);

    public:

        /**
         * Getter for line from source code
         * @param index Index in array
         * @return Line from source code
         */
        GS_Line getLine(IndexT index);

        /**
         * Getter for start iterator in code
         * @return Start iterator in code
         */
        VectorIterator<GS_Line> getStartIterator();

        /**
         * Getter for end iterator in code
         * @return End iterator in code
         */
        VectorIterator<GS_Line> getEndIterator();

        /**
         * Getter for begin iterator in code
         * @return Begin iterator in code
         */
        VectorIterator<GS_Line> begin();

        /**
         * Getter for end iterator in code
         * @return End iterator in code
         */
        VectorIterator<GS_Line> end();

    private:

        /**
         * Array for containing lines from source code
         */
        Vector<GS_Line> _lines;
    };

}

#endif //GSLANGUAGE_GS_CODE_H
