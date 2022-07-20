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

    GS_Lexer::GS_Lexer(UString content, Driver::GSCompilerSessionConfigPtr sessionConfig)
            : _content(std::move(content)), _contentIterator(_content.begin()), _sessionConfig(std::move(sessionConfig)) {}

    GS_Lexer GS_Lexer::Create(UString content, Driver::GSCompilerSessionConfigPtr sessionConfig) {
        return GS_Lexer(std::move(content), std::move(sessionConfig));
    }

    GSTokenArray GS_Lexer::Tokenize() {
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

        return tokens;
    }

    GS_Token GS_Lexer::GetToken() {
        // TODO update or remove
        while (CurrentSymbol().IsWhitespace()) {
            NextSymbol();

//            return GS_Token::Create(TokenType::SymbolSpace);
        } if (CurrentSymbol().IsIDStart()) {
            UString string;

            while (true) {
                string += CurrentSymbol();

                NextSymbol();

                if (!CurrentSymbol().IsIDContinue()) {
                    break;
                }
            }

            if (ReservedWordType(string) != TokenType::Unknown) {
                return GS_Token::Create(ReservedWordType(string));
            }

            return GS_Token::Create(TokenType::Identifier, string);
        } else if (CurrentSymbol().IsDigit()) {
            UString string;

            while (true) {
                string += CurrentSymbol();

                NextSymbol();

                if (!CurrentSymbol().IsDigit()) {
                    break;
                }
            }

            return GS_Token::Create(TokenType::LiteralNumber, string);
        } else if (CurrentSymbol() == '\"') {
            UString string;

            while (true) {
                string += CurrentSymbol();

                NextSymbol();

                if (CurrentSymbol() == '\"') {
                    NextSymbol();

                    break;
                }
            }

            return GS_Token::Create(TokenType::LiteralNumber, string);
        } else if (ReservedSymbolType(CurrentSymbol()) != TokenType::Unknown) {
            auto type = ReservedSymbolType(CurrentSymbol());

            NextSymbol();

            return GS_Token::Create(type);
        }

        return GS_Token::Create(TokenType::EndOfFile); // Unknown?
    }

    USymbol GS_Lexer::CurrentSymbol() {
        return *_contentIterator;
    }

    Void GS_Lexer::NextSymbol() {
        ++_contentIterator;
    }

    Void GS_Lexer::PrevSymbol() {
        --_contentIterator;
    }

}
