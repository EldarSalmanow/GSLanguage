#include <GS_Token.h>

namespace GSLanguageCompiler::Lexer {

    GS_Token::GS_Token(TokenType type,
                       UString value,
                       IO::GS_SourceLocation location)
            : _type(type),
              _value(std::move(value)),
              _location(location) {}

    GS_Token GS_Token::Create(TokenType type,
                              UString value,
                              IO::GS_SourceLocation location) {
        return GS_Token(type,
                        std::move(value),
                        location);
    }

    GS_Token GS_Token::Create(TokenType type,
                              UString value) {
        return GS_Token::Create(type,
                                std::move(value),
                                IO::GS_SourceLocation::Create());
    }

    GS_Token GS_Token::Create(TokenType type,
                              IO::GS_SourceLocation location) {
        return GS_Token::Create(type,
                                UString(),
                                location);
    }

    GS_Token GS_Token::Create(TokenType type) {
        return GS_Token::Create(type,
                                UString(),
                                IO::GS_SourceLocation::Create());
    }

    GS_Token GS_Token::Create() {
        return GS_Token::Create(TokenType::Unknown,
                                UString(),
                                IO::GS_SourceLocation::Create());
    }

    TokenType GS_Token::GetType() const {
        return _type;
    }

    ConstLRef<UString> GS_Token::GetValue() const {
        return _value;
    }

    IO::GS_SourceLocation GS_Token::GetLocation() const {
        return _location;
    }

    GS_TokenBuffer::GS_TokenBuffer(GSTokenArray tokens)
            : _tokens(std::move(tokens)) {}

    GS_TokenBuffer GS_TokenBuffer::Create(GSTokenArray tokens) {
        return GS_TokenBuffer(std::move(tokens));
    }

    GS_TokenBuffer::Iterator GS_TokenBuffer::begin() {
        return _tokens.begin();
    }

    GS_TokenBuffer::Iterator GS_TokenBuffer::end() {
        return _tokens.end();
    }

    GS_TokenBuffer::ConstIterator GS_TokenBuffer::begin() const {
        return _tokens.begin();
    }

    GS_TokenBuffer::ConstIterator GS_TokenBuffer::end() const {
        return _tokens.end();
    }

    GS_TokenBuffer::ConstIterator GS_TokenBuffer::cbegin() const {
        return _tokens.cbegin();
    }

    GS_TokenBuffer::ConstIterator GS_TokenBuffer::cend() const {
        return _tokens.cend();
    }

    ConstLRef<GSTokenArray> GS_TokenBuffer::GetTokens() const {
        return _tokens;
    }

    GS_TokenBuilder::GS_TokenBuilder(TokenType tokenType,
                                     UString tokenValue,
                                     IO::GS_SourceLocation tokenLocation)
            : _tokenType(tokenType),
              _tokenValue(std::move(tokenValue)),
              _tokenLocation(tokenLocation) {}

    GS_TokenBuilder GS_TokenBuilder::Create(TokenType tokenType,
                                            UString tokenValue,
                                            IO::GS_SourceLocation tokenLocation) {
        return GS_TokenBuilder(tokenType,
                               std::move(tokenValue),
                               tokenLocation);
    }

    GS_TokenBuilder GS_TokenBuilder::Create(TokenType tokenType,
                                            UString tokenValue) {
        return GS_TokenBuilder::Create(tokenType,
                                       std::move(tokenValue),
                                       IO::GS_SourceLocation::Create());
    }

    GS_TokenBuilder GS_TokenBuilder::Create(TokenType tokenType,
                                            IO::GS_SourceLocation tokenLocation) {
        return GS_TokenBuilder::Create(tokenType,
                                       UString(),
                                       tokenLocation);
    }

    GS_TokenBuilder GS_TokenBuilder::Create(TokenType tokenType) {
        return GS_TokenBuilder::Create(tokenType,
                                       UString(),
                                       IO::GS_SourceLocation::Create());
    }

    GS_TokenBuilder GS_TokenBuilder::Create() {
        return GS_TokenBuilder::Create(TokenType::Unknown,
                                       UString(),
                                       IO::GS_SourceLocation::Create());
    }

    LRef<GS_TokenBuilder> GS_TokenBuilder::Type(TokenType tokenType) {
        _tokenType = tokenType;

        return *this;
    }

    LRef<GS_TokenBuilder> GS_TokenBuilder::Value(UString tokenValue) {
        _tokenValue = std::move(tokenValue);

        return *this;
    }

    LRef<GS_TokenBuilder> GS_TokenBuilder::Location(IO::GS_SourceLocation tokenLocation) {
        _tokenLocation = tokenLocation;

        return *this;
    }

    GS_Token GS_TokenBuilder::Token() {
        auto token = GS_Token::Create(_tokenType,
                                      _tokenValue,
                                      _tokenLocation);

        _tokenType = TokenType::Unknown;
        _tokenValue = UString();
        _tokenLocation = IO::GS_SourceLocation::Create();

        return token;
    }

    TokenType GS_TokenBuilder::GetTokenType() const {
        return _tokenType;
    }

    ConstLRef<UString> GS_TokenBuilder::GetTokenValue() const {
        return _tokenValue;
    }

    IO::GS_SourceLocation GS_TokenBuilder::GetTokenLocation() const {
        return _tokenLocation;
    }

}