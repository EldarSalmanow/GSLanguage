#ifndef GSLANGUAGE_GS_CURSOR_H
#define GSLANGUAGE_GS_CURSOR_H

#include <IO/GS_Source.h>

namespace GSLanguageCompiler::Lexer {

    /**
     * Class for smart iterating over source code
     */
    class GS_Cursor {
    public:

        /*
         *
         * GS_Cursor PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for cursor
         * @param source Source
         */
        explicit GS_Cursor(ConstLRef<IO::GS_Source> source);

    public:

        /*
         *
         * GS_Cursor PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating cursor
         * @param source Source
         * @return Cursor
         */
        static GS_Cursor Create(ConstLRef<IO::GS_Source> source);

    public:

        /*
         *
         * GS_Cursor PUBLIC METHODS
         *
         */

        /**
         * Getting current symbol from cursor
         * @return Current symbol
         */
        ConstLRef<USymbol> CurrentSymbol() const;

        /**
         * Setting cursor to next symbol in source
         * @return Void return
         */
        Void NextSymbol();

        /**
         * Lookup for next symbol by offset from current position
         * @param index Index
         * @return Symbol by offset
         */
        ConstLRef<USymbol> LookupSymbol(U64 index) const;

        /**
         * Getting current location
         * @return Current location
         */
        IO::GS_SourceLocation CurrentLocation() const;

        /**
         * Saving current position for calculating length of token in future
         * @return Void return
         */
        Void SavePosition();

        /**
         * Is end of source
         * @return Is end of source
         */
        Bool IsEnd() const;

    public:

        /*
         *
         * GS_Cursor PUBLIC OPERATOR METHODS
         *
         */

        /**
         * Getting current symbol from cursor
         * @return Current symbol
         */
        ConstLRef<USymbol> operator*() const;

        /**
         * Setting cursor to next symbol in source
         * @return Cursor
         */
        LRef<GS_Cursor> operator++();

    private:

        /*
         *
         * GS_Cursor PRIVATE FIELDS
         *
         */

        /**
         * Source
         */
        ConstLRef<IO::GS_Source> _source;

        /**
         * Source iterator
         */
        IO::GS_Source::ConstIterator _sourceIterator;

        /**
         * Saved position
         */
        I64 _savedPosition;

        /**
         * Current position
         */
        I64 _currentPosition;
    };

}

#endif //GSLANGUAGE_GS_CURSOR_H
