#include <GS_Token.h>

namespace GSLanguageCompiler::Lexer {

    GS_Token::GS_Token(TokenType type)
            : _type(type) {}

    TokenType GS_Token::getTokenType() const {
        return _type;
    }

    GS_ValueToken::GS_ValueToken(TokenType type, UString value)
            : GS_Token(type), _value(std::move(value)) {}

    UString GS_ValueToken::getValue() const {
        return _value;
    }

}