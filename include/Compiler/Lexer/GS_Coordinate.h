#ifndef GSLANGUAGE_GS_COORDINATE_H
#define GSLANGUAGE_GS_COORDINATE_H

#include <ctype.h>

namespace GSLanguageCompiler::Lexer {

    /**
     *
     */
    class GS_Coordinate {
    public:

        GS_Coordinate() = default;

        /**
         *
         * @param line
         * @param column
         */
        GS_Coordinate(size_t line, size_t column);

    public:

        /**
         *
         * @return
         */
        size_t getLine();

        /**
         *
         * @return
         */
        size_t getColumn();

    private:

        /**
         *
         */
        size_t _line = 0, _column = 0;
    };

}

#endif //GSLANGUAGE_GS_COORDINATE_H
