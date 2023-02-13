#include <GS_Lexer.h>

namespace GSLanguageCompiler::Lexer {

    class SymbolRule {
    public:

        static Bool IsValid(USymbol symbol) {
            return false;
        }
    };

    class WhitespaceSymbolRule : public SymbolRule {
    public:

        static Bool IsValid(USymbol symbol) {
            return symbol.IsWhitespace();
        }
    };

    class IDStartSymbolRule : public SymbolRule {
    public:

        static Bool IsValid(USymbol symbol) {
            return symbol.IsIDStart();
        }
    };

    class IDContinueSymbolRule : public SymbolRule {
    public:

        static Bool IsValid(USymbol symbol) {
            return symbol.IsIDContinue();
        }
    };

    class DigitSymbolRule : public SymbolRule {
    public:

        static Bool IsValid(USymbol symbol) {
            return symbol.IsDigit();
        }
    };

    class ReservedSymbolRule : public SymbolRule {
    public:

        static Bool IsValid(USymbol symbol) {
            if (symbol == '('
             || symbol == ')'
             || symbol == '{'
             || symbol == '}'
             || symbol == '['
             || symbol == ']'

             || symbol == ':'
             || symbol == ','

             || symbol == '+'
             || symbol == '-'
             || symbol == '*'
             || symbol == '/'

             || symbol == '=') {
                return true;
            }

            return false;
        }
    };

    template<typename T>
    requires(std::is_base_of_v<SymbolRule, T>)
    Bool ValidSymbolRule(USymbol symbol) {
        return T::IsValid(std::move(symbol));
    }

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
              _messages(IO::GSMessageArray()),
              _source(source),
              _sourceIterator(_source.cbegin()),
              _currentPosition(1) {}

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

        auto tokensBuffer = GS_TokenBuffer::Create(std::move(tokens));

        for (auto &message : _messages) {
            _session.Out() << message;
        }

        return tokensBuffer;
    }

    GS_Token GS_Lexer::GetToken() {
        if (ValidSymbolRule<WhitespaceSymbolRule>(CurrentSymbol())) {
            auto startPosition = IO::GS_ByteSourceLocation::Create(_currentPosition, _source.GetHash());
            auto endPosition = IO::GS_ByteSourceLocation::Create(_currentPosition, _source.GetHash());

            NextSymbol();

            return GS_Token::Create(TokenType::SymbolSpace, IO::GSByteSourceRange::Create(startPosition, endPosition));
        } else if (ValidSymbolRule<IDStartSymbolRule>(CurrentSymbol())) {
            UString string;

            I64 startPosition = _currentPosition, endPosition = 0;

            while (true) {
                string += CurrentSymbol();

                NextSymbol();

                if (!ValidSymbolRule<IDStartSymbolRule>(CurrentSymbol())) {
                    endPosition = _currentPosition - 1;

                    break;
                }
            }

            if (ReservedWordType(string) != TokenType::Unknown) {
                return GS_Token::Create(ReservedWordType(string), IO::GS_SourceLocation::Create(_source.GetHash(), startPosition, endPosition));
            }

            return GS_Token::Create(TokenType::Identifier, string, IO::GS_SourceLocation::Create(_source.GetHash(), startPosition, endPosition));
        } else if (ValidSymbolRule<DigitSymbolRule>(CurrentSymbol())) {
            UString string;

            I64 startPosition = _currentPosition, endPosition = 0;

            while (true) {
                string += CurrentSymbol();

                NextSymbol();

                if (!ValidSymbolRule<DigitSymbolRule>(CurrentSymbol())) {
                    endPosition = _currentPosition - 1;

                    break;
                }
            }

            return GS_Token::Create(TokenType::LiteralNumber, string, IO::GS_SourceLocation::Create(_source.GetHash(), startPosition, endPosition));
        } else if (CurrentSymbol() == '\'') {
            UString string;

            I64 startPosition = _currentPosition, endPosition = 0;

            string += CurrentSymbol();

            NextSymbol();

            if (CurrentSymbol() != '\'') {
                // todo ?

//                LocatedMessage("Symbol must be a one symbol!",
//                               IO::MessageLevel::Error,
//                               IO::GS_SourceLocation::Create(_source.GetHash(), startPosition, startPosition));

                // ?
            }

            NextSymbol();

            endPosition = _currentPosition - 1;

            return GS_Token::Create(TokenType::LiteralSymbol, string, IO::GS_SourceLocation::Create(_source.GetHash(), startPosition, endPosition));
        } else if (CurrentSymbol() == '\"') {
            UString string;

            I64 startPosition = _currentPosition, endPosition = 0;

            while (true) {
                string += CurrentSymbol();

                NextSymbol();

                if (CurrentSymbol() == '\"') {
                    NextSymbol();

                    endPosition = _currentPosition - 1;

                    break;
                }
            }

            return GS_Token::Create(TokenType::LiteralNumber, string, IO::GS_SourceLocation::Create(_source.GetHash(), startPosition, endPosition));
        } else if (ValidSymbolRule<ReservedSymbolRule>(CurrentSymbol())) {
            I64 startPosition = _currentPosition, endPosition = _currentPosition;

            auto type = ReservedSymbolType(CurrentSymbol());

            NextSymbol();

            return GS_Token::Create(type, IO::GS_SourceLocation::Create(_source.GetHash(), startPosition, endPosition));
        }

        // TODO add detecting end of file or unknown symbol

        return GS_Token::Create(TokenType::EndOfFile, IO::GS_SourceLocation::Create(_source.GetHash(), _currentPosition, _currentPosition));
    }

    USymbol GS_Lexer::CurrentSymbol() {
        return *_sourceIterator;
    }

    Void GS_Lexer::NextSymbol() {
        ++_sourceIterator;

        ++_currentPosition;
    }

    Void GS_Lexer::PrevSymbol() {
        --_sourceIterator;

        --_currentPosition;
    }

}
