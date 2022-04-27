#include <GS_Lexer.h>

namespace GSLanguageCompiler::Lexer {

    Vector<std::pair<UString, TokenType>> ReservedWords = {
            {"var"_us, TokenType::KeywordVar},
            {"func"_us, TokenType::KeywordFunc}
    };

    Vector<std::pair<USymbol, TokenType>> ReservedSymbols = {
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

    // TODO add saving information in token about location

    GS_Lexer::GS_Lexer(LRef<Reader::GS_TextStream> textStream)
            : _stream(textStream) {}

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

    GS_Token GS_Lexer::GetToken() {
        if (CurrentSymbol().IsWhitespace()) {
            NextSymbol();

            return GetToken();
//            return GS_Token::Create(TokenType::SymbolSpace); // TODO delete or modify
        }

        auto type = ReservedSymbolsType(CurrentSymbol());

        if (type != TokenType::Unknown) {
            NextSymbol();

            return GS_Token::Create(type);
        }

        if (CurrentSymbol().IsIDStart()) {
            UString string;

            string += CurrentSymbol();

            NextSymbol();

            while (CurrentSymbol().IsIDContinue()) {
                string += CurrentSymbol();

                NextSymbol();
            }

            if (ReservedWordsType(string) != TokenType::Unknown) {
                return GS_Token::Create(ReservedWordsType(string));
            }

            return GS_Token::Create(TokenType::Identifier, string);
        }

        if (CurrentSymbol().IsDigit()) {
            UString string;

            string += CurrentSymbol();

            NextSymbol();

            while (CurrentSymbol().IsDigit()) {
                string += CurrentSymbol();

                NextSymbol();
            }

            return GS_Token::Create(TokenType::LiteralNumber, string);
        }

        return GS_Token::Create(TokenType::EndOfFile);
    }

    USymbol GS_Lexer::CurrentSymbol() {
        return _stream.CurrentSymbol();
    }

    Void GS_Lexer::NextSymbol() {
        _stream.NextSymbol();
    }

}