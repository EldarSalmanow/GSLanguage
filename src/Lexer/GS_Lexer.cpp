#include <GS_Lexer.h>

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

        _buffer += symbol;

        if (ReservedSymbols.find(symbol) != ReservedSymbols.end()) {
            return {ReservedSymbols[symbol]};
        } else if (std::isalpha(symbol)) {
            String value;

            value += symbol;

            symbol = _textStream.getSymbol();

            std::istreambuf_iterator

            while (std::isalpha(symbol) && symbol != EOF && symbol != ' ' && symbol != '\n') {
                value += symbol;

                symbol = _textStream.getSymbol();
            }

            if (ReservedLetters.find(value) != ReservedLetters.end()) {
                return {ReservedLetters[value]};
            }

            return {TokenType::Identifier,  value};
        } else if (std::isdigit(symbol)) {
            String value;

            value += symbol;

            symbol = _textStream.getSymbol();

            while (std::isdigit(symbol) && symbol != EOF && symbol != ' ' && symbol != '\n') {
                value += symbol;

                symbol = _textStream.getSymbol();
            }

            return {TokenType::LiteralNumber,  value};
        }

        return {TokenType::Unknown};
    }

}