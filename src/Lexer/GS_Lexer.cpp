#include <GS_Lexer.h>

namespace GSLanguageCompiler::Lexer {

    inline TokenType ReservedWordType(ConstLRef<UString> string) {
        if (string == "var"_us) {
            return TokenType::KeywordVar;
        } else if (string == "func"_us) {
            return TokenType::KeywordFunc;
        }

        return TokenType::Unknown;
    }

    inline TokenType ReservedSymbolType(ConstLRef<USymbol> symbol) {
        if (symbol == '(') {
            return TokenType::SymbolLeftParen;
        } else if (symbol == ')') {
            return TokenType::SymbolRightParen;
        } else if (symbol == '{') {
            return TokenType::SymbolLeftBrace;
        } else if (symbol == '}') {
            return TokenType::SymbolRightBrace;
        } else if (symbol == '[') {
            return TokenType::SymbolLeftBracket;
        } else if (symbol == ']') {
            return TokenType::SymbolRightBracket;
        } else if (symbol == ':') {
            return TokenType::SymbolColon;
        } else if (symbol == ',') {
            return TokenType::SymbolComma;
        } else if (symbol == '+') {
            return TokenType::SymbolPlus;
        } else if (symbol == '-') {
            return TokenType::SymbolMinus;
        } else if (symbol == '*') {
            return TokenType::SymbolStar;
        } else if (symbol == '/') {
            return TokenType::SymbolSlash;
        } else if (symbol == '=') {
            return TokenType::SymbolEq;
        }

        return TokenType::Unknown;
    }

    GS_Lexer::GS_Lexer(LRef<Driver::GS_Session> session,
                       ConstLRef<IO::GS_Source> source)
            : _session(session),
              _messageQueue(IO::GS_MessageQueue::Create()),
              _source(source),
              _sourceIterator(_source.cbegin()),
              _currentPosition(1) {
        auto sourceHash = _source.GetHash();

        auto optionalSource = _session.GetSource(sourceHash);

        if (!optionalSource.has_value()) {
            Driver::GlobalContext().Exit();
        }
    }

    GS_Lexer GS_Lexer::Create(LRef<Driver::GS_Session> session,
                              ConstLRef<IO::GS_Source> source) {
        return GS_Lexer(session, source);
    }

    GS_TokenBuffer GS_Lexer::Run(LRef<Driver::GS_Session> session,
                                  ConstLRef<IO::GS_Source> source) {
        auto lexer = GS_Lexer::Create(session, source);

        auto tokensBuffer = lexer.Tokenize();

        return tokensBuffer;
    }

    GS_TokenBuffer GS_Lexer::Tokenize() {
        GSTokenArray tokens;

        auto token = GetToken();

        while (true) {
            if (token.GetType() == TokenType::SymbolSpace) {
                token = GetToken();

                continue;
            }

            tokens.emplace_back(token);

            if (token.GetType() == TokenType::EndOfFile) {
                break;
            }

            token = GetToken();
        }

        _messageQueue.Flush(_session.Out());

        auto tokenBuffer = GS_TokenBuffer::Create(std::move(tokens));

        return tokenBuffer;
    }

    GS_Token GS_Lexer::GetToken() {
        auto symbol = CurrentSymbol();

        if (symbol.IsWhitespace()) {
            // tokenizing whitespace

            return TokenizeWhitespace();
        } else if (symbol.IsIDStart()) {
            // tokenizing word

            return TokenizeWord();
        } else if (ReservedSymbolType(symbol) != TokenType::Unknown) {
            // tokenizing reserved symbol

            return TokenizeReservedSymbol();
        } else if (symbol.IsDigit()) {
            // tokenizing digit literal

            return TokenizeDigit();
        } else if (symbol == '\'') {
            // tokenizing symbol literal

            return TokenizeSymbol();
        } else if (symbol == '\"') {
            // tokenizing string literal

            return TokenizeString();
        } else if (_sourceIterator == _source.cend()) {
            // end of file

            return GS_Token::Create(TokenType::EndOfFile,
                                    IO::GSByteSourceRange::Create(CurrentLocation(),
                                                                  CurrentLocation()));
        }

        // unknown symbol

        _messageQueue << _session.ErrorMessage()
                                 .Text("Unknown symbol '"_us + symbol + "'!"_us)
                                 .Message();

        return GS_Token::Create(TokenType::Unknown,
                                IO::GSByteSourceRange::Create(CurrentLocation(),
                                                              CurrentLocation()));
    }

