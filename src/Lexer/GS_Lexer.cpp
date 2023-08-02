#include <GS_Lexer.h>

namespace GSLanguageCompiler::Lexer {

    GS_Lexer::GS_Lexer(LRef<Driver::GS_Session> session,
                       ConstLRef<IO::GS_Source> source)
            : _session(session),
              _messageQueue(IO::GS_MessageQueue::Create()),
              _cursor(source) {
        auto sourceHash = source.GetHash();

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

        auto tokenBuilder = GS_TokenBuilder::Create();

        SavePosition();

        // tokenizing whitespace
        if (symbol.IsWhitespace()) {
            tokenBuilder.Type(TokenType::SymbolSpace)
                        .Location(CurrentLocation());
        }

        // tokenizing word
        else if (symbol.IsIDStart()) {
            UString string;

            while (true) {
                string += CurrentSymbol();

                if (!LookupSymbol(1).IsIDContinue()) {
                    tokenBuilder.Location(CurrentLocation());

                    break;
                }

                NextSymbol();
            }

            if (string == "module") {
                tokenBuilder.Type(TokenType::KeywordModule);
            } else if (string == "import") {
                tokenBuilder.Type(TokenType::KeywordImport);
            } else if (string == "func") {
                tokenBuilder.Type(TokenType::KeywordFunc);
            } else if (string == "var") {
                tokenBuilder.Type(TokenType::KeywordVar);
            } else if (string == "if") {
                tokenBuilder.Type(TokenType::KeywordIf);
            } else if (string == "else") {
                tokenBuilder.Type(TokenType::KeywordElse);
            } else if (string == "for") {
                tokenBuilder.Type(TokenType::KeywordFor);
            } else if (string == "while") {
                tokenBuilder.Type(TokenType::KeywordWhile);
            } else if (string == "match") {
                tokenBuilder.Type(TokenType::KeywordMatch);
            } else if (string == "return") {
                tokenBuilder.Type(TokenType::KeywordReturn);
            } else if (string == "in") {
                tokenBuilder.Type(TokenType::KeywordIn);
            } else if (string == "as") {
                tokenBuilder.Type(TokenType::KeywordAs);
            } else if (string == "extern") {
                tokenBuilder.Type(TokenType::KeywordExtern);
            } else {
                tokenBuilder.Type(TokenType::Identifier)
                            .Value(string);
            }
        }

        // tokenizing reserved symbol
        else if (symbol == '(') {
            tokenBuilder.Type(TokenType::SymbolLeftParen)
                        .Location(CurrentLocation());
        } else if (symbol == ')') {
            tokenBuilder.Type(TokenType::SymbolRightParen)
                        .Location(CurrentLocation());
        } else if (symbol == '{') {
            tokenBuilder.Type(TokenType::SymbolLeftBrace)
                        .Location(CurrentLocation());
        } else if (symbol == '}') {
            tokenBuilder.Type(TokenType::SymbolRightBrace)
                        .Location(CurrentLocation());
        } else if (symbol == '[') {
            tokenBuilder.Type(TokenType::SymbolLeftBracket)
                        .Location(CurrentLocation());
        } else if (symbol == ']') {
            tokenBuilder.Type(TokenType::SymbolRightBracket)
                        .Location(CurrentLocation());
        } else if (symbol == ':') {
            tokenBuilder.Type(TokenType::SymbolColon)
                        .Location(CurrentLocation());
        } else if (symbol == ',') {
            tokenBuilder.Type(TokenType::SymbolComma)
                        .Location(CurrentLocation());
        } else if (symbol == '.') {
            if (LookupSymbol(1) == '.') {
                NextSymbol(); // skip '.'

                tokenBuilder.Type(TokenType::SymbolDotDot)
                            .Location(CurrentLocation());
            } else {
                tokenBuilder.Type(TokenType::SymbolDot)
                            .Location(CurrentLocation());
            }
        } else if (symbol == '+') {
            if (LookupSymbol(1) == '+') {
                NextSymbol(); // skip '+'

                tokenBuilder.Type(TokenType::SymbolPlusPlus)
                            .Location(CurrentLocation());
            } else if (LookupSymbol(1) == '=') {
                NextSymbol(); // skip '+'

                tokenBuilder.Type(TokenType::SymbolPlusEq)
                            .Location(CurrentLocation());
            } else {
                tokenBuilder.Type(TokenType::SymbolPlus)
                            .Location(CurrentLocation());
            }
        } else if (symbol == '-') {
            if (LookupSymbol(1) == '-') {
                NextSymbol(); // skip '-'

                tokenBuilder.Type(TokenType::SymbolMinusMinus)
                            .Location(CurrentLocation());
            } else if (LookupSymbol(1) == '=') {
                NextSymbol(); // skip '-'

                tokenBuilder.Type(TokenType::SymbolMinusEq)
                            .Location(CurrentLocation());
            } else {
                tokenBuilder.Type(TokenType::SymbolMinus)
                            .Location(CurrentLocation());
            }
        } else if (symbol == '*') {
            if (LookupSymbol(1) == '*') {
                NextSymbol(); // skip '*'

                tokenBuilder.Type(TokenType::SymbolStarStar)
                            .Location(CurrentLocation());
            } else if (LookupSymbol(1) == '=') {
                NextSymbol(); // skip '*'

                tokenBuilder.Type(TokenType::SymbolStarEq)
                            .Location(CurrentLocation());
            } else {
                tokenBuilder.Type(TokenType::SymbolStar)
                            .Location(CurrentLocation());
            }
        } else if (symbol == '/') {
            if (LookupSymbol(1) == '=') {
                NextSymbol(); // skip '/'

                tokenBuilder.Type(TokenType::SymbolSlashEq)
                            .Location(CurrentLocation());
            } else {
                tokenBuilder.Type(TokenType::SymbolSlash)
                            .Location(CurrentLocation());
            }
        } else if (symbol == '%') {
            if (LookupSymbol(1) == '=') {
                NextSymbol(); // skip '%'

                tokenBuilder.Type(TokenType::SymbolPercentEq)
                            .Location(CurrentLocation());
            } else {
                tokenBuilder.Type(TokenType::SymbolPercent)
                            .Location(CurrentLocation());
            }
        } else if (symbol == '^') {
            if (LookupSymbol(1) == '=') {
                NextSymbol(); // skip '^'

                tokenBuilder.Type(TokenType::SymbolCaretEq)
                            .Location(CurrentLocation());
            } else {
                tokenBuilder.Type(TokenType::SymbolCaret)
                            .Location(CurrentLocation());
            }
        } else if (symbol == '&') {
            if (LookupSymbol(1) == '&') {
                NextSymbol(); // skip '&'

                tokenBuilder.Type(TokenType::SymbolAndAnd)
                            .Location(CurrentLocation());
            } else if (LookupSymbol(1) == '=') {
                NextSymbol(); // skip '&'

                tokenBuilder.Type(TokenType::SymbolAndEq)
                            .Location(CurrentLocation());
            } else {
                tokenBuilder.Type(TokenType::SymbolAnd)
                            .Location(CurrentLocation());
            }
        } else if (symbol == '|') {
            if (LookupSymbol(1) == '|') {
                NextSymbol(); // skip '|'

                tokenBuilder.Type(TokenType::SymbolOrOr)
                            .Location(CurrentLocation());
            } else if (LookupSymbol(1) == '=') {
                NextSymbol(); // skip '|'

                tokenBuilder.Type(TokenType::SymbolOrEq)
                            .Location(CurrentLocation());
            } else {
                tokenBuilder.Type(TokenType::SymbolOr)
                            .Location(CurrentLocation());
            }
        } else if (symbol == '>') {
            if (LookupSymbol(1) == '>') {
                NextSymbol(); // skip '>'

                tokenBuilder.Type(TokenType::SymbolGtGt)
                            .Location(CurrentLocation());
            } else if (LookupSymbol(1) == '=') {
                NextSymbol(); // skip '>'

                tokenBuilder.Type(TokenType::SymbolGtEq)
                            .Location(CurrentLocation());
            } else {
                tokenBuilder.Type(TokenType::SymbolGt)
                            .Location(CurrentLocation());
            }
        } else if (symbol == '<') {
            if (LookupSymbol(1) == '<') {
                NextSymbol(); // skip '<'

                tokenBuilder.Type(TokenType::SymbolLtLt)
                            .Location(CurrentLocation());
            } else if (LookupSymbol(1) == '=') {
                NextSymbol(); // skip '<'

                tokenBuilder.Type(TokenType::SymbolLtEq)
                            .Location(CurrentLocation());
            } else {
                tokenBuilder.Type(TokenType::SymbolLt)
                            .Location(CurrentLocation());
            }
        } else if (symbol == '!') {
            if (LookupSymbol(1) == '=') {
                NextSymbol(); // skip '!'

                tokenBuilder.Type(TokenType::SymbolNotEq)
                            .Location(CurrentLocation());
            } else {
                tokenBuilder.Type(TokenType::SymbolNot)
                            .Location(CurrentLocation());
            }
        } else if (symbol == '=') {
            if (LookupSymbol(1) == '=') {
                NextSymbol(); // skip '='

                tokenBuilder.Type(TokenType::SymbolEqEq)
                            .Location(CurrentLocation());
            } else if (LookupSymbol(1) == '>') {
                NextSymbol(); // skip '='

                tokenBuilder.Type(TokenType::SymbolEqGt)
                            .Location(CurrentLocation());
            } else {
                tokenBuilder.Type(TokenType::SymbolEq)
                            .Location(CurrentLocation());
            }
        }

        // tokenizing digit literal
        else if (symbol.IsDigit()) {
            UString string;

            while (true) {
                string += CurrentSymbol();

                if (!LookupSymbol(1).IsDigit()) {
                    tokenBuilder.Type(TokenType::LiteralNumber)
                                .Value(string)
                                .Location(CurrentLocation());

                    break;
                }

                NextSymbol();
            }
        }

        // tokenizing symbol literal
        else if (symbol == '\'') {
            UString string;

            NextSymbol(); // skip '''

            string += CurrentSymbol();

            NextSymbol(); // skip '''

            if (CurrentSymbol() != '\'') {
                Driver::GlobalContext().Exit();
            }

            tokenBuilder.Type(TokenType::LiteralSymbol)
                        .Value(string)
                        .Location(CurrentLocation());
        }

        // tokenizing string literal
        else if (symbol == '\"') {
            UString string;

            NextSymbol(); // skip '"'

            while (true) {
                string += CurrentSymbol();

                if (LookupSymbol(1) == '\"') {
                    NextSymbol(); // skip '"'

                    tokenBuilder.Type(TokenType::LiteralString)
                                .Value(string)
                                .Location(CurrentLocation());

                    break;
                }

                NextSymbol();
            }
        }

        // end of file
        else if (IsEnd()) {
            tokenBuilder.Type(TokenType::EndOfFile)
                        .Location(CurrentLocation());
        }

        // unknown symbol
        else {
            UStringStream stringStream;

            stringStream << "Unknown symbol '"_us
                         << UString() + symbol // TODO
                         << "'!"_us;

            _messageQueue << _session.ErrorMessage()
                                     .Text(stringStream.String())
                                     .Message();

            tokenBuilder.Type(TokenType::Unknown)
                        //.Value(UString() + symbol) TODO
                        .Location(CurrentLocation());
        }

        NextSymbol();

        return tokenBuilder.Token();
    }

    USymbol GS_Lexer::CurrentSymbol() const {
        return *_cursor;
    }

    Void GS_Lexer::NextSymbol() {
        ++_cursor;
    }

    USymbol GS_Lexer::LookupSymbol(U64 index) const {
        return _cursor.LookupSymbol(index);
    }

    IO::GS_SourceLocation GS_Lexer::CurrentLocation() const {
        return _cursor.CurrentLocation();
    }

    Void GS_Lexer::SavePosition() {
        _cursor.SavePosition();
    }

    Bool GS_Lexer::IsEnd() const {
        return _cursor.IsEnd();
    }

}
