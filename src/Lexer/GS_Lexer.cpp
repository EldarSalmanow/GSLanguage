#include <GS_TokenStream.h>

#include <GS_Lexer.h>

namespace GSLanguageCompiler::Lexer {

    inline TokenType ReservedWordsType(ConstLRef<UString> string) {
        if (string == "var"_us) {
            return TokenType::KeywordVar;
        } else if (string == "func"_us) {
            return TokenType::KeywordFunc;
        }

        return TokenType::Unknown;
    }

    inline TokenType ReservedSymbolsType(ConstLRef<USymbol> symbol) {
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

    GS_Lexer::GS_Lexer(LRef<IO::GS_TextStream> textStream)
            : _stream(textStream) {}

    GS_Lexer GS_Lexer::Create(LRef<IO::GS_TextStream> textStream) {
        return GS_Lexer(textStream);
    }

    GSTokenArray GS_Lexer::Tokenize() {
        GSTokenArray tokens;

        auto token = GetToken();

        while (true) {
            tokens.emplace_back(token);

            if (token.GetType() == TokenType::EndOfFile) {
                break;
            }

            token = GetToken();
        }

        return tokens;
    }

    GS_TokenStream GS_Lexer::CreateStream() {
        return GS_TokenStream::Create(*this);
    }

    GS_Token GS_Lexer::GetToken() {
        if (CurrentSymbolValue().IsWhitespace()) {
            auto location = CurrentSymbolLocation();

            NextSymbol();

            return GS_Token::Create(TokenType::SymbolSpace, GS_TokenLocation::Create(location));
        }

//        while (CurrentUSymbol().IsWhitespace()) {
//            NextSymbol();
//        }

        auto type = ReservedSymbolsType(CurrentSymbolValue());

        if (type != TokenType::Unknown) {
            auto location = CurrentSymbolLocation();

            NextSymbol();

            return GS_Token::Create(type, GS_TokenLocation::Create(location));
        }

        if (CurrentSymbolValue().IsIDStart()) {
            UString string;

            auto startLocation = CurrentSymbolLocation();

            string += CurrentSymbolValue();

            NextSymbol();

            auto endLocation = IO::GS_SymbolLocation::Create();

            while (true) {
                if (!CurrentSymbolValue().IsIDContinue()) {
                    endLocation = CurrentSymbolLocation();

                    break;
                }

                string += CurrentSymbolValue();

                NextSymbol();
            }

            if (ReservedWordsType(string) != TokenType::Unknown) {
                return GS_Token::Create(ReservedWordsType(string), GS_TokenLocation::Create(startLocation, endLocation));
            }

            return GS_Token::Create(TokenType::Identifier, string, GS_TokenLocation::Create(startLocation, endLocation));
        }

        if (CurrentSymbolValue().IsDigit()) {
            UString string;

            auto startLocation = CurrentSymbolLocation();

            string += CurrentSymbolValue();

            NextSymbol();

            auto endLocation = IO::GS_SymbolLocation::Create();

            while (true) {
                if (!CurrentSymbolValue().IsDigit()) {
                    endLocation = CurrentSymbolLocation();

                    break;
                }

                string += CurrentSymbolValue();

                NextSymbol();
            }

            return GS_Token::Create(TokenType::LiteralNumber, string, GS_TokenLocation::Create(startLocation, endLocation));
        }

        return GS_Token::Create(TokenType::EndOfFile);
    }

    IO::GS_Symbol GS_Lexer::CurrentSymbol() {
        return _stream.CurrentSymbol();
    }

    USymbol GS_Lexer::CurrentSymbolValue() {
        return CurrentSymbol().GetValue();
    }

    IO::GS_SymbolLocation GS_Lexer::CurrentSymbolLocation() {
        return CurrentSymbol().GetLocation();
    }

    Void GS_Lexer::NextSymbol() {
        _stream.NextSymbol();
    }

}