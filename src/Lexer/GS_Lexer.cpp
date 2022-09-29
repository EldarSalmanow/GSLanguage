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

    GS_Lexer::GS_Lexer(Driver::GSContextPtr context)
            : _context(std::move(context)),
              _content(UString()),
              _contentIterator(UString::Iterator()),
              _sourceHash(0),
              _currentPosition(1) {}

    GS_Lexer GS_Lexer::Create(Driver::GSContextPtr context) {
        return GS_Lexer(std::move(context));
    }

    GSTokenArray GS_Lexer::Tokenize(LRef<Driver::GS_CompilationUnit> compilationUnit) {
        _content = compilationUnit.GetSource()->GetSource();

        _contentIterator = _content.begin();

        _sourceHash = compilationUnit.GetSource()->GetHash();

        GSTokenArray tokens;

        auto token = GetToken();

        while (true) {
            tokens.emplace_back(token);

            // TODO EndOfFile or Unknown ?
            if (token.GetType() == TokenType::EndOfFile) {
                break;
            }

            token = GetToken();
        }

        _content = UString();

        _contentIterator = UString::Iterator();

        _sourceHash = 0;

        _currentPosition = 1;

        return tokens;
    }

    GS_Token GS_Lexer::GetToken() {
        // TODO update or remove
        while (CurrentSymbol().IsWhitespace()) {
            NextSymbol();

//            return GS_Token::Create(TokenType::SymbolSpace);
        } if (CurrentSymbol().IsIDStart()) {
            UString string;

            I64 startPosition = _currentPosition, endPosition = 0;

            while (true) {
                string += CurrentSymbol();

                NextSymbol();

                if (!CurrentSymbol().IsIDContinue()) {
                    endPosition = _currentPosition - 1;

                    break;
                }
            }

            if (ReservedWordType(string) != TokenType::Unknown) {
                return GS_Token::Create(ReservedWordType(string), IO::GS_SourceLocation::Create(_sourceHash, startPosition, endPosition));
            }

            return GS_Token::Create(TokenType::Identifier, string, IO::GS_SourceLocation::Create(_sourceHash, startPosition, endPosition));
        } else if (CurrentSymbol().IsDigit()) {
            UString string;

            I64 startPosition = _currentPosition, endPosition = 0;

            while (true) {
                string += CurrentSymbol();

                NextSymbol();

                if (!CurrentSymbol().IsDigit()) {
                    endPosition = _currentPosition - 1;

                    break;
                }
            }

            return GS_Token::Create(TokenType::LiteralNumber, string, IO::GS_SourceLocation::Create(_sourceHash, startPosition, endPosition));
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

            return GS_Token::Create(TokenType::LiteralNumber, string, IO::GS_SourceLocation::Create(_sourceHash, startPosition, endPosition));
        } else if (ReservedSymbolType(CurrentSymbol()) != TokenType::Unknown) {
            I64 position = _currentPosition;

            auto type = ReservedSymbolType(CurrentSymbol());

            NextSymbol();

            return GS_Token::Create(type, IO::GS_SourceLocation::Create(_sourceHash, position));
        }

        return GS_Token::Create(TokenType::EndOfFile, IO::GS_SourceLocation::Create(_sourceHash, _currentPosition)); // Unknown?
    }

    USymbol GS_Lexer::CurrentSymbol() {
        return *_contentIterator;
    }

    Void GS_Lexer::NextSymbol() {
        ++_contentIterator;

        ++_currentPosition;
    }

    Void GS_Lexer::PrevSymbol() {
        --_contentIterator;

        --_currentPosition;
    }

}
