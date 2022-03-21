#include <GS_Token.h>

namespace GSLanguageCompiler::Lexer {

    GS_Token::GS_Token(TokenType type, UString value)
            : _type(type), _value(std::move(value)) {}

    GS_Token GS_Token::Create(TokenType type, UString value) {
        return GS_Token(type, std::move(value));
    }

    GS_Token GS_Token::Create(TokenType type) {
        return GS_Token::Create(type, UString());
    }

    TokenType GS_Token::GetType() const {
        return _type;
    }

    UString GS_Token::GetValue() const {
        return _value;
    }

}