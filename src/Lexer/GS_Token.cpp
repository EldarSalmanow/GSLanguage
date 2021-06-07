#include <GS_Token.h>

namespace GSLanguageCompiler::Lexer {

    GS_Token::GS_Token(TokenType type, GS_Position position) {
        this->_type = type;
        this->_position = position;
    }

    GS_Token::GS_Token(TokenType type, std::string &word, GS_Position position) {
        this->_type = type;
        this->_value = word;
        this->_position = position;
    }

    TokenType GS_Token::getType() {
        return this->_type;
    }

    std::string GS_Token::getValue() {
        return this->_value;
    }

    GS_Position GS_Token::getPosition() {
        return this->_position;
    }

}