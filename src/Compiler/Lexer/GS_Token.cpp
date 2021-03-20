#include "../../../include/Compiler/Lexer/GS_Token.h"

namespace GSLanguageCompiler::Lexer {

    GS_Token::GS_Token(TokenType type) {
        this->_type = type;
    }

    GS_Token::GS_Token(TokenType type, std::string &word) {
        this->_type = type;
        this->_value = word;
    }

    TokenType GS_Token::getType() {
        return this->_type;
    }

    std::string GS_Token::getValue() {
        return this->_value;
    }

}