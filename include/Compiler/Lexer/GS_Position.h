#ifndef GSLANGUAGE_GS_POSITION_H
#define GSLANGUAGE_GS_POSITION_H

#include <ctype.h>

namespace GSLanguageCompiler::Lexer {

    /**
     * Class for displaying information about the location of a character in the source file
     */
    class GS_Position {
    public:

        /**
         * Default constructor for GS_Position
         */
        GS_Position() = default;

        /**
         * Constructor for GS_Position
         * @param line
         */
        GS_Position(size_t line, size_t column);

        /**
         * Getter for _line position in source
         * @return
         */
        size_t getLine();

        /**
         * Getter for _column position in source
         * @return
         */
        size_t getColumn();

    private:

        /**
         * Position in source file
         */
        size_t _line, _column;
    };

}

#endif //GSLANGUAGE_GS_POSITION_H
