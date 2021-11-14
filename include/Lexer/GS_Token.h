#ifndef GSLANGUAGE_GS_TOKEN_H
#define GSLANGUAGE_GS_TOKEN_H

#include <Lexer/GS_Keywords.h>

namespace GSLanguageCompiler::Lexer {

    /**
     * Index type
     */
    using IndexT = U64;

    /**
     * Class for displaying information about the location of a character in the source file
     */
    class GS_Location {
    public:

        /**
         * Default constructor for GS_Position
         */
        GS_Location();

        /**
         * Constructor for GS_Position
         * @param line Line in code
         * @param column Column in code
         */
        GS_Location(IndexT line, IndexT column);

    public:

        /**
         * Getter for line
         * @return Line
         */
        IndexT getLine();

        /**
         * Getter for column
         * @return Column
         */
        IndexT getColumn();

    private:

        /**
         * Position in source file
         */
        IndexT _line, _column;
    };

    /**
     * Class for issuing information about the token
     */
    class GS_Token {
    public:

        /**
         * Default constructor for GS_Token
         */
        GS_Token() = default;

        /**
         * Constructor for GS_Token
         * @param type Token type
         * @param location Token location
         */
        GS_Token(TokenType type, GS_Location location);

        /**
         * Constructor for GS_Token
         * @param type Token type
         * @param word Value
         * @param location Token location
         */
        GS_Token(TokenType type, String word, GS_Location location);

    public:

        /**
         * Getter for type
         * @return Token type
         */
        TokenType getType();

        /**
         * Getter for value
         * @return Token value
         */
        String getValue();

        /**
         * Getter for location in source file
         * @return Location in source file
         */
        GS_Location getLocation();

    private:

        /**
         * Type of token
         */
        TokenType _type;

        /**
         * String value or name
         */
        String _value;

        /**
         * Token location
         */
        GS_Location _location;
    };

    /**
     * Token array type
     */
    using GSTokenArray = Vector<GS_Token>;

    /**
     * Token array iterator type
     */
    using GSTokenArrayIterator = Vector<GS_Token>::iterator;

}

#endif //GSLANGUAGE_GS_TOKEN_H
