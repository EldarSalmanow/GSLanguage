#ifndef GSLANGUAGE_GS_TOKEN_H
#define GSLANGUAGE_GS_TOKEN_H

#include <Reader/GS_Code.h>

#include <Lexer/GS_Keywords.h>

namespace GSLanguageCompiler::Lexer {

    namespace New {

        enum class TokenType {
            Identifier,             // 'main'

            LiteralNumber,          // '12'

            KeywordVar,             // 'var'
            KeywordFunc,            // 'func'

            SymbolSpace,            // ' '

            SymbolLeftParen,        // (
            SymbolRightParen,       // )
            SymbolLeftBrace,        // {
            SymbolRightBrace,       // }

            SymbolDoubleQuotes,     // "
            SymbolColon,            // :
            SymbolComma,            // ,

            SymbolPlus,             // +
            SymbolMinus,            // -
            SymbolStar,             // *
            SymbolSlash,            // /
            SymbolEq,               // =

            Invalid
        };

        class GS_Token {
        public:

            ~GS_Token();

        public:

            virtual TokenType getTokenType();
        };

        using GSTokenPtr = SharedPtr<GS_Token>;

        class GS_BaseToken : public GS_Token {
        public:

            explicit GS_BaseToken(TokenType type);

        public:

            TokenType getTokenType() override;

        private:

            TokenType _type;
        };

        class GS_TokenWithValue : public GS_BaseToken {
        public:

            GS_TokenWithValue(TokenType type, String value);

        public:

            String getValue();

        private:

            String _value;
        };

    }

    /**
     * Index type
     */
    using IndexT = U64;

    /**
     * Class for displaying information about the location of a character in the source file
     */
    class GS_Position {
    public:

        /**
         * Default constructor for GS_Position
         */
        GS_Position();

        /**
         * Constructor for GS_Position
         * @param code String code
         * @param line Line in code
         * @param column Column in code
         */
        GS_Position(String code, IndexT line, IndexT column);

    public:

        /**
         * Getter for string with code
         * @return Code line
         */
        String getCode();

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
         * Code line from source file
         */
        String _code;

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
         * @param position Token position
         */
        GS_Token(TokenType type, GS_Position position);

        /**
         * Constructor for GS_Token
         * @param type Token type
         * @param word Value
         * @param position Token position
         */
        GS_Token(TokenType type, String word, GS_Position position);

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
         * Getter for position in source file
         * @return Position in source file
         */
        GS_Position getPosition();

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
         * Token position
         */
        GS_Position _position;
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
