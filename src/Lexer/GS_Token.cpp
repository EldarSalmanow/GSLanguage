#include <GS_Token.h>

namespace GSLanguageCompiler::Lexer {

    GS_Token::GS_Token(TokenType type, GS_Position position)
            : _type(type), _position(std::move(position)) {}

    GS_Token::GS_Token(TokenType type, std::string word, GS_Position position)
            : _type(type), _value(std::move(word)), _position(std::move(position)) {}

    TokenType GS_Token::getType() {
        return _type;
    }

    std::string GS_Token::getValue() {
        return _value;
    }

    GS_Position GS_Token::getPosition() {
        return _position;
    }

}