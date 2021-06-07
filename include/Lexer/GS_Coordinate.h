#ifndef GSLANGUAGE_GS_COORDINATE_H
#define GSLANGUAGE_GS_COORDINATE_H

#include <CrossPlatform/GS_PlatformTypes.h>

namespace GSLanguageCompiler::Lexer {

    /**
     * Class for representation position in source code
     */
    class GS_Coordinate {
    public:

        GS_Coordinate() = default;

        /**
         * Constructor for GS_Coordinate
         * @param line Line position
         * @param column Column position
         */
        GS_Coordinate(GSULongLong line, GSULongLong column);

    public:

        /**
         * Getter line position in source code
         * @return Line number
         */
        GSULongLong getLine();

        /**
         * Getter column position in source code
         * @return Column number
         */
        GSULongLong getColumn();

    private:

        /**
         * Position in source code from file
         */
        GSULongLong _line = 0, _column = 0;
    };

}

#endif //GSLANGUAGE_GS_COORDINATE_H
