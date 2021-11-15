#include <GS_Token.h>

namespace GSLanguageCompiler::Lexer {

    GS_Location::GS_Location()
            : _line(0), _column(0) {}

    GS_Location::GS_Location(IndexT line, IndexT column)
            : _line(line), _column(column) {}

    IndexT GS_Location::getLine() {
        return _line;
    }

    IndexT GS_Location::getColumn() {
        return _column;
    }

    GS_Token::GS_Token(TokenType type)
            : _type(type) {}

    GS_Token::GS_Token(TokenType type, GS_Location location)
            : _type(type), _location(location) {}

    GS_Token::GS_Token(TokenType type, String value)
            : _type(type), _value(std::move(value)) {}

    GS_Token::GS_Token(TokenType type, String word, GS_Location location)
            : _type(type), _value(std::move(word)), _location(location) {}

    TokenType GS_Token::getType() {
        return _type;
    }

    String GS_Token::getValue() {
        return _value;
    }

    GS_Location GS_Token::getLocation() {
        return _location;
    }

}