    GS_Token GS_Lexer::TokenizeWhitespace() {
        if (CurrentSymbol().IsWhitespace()) {
            auto startPosition = CurrentLocation(),
                 endPosition = CurrentLocation();

            NextSymbol();

            return GS_Token::Create(TokenType::SymbolSpace,
                                    IO::GSByteSourceRange::Create(startPosition,
                                                                  endPosition));
        }

        return GS_Token::Create();
    }

    GS_Token GS_Lexer::TokenizeWord() {
        if (CurrentSymbol().IsIDStart()) {
            UString string;

            auto startPosition = CurrentLocation(),
                 endPosition = Location();

            while (true) {
                string += CurrentSymbol();

                NextSymbol();

                if (!CurrentSymbol().IsIDContinue()) {
                    endPosition = PrevLocation();

                    break;
                }
            }

            if (ReservedWordType(string) != TokenType::Unknown) {
                return GS_Token::Create(ReservedWordType(string),
                                        IO::GSByteSourceRange::Create(startPosition,
                                                                      endPosition));
            }

            return GS_Token::Create(TokenType::Identifier,
                                    string,
                                    IO::GSByteSourceRange::Create(startPosition,
                                                                  endPosition));
        }

        return GS_Token::Create();
    }

    GS_Token GS_Lexer::TokenizeReservedSymbol() {
        if (ReservedSymbolType(CurrentSymbol()) != TokenType::Unknown) {
            auto startPosition = CurrentLocation(),
                 endPosition = CurrentLocation();

            auto type = ReservedSymbolType(CurrentSymbol());

            NextSymbol();

            return GS_Token::Create(type,
                                    IO::GSByteSourceRange::Create(startPosition,
                                                                  endPosition));
        }

        return GS_Token::Create();
    }

    GS_Token GS_Lexer::TokenizeDigit() {
        if (CurrentSymbol().IsDigit()) {
            UString string;

            auto startPosition = CurrentLocation(),
                 endPosition = Location();

            while (true) {
                string += CurrentSymbol();

                NextSymbol();

                if (!CurrentSymbol().IsDigit()) {
                    endPosition = PrevLocation();

                    break;
                }
            }

            return GS_Token::Create(TokenType::LiteralNumber,
                                    string,
                                    IO::GSByteSourceRange::Create(startPosition,
                                                                  endPosition));
        }

        return GS_Token::Create();
    }

    GS_Token GS_Lexer::TokenizeSymbol() {
        if (CurrentSymbol() == '\'') {
            UString string;

            auto startPosition = CurrentLocation(),
                 endPosition = Location();

            string += CurrentSymbol();

            NextSymbol();

            if (CurrentSymbol() != '\'') {
                Driver::GlobalContext().Exit();
            }

            NextSymbol();

            endPosition = PrevLocation();

            return GS_Token::Create(TokenType::LiteralSymbol,
                                    string,
                                    IO::GSByteSourceRange::Create(startPosition,
                                                                  endPosition));
        }

        return GS_Token::Create();
    }

    GS_Token GS_Lexer::TokenizeString() {
        if (CurrentSymbol() == '\"') {
            UString string;

            auto startPosition = CurrentLocation(),
                 endPosition = Location();

            NextSymbol();

            while (true) {
                string += CurrentSymbol();

                NextSymbol();

                if (CurrentSymbol() == '\"') {
                    NextSymbol();

                    endPosition = PrevLocation();

                    break;
                }
            }

            return GS_Token::Create(TokenType::LiteralString,
                                    string,
                                    IO::GSByteSourceRange::Create(startPosition,
                                                                  endPosition));
        }

        return GS_Token::Create();
    }

    USymbol GS_Lexer::CurrentSymbol() {
        return *_sourceIterator;
    }

    Void GS_Lexer::PrevSymbol() {
        --_sourceIterator;

        --_currentPosition;
    }

    Void GS_Lexer::NextSymbol() {
        ++_sourceIterator;

        ++_currentPosition;
    }

    IO::GS_ByteSourceLocation GS_Lexer::CurrentLocation() const {
        return Location(_currentPosition);
    }

    IO::GS_ByteSourceLocation GS_Lexer::PrevLocation() const {
        return Location(_currentPosition - 1);
    }

    IO::GS_ByteSourceLocation GS_Lexer::NextLocation() const {
        return Location(_currentPosition + 1);
    }

    IO::GS_ByteSourceLocation GS_Lexer::Location(I64 position) const {
        return IO::GS_ByteSourceLocation::Create(position,
                                                 _source.GetHash());
    }

    IO::GS_ByteSourceLocation GS_Lexer::Location() const {
        return IO::GS_ByteSourceLocation::Create();
    }

}
