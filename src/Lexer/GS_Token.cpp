#include <GS_Token.h>

namespace GSLanguageCompiler::Lexer {

    GS_TokenLocation::GS_TokenLocation(UString sourceName, U64 line, U64 column)
            : _sourceName(std::move(sourceName)), _line(line), _column(column) {}

    GS_TokenLocation GS_TokenLocation::Create(UString sourceName, U64 line, U64 column) {
        return GS_TokenLocation(std::move(sourceName), line, column);
    }

    GS_TokenLocation GS_TokenLocation::Create(U64 line, U64 column) {
        return GS_TokenLocation::Create("<unknown>"_us, line, column);
    }

    GS_TokenLocation GS_TokenLocation::Create() {
        return GS_TokenLocation::Create(0, 0);
    }

    UString GS_TokenLocation::GetSourceName() const {
        return _sourceName;
    }

    U64 GS_TokenLocation::GetLine() const {
        return _line;
    }

    U64 GS_TokenLocation::GetColumn() const {
        return _column;
    }

    GS_Token::GS_Token(TokenType type, UString value, GS_TokenLocation location)
            : _type(type), _value(std::move(value)), _location(std::move(location)) {}

    GS_Token GS_Token::Create(TokenType type, UString value, GS_TokenLocation location) {
        return GS_Token(type, std::move(value), std::move(location));
    }

    GS_Token GS_Token::Create(TokenType type, UString value) {
        return GS_Token::Create(type, std::move(value), GS_TokenLocation::Create());
    }

    GS_Token GS_Token::Create(TokenType type, GS_TokenLocation location) {
        return GS_Token::Create(type, UString(), std::move(location));
    }

    GS_Token GS_Token::Create(TokenType type) {
        return GS_Token::Create(type, GS_TokenLocation::Create());
    }

    TokenType GS_Token::GetType() const {
        return _type;
    }

    UString GS_Token::GetValue() const {
        return _value;
    }

    GS_TokenLocation GS_Token::GetLocation() const {
        return _location;
    }

}