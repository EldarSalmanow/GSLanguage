#include <GS_Lexer.h>

#include <utility>

namespace GSLanguageCompiler::Lexer {

    Map<Reader::SymbolT, TokenType> ReservedSymbols = {
            {EOF,   TokenType::EndOfFile},
            {'\n', TokenType::NewLine},
            {' ',  TokenType::SymbolSpace},

            {'(',  TokenType::SymbolLeftParen},
            {')',  TokenType::SymbolRightParen},
            {'{',  TokenType::SymbolLeftBrace},
            {'}',  TokenType::SymbolRightBrace},

            {'\"', TokenType::SymbolDoubleQuotes},
            {':',  TokenType::SymbolColon},
            {',',  TokenType::SymbolComma},

            {'+',  TokenType::SymbolPlus},
            {'-',  TokenType::SymbolMinus},
            {'*',  TokenType::SymbolStar},
            {'/',  TokenType::SymbolSlash},
            {'=' , TokenType::SymbolEq}
    };

    Map<String, TokenType> ReservedLetters = {
            {"var",  TokenType::KeywordVar},
            {"func", TokenType::KeywordFunc},
    };

    GS_Lexer::GS_Lexer(Reader::GS_TextStream textStream)
            : _textStream(textStream) {}

    GS_Token GS_Lexer::getToken() {
        auto symbol = _textStream.getSymbol();

        if (ReservedSymbols.find(symbol) != ReservedSymbols.end()) {
            return GS_Token(ReservedSymbols[symbol]);
        } else if (std::isalpha(symbol)) {
            String value;

            while (std::isalpha(symbol) && symbol != EOF && symbol != ' ' && symbol != '\n') {
                value += symbol;

                symbol = _textStream.getSymbol();
            }

            _textStream.prevSymbol();

            if (ReservedLetters.find(value) != ReservedLetters.end()) {
                return GS_Token(ReservedLetters[value]);
            }

            return GS_Token(TokenType::Identifier,  value);
        } else if (std::isdigit(symbol)) {
            String value;

            while (std::isdigit(symbol) && symbol != EOF && symbol != ' ' && symbol != '\n') {
                value += symbol;

                symbol = _textStream.getSymbol();
            }

            _textStream.prevSymbol();

            return GS_Token(TokenType::LiteralNumber,  value);
        }

        return {};
    }

}