#ifndef GSLANGUAGE_GS_SYMBOL_H
#define GSLANGUAGE_GS_SYMBOL_H

#include <vector>

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::IO {

    /**
     * Class for containing information about symbol location
     */
    class GS_SymbolLocation {
    public:

        /**
         * Constructor for symbol location
         * @param sourceName Source name
         * @param line Line
         * @param column Column
         * @return Symbol location
         */
        GS_SymbolLocation(UString sourceName, U64 line, U64 column);

    public:

        /**
         * Creating symbol location
         * @param sourceName Source name
         * @param line Line
         * @param column Column
         * @return Symbol location
         */
        static GS_SymbolLocation Create(UString sourceName, U64 line, U64 column);

        /**
         * Creating symbol location
         * @param line Line
         * @param column Column
         * @return Symbol location
         */
        static GS_SymbolLocation Create(U64 line, U64 column);

        /**
         * Creating symbol location
         * @return Symbol location
         */
        static GS_SymbolLocation Create();

    public:

        /**
         * Getter for source name
         * @return Source name
         */
        UString GetSourceName() const;

        /**
         * Getter for line
         * @return Line
         */
        U64 GetLine() const;

        /**
         * Getter for column
         * @return Column
         */
        U64 GetColumn() const;

    private:

        /**
         * Source name
         */
        UString _sourceName;

        /**
         * Line
         */
        U64 _line;

        /**
         * Column
         */
        U64 _column;
    };

    /**
     * Class for containing information symbol
     */
    class GS_Symbol {
    public:

        /**
         * Constructor for symbol
         * @param value Symbol value
         * @param location Symbol location
         */
        GS_Symbol(USymbol value, GS_SymbolLocation location);

    public:

        /**
         * Creating symbol
         * @param value Symbol value
         * @param location Symbol location
         * @return Symbol
         */
        static GS_Symbol Create(USymbol value, GS_SymbolLocation location);

        /**
         * Creating symbol
         * @param value Symbol value
         * @return Symbol
         */
        static GS_Symbol Create(USymbol value);

        /**
         * Creating symbol
         * @return Symbol
         */
        static GS_Symbol Create();

    public:

        /**
         * Getter for unicode symbol
         * @return Unicode symbol
         */
        USymbol GetValue() const;

        /**
         * Getter for symbol location
         * @return Symbol location
         */
        GS_SymbolLocation GetLocation() const;

    private:

        /**
         * Symbol value
         */
        USymbol _value;

        /**
         * Symbol location
         */
        GS_SymbolLocation _location;
    };

    /**
     * Symbol array type
     */
    using GSSymbolArray = std::vector<GS_Symbol>;

    /**
     * Symbol array iterator type
     */
    using GSSymbolArrayIterator = GSSymbolArray::iterator;

}

#endif //GSLANGUAGE_GS_SYMBOL_H
