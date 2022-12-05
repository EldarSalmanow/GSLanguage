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

    GS_TokensBuffer::GS_TokensBuffer(GSTokenArray tokens)
            : _tokens(std::move(tokens)) {}

    GS_TokensBuffer GS_TokensBuffer::Create(GSTokenArray tokens) {
        return GS_TokensBuffer(std::move(tokens));
    }

    GS_TokensBuffer::Iterator GS_TokensBuffer::begin() {
        return _tokens.begin();
    }

    GS_TokensBuffer::Iterator GS_TokensBuffer::end() {
        return _tokens.end();
    }

    GS_TokensBuffer::ConstIterator GS_TokensBuffer::begin() const {
        return _tokens.begin();
    }

    GS_TokensBuffer::ConstIterator GS_TokensBuffer::end() const {
        return _tokens.end();
    }

    GS_TokensBuffer::ConstIterator GS_TokensBuffer::cbegin() const {
        return _tokens.cbegin();
    }

    GS_TokensBuffer::ConstIterator GS_TokensBuffer::cend() const {
        return _tokens.cend();
    }

    ConstLRef<GSTokenArray> GS_TokensBuffer::GetTokens() const {
        return _tokens;
    }

}