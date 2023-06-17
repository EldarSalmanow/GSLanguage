#include <GS_Token.h>

namespace GSLanguageCompiler::Lexer {

    GS_Token::GS_Token(TokenType type,
                       UString value,
                       IO::GS_SourceRange locationRange)
            : _type(type),
              _value(std::move(value)),
              _locationRange(locationRange) {}

    GS_Token GS_Token::Create(TokenType type,
                              UString value,
                              IO::GS_SourceRange locationRange) {
        return GS_Token(type,
                        std::move(value),
                        locationRange);
    }

    GS_Token GS_Token::Create(TokenType type,
                              UString value) {
        return GS_Token::Create(type,
                                std::move(value),
                                IO::GS_SourceRange::Create());
    }

    GS_Token GS_Token::Create(TokenType type,
                              IO::GS_SourceRange locationRange) {
        return GS_Token::Create(type,
                                UString(),
                                locationRange);
    }

    GS_Token GS_Token::Create(TokenType type) {
        return GS_Token::Create(type,
                                UString(),
                                IO::GS_SourceRange::Create());
    }

    GS_Token GS_Token::Create() {
        return GS_Token::Create(TokenType::Unknown,
                                UString(),
                                IO::GS_SourceRange::Create());
    }

    TokenType GS_Token::GetType() const {
        return _type;
    }

    ConstLRef<UString> GS_Token::GetValue() const {
        return _value;
    }

    IO::GS_SourceRange GS_Token::GetLocationRange() const {
        return _locationRange;
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

}