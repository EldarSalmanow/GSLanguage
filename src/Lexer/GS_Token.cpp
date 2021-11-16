#include <GS_Token.h>

namespace GSLanguageCompiler::Lexer {

    GS_Token::GS_Token()
            : _type(TokenType::Unknown) {}

    GS_Token::GS_Token(TokenType type)
            : _type(type) {}

    GS_Token::GS_Token(TokenType type, String value)
            : _type(type), _value(std::move(value)) {}

    TokenType GS_Token::getType() {
        return _type;
    }

    String GS_Token::getValue() {
        return _value;
    }

}