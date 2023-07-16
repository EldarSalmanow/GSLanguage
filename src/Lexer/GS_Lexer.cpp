#include <GS_Lexer.h>

namespace GSLanguageCompiler::Lexer {

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
        } else if (symbol == '.') {
            return TokenType::SymbolDot;
        } else if (symbol == '+') {
            return TokenType::SymbolPlus;
        } else if (symbol == '-') {
            return TokenType::SymbolMinus;
        } else if (symbol == '*') {
            return TokenType::SymbolStar;
        } else if (symbol == '/') {
            return TokenType::SymbolSlash;
        } else if (symbol == '%') {
            return TokenType::SymbolPercent;
        } else if (symbol == '&') {
            return TokenType::SymbolAnd;
        } else if (symbol == '|') {
            return TokenType::SymbolOr;
        } else if (symbol == '^') {
            return TokenType::SymbolCaret;
        } else if (symbol == '>') {
            return TokenType::SymbolGt;
        } else if (symbol == '<') {
            return TokenType::SymbolLt;
        } else if (symbol == '!') {
            return TokenType::SymbolNot;
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

            auto startPosition = CurrentLocation(),
                 endPosition = CurrentLocation();

            NextSymbol();

            return GS_Token::Create(TokenType::SymbolSpace,
                                    IO::GS_SourceRange::Create(startPosition,
                                                               endPosition));
        } else if (symbol.IsIDStart()) {
            // tokenizing word

            UString string;

            auto startPosition = CurrentLocation(),
                 endPosition = CurrentLocation();

            while (true) {
                string += CurrentSymbol();

                endPosition = CurrentLocation();

                NextSymbol();

                if (!CurrentSymbol().IsIDContinue()) {
                    break;
                }
            }

            TokenType tokenType = TokenType::Identifier;

            if (string == "module") {
                tokenType = TokenType::KeywordModule;
            } else if (string == "import") {
                tokenType = TokenType::KeywordImport;
            } else if (string == "func") {
                tokenType = TokenType::KeywordFunc;
            } else if (string == "var") {
                tokenType = TokenType::KeywordVar;
            } else if (string == "if") {
                tokenType = TokenType::KeywordIf;
            } else if (string == "else") {
                tokenType = TokenType::KeywordElse;
            } else if (string == "for") {
                tokenType = TokenType::KeywordFor;
            } else if (string == "while") {
                tokenType = TokenType::KeywordWhile;
            } else if (string == "match") {
                tokenType = TokenType::KeywordMatch;
            } else if (string == "return") {
                tokenType = TokenType::KeywordReturn;
            } else if (string == "in") {
                tokenType = TokenType::KeywordIn;
            } else if (string == "as") {
                tokenType = TokenType::KeywordAs;
            } else if (string == "extern") {
                tokenType = TokenType::KeywordExtern;
            }

            if (tokenType == TokenType::Identifier) {
                return GS_Token::Create(TokenType::Identifier,
                                        string,
                                        IO::GS_SourceRange::Create(startPosition,
                                                                   endPosition));
            }

            return GS_Token::Create(tokenType,
                                    IO::GS_SourceRange::Create(startPosition,
                                                               endPosition));
        } else if (ReservedSymbolType(symbol) != TokenType::Unknown) {
            // tokenizing reserved symbol

            auto startPosition = CurrentLocation(),
                 endPosition = CurrentLocation();

            NextSymbol();

            auto type = TokenType::Unknown;

            if (symbol == '(') {
                type = TokenType::SymbolLeftParen;
            } else if (symbol == ')') {
                type = TokenType::SymbolRightParen;
            } else if (symbol == '{') {
                type = TokenType::SymbolLeftBrace;
            } else if (symbol == '}') {
                type = TokenType::SymbolRightBrace;
            } else if (symbol == '[') {
                type = TokenType::SymbolLeftBracket;
            } else if (symbol == ']') {
                type = TokenType::SymbolRightBracket;
            } else if (symbol == ':') {
                type = TokenType::SymbolColon;
            } else if (symbol == ',') {
                type = TokenType::SymbolComma;
            } else if (symbol == '.') {
                NextSymbol();

                if (CurrentSymbol() == '.') {
                    type = TokenType::SymbolDotDot;

                    endPosition = CurrentLocation();
                } else {
                    type = TokenType::SymbolDot;
                }
            } else if (symbol == '+') {
                NextSymbol();

                if (CurrentSymbol() == '+') {
                    type = TokenType::SymbolPlusPlus;

                    endPosition = CurrentLocation();
                } else if (CurrentSymbol() == '=') {
                    type = TokenType::SymbolPlusEq;

                    endPosition = CurrentLocation();
                } else {
                    type = TokenType::SymbolPlus;
                }
            } else if (symbol == '-') {
                NextSymbol();

                if (CurrentSymbol() == '-') {
                    type = TokenType::SymbolMinusMinus;

                    endPosition = CurrentLocation();
                } else if (CurrentSymbol() == '=') {
                    type = TokenType::SymbolMinusEq;

                    endPosition = CurrentLocation();
                } else {
                    type = TokenType::SymbolMinus;
                }
            } else if (symbol == '*') {
                NextSymbol();

                if (CurrentSymbol() == '*') {
                    type = TokenType::SymbolStarStar;

                    endPosition = CurrentLocation();
                } else if (CurrentSymbol() == '=') {
                    type = TokenType::SymbolStarEq;

                    endPosition = CurrentLocation();
                } else {
                    type = TokenType::SymbolStar;
                }
            } else if (symbol == '/') {
                NextSymbol();

                if (CurrentSymbol() == '=') {
                    type = TokenType::SymbolSlashEq;

                    endPosition = CurrentLocation();
                } else {
                    type = TokenType::SymbolSlash;
                }
            } else if (symbol == '%') {
                NextSymbol();

                if (CurrentSymbol() == '=') {
                    type = TokenType::SymbolPercentEq;

                    endPosition = CurrentLocation();
                } else {
                    type = TokenType::SymbolPercent;
                }
            } else if (symbol == '^') {
                NextSymbol();

                if (CurrentSymbol() == '=') {
                    type = TokenType::SymbolCaretEq;

                    endPosition = CurrentLocation();
                } else {
                    type = TokenType::SymbolCaret;
                }
            } else if (symbol == '&') {
                NextSymbol();

                if (CurrentSymbol() == '&') {
                    type = TokenType::SymbolAndAnd;

                    endPosition = CurrentLocation();
                } else if (CurrentSymbol() == '=') {
                    type = TokenType::SymbolAndEq;

                    endPosition = CurrentLocation();
                } else {
                    type = TokenType::SymbolAnd;
                }
            } else if (symbol == '|') {
                NextSymbol();

                if (CurrentSymbol() == '|') {
                    type = TokenType::SymbolOrOr;

                    endPosition = CurrentLocation();
                } else if (CurrentSymbol() == '=') {
                    type = TokenType::SymbolOrEq;

                    endPosition = CurrentLocation();
                } else {
                    type = TokenType::SymbolOr;
                }
            } else if (symbol == '>') {
                NextSymbol();

                if (CurrentSymbol() == '>') {
                    type = TokenType::SymbolGtGt;

                    endPosition = CurrentLocation();
                } else if (CurrentSymbol() == '=') {
                    type = TokenType::SymbolGtEq;

                    endPosition = CurrentLocation();
                } else {
                    type = TokenType::SymbolGt;
                }
            } else if (symbol == '<') {
                NextSymbol();

                if (CurrentSymbol() == '<') {
                    type = TokenType::SymbolLtLt;

                    endPosition = CurrentLocation();
                } else if (CurrentSymbol() == '=') {
                    type = TokenType::SymbolLtEq;

                    endPosition = CurrentLocation();
                } else {
                    type = TokenType::SymbolLt;
                }
            } else if (symbol == '!') {
                NextSymbol();

                if (CurrentSymbol() == '=') {
                    type = TokenType::SymbolNotEq;

                    endPosition = CurrentLocation();
                } else {
                    type = TokenType::SymbolNot;
                }
            } else if (symbol == '=') {
                NextSymbol();

                if (CurrentSymbol() == '=') {
                    type = TokenType::SymbolEqEq;

                    endPosition = CurrentLocation();
                } else if (CurrentSymbol() == '>') {
                    type = TokenType::SymbolEqGt;

                    endPosition = CurrentLocation();
                } else {
                    type = TokenType::SymbolEq;
                }
            }

            return GS_Token::Create(type,
                                    IO::GS_SourceRange::Create(startPosition,
                                                               endPosition));
        } else if (symbol.IsDigit()) {
            // tokenizing digit literal

            UString string;

            auto startPosition = CurrentLocation(),
                 endPosition = CurrentLocation();

            while (true) {
                string += CurrentSymbol();

                endPosition = CurrentLocation();

                NextSymbol();

                if (!CurrentSymbol().IsDigit()) {
                    break;
                }
            }

            return GS_Token::Create(TokenType::LiteralNumber,
                                    string,
                                    IO::GS_SourceRange::Create(startPosition,
                                                               endPosition));
        } else if (symbol == '\'') {
            // tokenizing symbol literal

            UString string;

            auto startPosition = CurrentLocation(),
                 endPosition = CurrentLocation();

            NextSymbol();

            string += CurrentSymbol();

            NextSymbol();

            if (CurrentSymbol() != '\'') {
                Driver::GlobalContext().Exit();
            }

            endPosition = CurrentLocation();

            NextSymbol();

            return GS_Token::Create(TokenType::LiteralSymbol,
                                    string,
                                    IO::GS_SourceRange::Create(startPosition,
                                                               endPosition));
        } else if (symbol == '\"') {
            // tokenizing string literal

            UString string;

            auto startPosition = CurrentLocation(),
                 endPosition = CurrentLocation();

            NextSymbol();

            while (true) {
                string += CurrentSymbol();

                NextSymbol();

                if (CurrentSymbol() == '\"') {
                    NextSymbol();

                    endPosition = CurrentLocation();

                    break;
                }
            }

            return GS_Token::Create(TokenType::LiteralString,
                                    string,
                                    IO::GS_SourceRange::Create(startPosition,
                                                               endPosition));
        } else if (_sourceIterator == _source.cend()) {
            // end of file

            return GS_Token::Create(TokenType::EndOfFile,
                                    IO::GS_SourceRange::Create(CurrentLocation(),
                                                               CurrentLocation()));
        }

        // unknown symbol

        _messageQueue << _session.ErrorMessage()
                                 .Text("Unknown symbol '"_us + symbol + "'!"_us)
                                 .Message();

        return GS_Token::Create(TokenType::Unknown,
                                IO::GS_SourceRange::Create(CurrentLocation(),
                                                           CurrentLocation()));
    }

    USymbol GS_Lexer::CurrentSymbol() {
        return *_sourceIterator;
    }

    Void GS_Lexer::NextSymbol() {
        ++_sourceIterator;

        ++_currentPosition;
    }

    IO::GS_SourceLocation GS_Lexer::CurrentLocation() const {
        return IO::GS_SourceLocation::Create(_currentPosition,
                                             _source.GetHash());
    }

}
