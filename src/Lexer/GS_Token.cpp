#include <GS_Token.h>

namespace GSLanguageCompiler::Lexer {

    GS_TokenLocation::GS_TokenLocation(IO::GS_SymbolLocation startLocation, IO::GS_SymbolLocation endLocation)
            : _startLocation(std::move(startLocation)), _endLocation(std::move(endLocation)) {}

    GS_TokenLocation GS_TokenLocation::Create(IO::GS_SymbolLocation startLocation, IO::GS_SymbolLocation endLocation) {
        return GS_TokenLocation(std::move(startLocation), std::move(endLocation));
    }

    GS_TokenLocation GS_TokenLocation::Create(IO::GS_SymbolLocation location) {
        return GS_TokenLocation::Create(location, location);
    }

    GS_TokenLocation GS_TokenLocation::Create() {
        return GS_TokenLocation::Create(IO::GS_SymbolLocation::Create(), IO::GS_SymbolLocation::Create());
    }

    IO::GS_SymbolLocation GS_TokenLocation::GetStartLocation() const {
        return _startLocation;
    }

    IO::GS_SymbolLocation GS_TokenLocation::GetEndLocation() const {
        return _endLocation;
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
        return GS_Token::Create(type, UString(), GS_TokenLocation::Create());
    }

    GS_Token GS_Token::Create() {
        return GS_Token::Create(TokenType::Unknown, UString(), GS_TokenLocation::Create());
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