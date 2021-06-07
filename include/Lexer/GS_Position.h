#ifndef GSLANGUAGE_GS_POSITION_H
#define GSLANGUAGE_GS_POSITION_H

#include <string>

#include <Lexer/GS_Coordinate.h>

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
        GS_Position(std::string code, GS_Coordinate start, GS_Coordinate end);


    public:

        /**
         * Getter for start position
         * @return Start position
         */
        GS_Coordinate getStartPosition();

        /**
         * Getter for end position
         * @return End position
         */
        GS_Coordinate getEndPosition();

        /**
         * Getter for string with code
         * @return Code line
         */
        std::string getCode();

    private:

        /**
         * Position in source file
         */
        GS_Coordinate _startPosition, _endPosition;

        /**
         * Code line from source file
         */
        std::string _code;
    };

}

#endif //GSLANGUAGE_GS_POSITION_H
