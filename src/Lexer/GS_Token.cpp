#include <GS_Token.h>

namespace GSLanguageCompiler::Lexer {

    namespace New {

        GS_Token::~GS_Token() = default;

        TokenType GS_Token::getTokenType() {
            return TokenType::Invalid;
        }

        GS_BaseToken::GS_BaseToken(TokenType type)
                : _type(type) {}

        TokenType GS_BaseToken::getTokenType() {
            return _type;
        }



    }

    GS_Position::GS_Position()
            : _line(0), _column(0) {}

    GS_Position::GS_Position(String code, IndexT line, IndexT column)
            : _code(std::move(code)), _line(line), _column(column) {}

    String GS_Position::getCode() {
        return _code;
    }

    IndexT GS_Position::getLine() {
        return _line;
    }

    IndexT GS_Position::getColumn() {
        return _column;
    }

    GS_Token::GS_Token(TokenType type, GS_Position position)
            : _type(type), _position(std::move(position)) {}

    GS_Token::GS_Token(TokenType type, String word, GS_Position position)
            : _type(type), _value(std::move(word)), _position(std::move(position)) {}

    TokenType GS_Token::getType() {
        return _type;
    }

    String GS_Token::getValue() {
        return _value;
    }

    GS_Position GS_Token::getPosition() {
        return _position;
    }

}