#include <GS_TokenStream.h>

#include <GS_Lexer.h>

namespace GSLanguageCompiler::Lexer {

    std::vector<std::pair<UString, TokenType>> ReservedWords = {
            {"var"_us, TokenType::KeywordVar},
            {"func"_us, TokenType::KeywordFunc}
    };

    std::vector<std::pair<USymbol, TokenType>> ReservedSymbols = {
            {U'(', TokenType::SymbolLeftParen},
            {U')', TokenType::SymbolRightParen},
            {U'{', TokenType::SymbolLeftBrace},
            {U'}', TokenType::SymbolRightBrace},

            {U':', TokenType::SymbolColon},
            {U',', TokenType::SymbolComma},

            {U'+', TokenType::SymbolPlus},
            {U'-', TokenType::SymbolMinus},
            {U'*', TokenType::SymbolStar},
            {U'/', TokenType::SymbolSlash},

            {U'=', TokenType::SymbolEq}
    };

    inline TokenType ReservedWordsType(ConstLRef<UString> string) {
        for (auto &pair : ReservedWords) {
            if (pair.first == string) {
                return pair.second;
            }
        }

        return TokenType::Unknown;
    }

    inline TokenType ReservedSymbolsType(ConstLRef<USymbol> symbol) {
        for (auto &pair : ReservedSymbols) {
            if (pair.first == symbol) {
                return pair.second;
            }
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

        while (token.GetType() != TokenType::EndOfFile) {
            tokens.emplace_back(token);

            token = GetToken();
        }

        tokens.emplace_back(GS_Token::Create(TokenType::EndOfFile));

        return tokens;
    }

    GS_TokenStream GS_Lexer::CreateStream() {
        return GS_TokenStream::Create(*this);
    }

    GS_Token GS_Lexer::GetToken() {
        while (CurrentSymbol().GetSymbol().IsWhitespace()) {
            NextSymbol();
        }

        auto type = ReservedSymbolsType(CurrentSymbol().GetSymbol());

        if (type != TokenType::Unknown) {
            NextSymbol();

            return GS_Token::Create(type);
        }

        if (CurrentSymbol().GetSymbol().IsIDStart()) {
            UString string;

            string += CurrentSymbol().GetSymbol();

            NextSymbol();

            while (CurrentSymbol().GetSymbol().IsIDContinue()) {
                string += CurrentSymbol().GetSymbol();

                NextSymbol();
            }

            if (ReservedWordsType(string) != TokenType::Unknown) {
                return GS_Token::Create(ReservedWordsType(string));
            }

            return GS_Token::Create(TokenType::Identifier, string);
        }

        if (CurrentSymbol().GetSymbol().IsDigit()) {
            UString string;

            string += CurrentSymbol().GetSymbol();

            NextSymbol();

            while (CurrentSymbol().GetSymbol().IsDigit()) {
                string += CurrentSymbol().GetSymbol();

                NextSymbol();
            }

            return GS_Token::Create(TokenType::LiteralNumber, string);
        }

        return GS_Token::Create(TokenType::EndOfFile);
    }

    IO::GS_Symbol GS_Lexer::CurrentSymbol() {
        return _stream.CurrentSymbol();
    }

    Void GS_Lexer::NextSymbol() {
        _stream.NextSymbol();
    }

}