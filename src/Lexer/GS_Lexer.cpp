#include <GS_Lexer.h>

namespace GSLanguageCompiler::Lexer {

    inline auto eof() {
        return std::char_traits<Reader::SymbolT>::eof();
    }

    inline TokenType reservedSymbolType(Reader::SymbolT symbol) {
        if (symbol == '(') {
            return TokenType::SymbolLeftParen;
        } else if (symbol == ')') {
            return TokenType::SymbolRightParen;
        } else if (symbol == '{') {
            return TokenType::SymbolLeftBrace;
        } else if (symbol == '}') {
            return TokenType::SymbolRightBrace;
        } else if (symbol == '\"') {
            return TokenType::SymbolDoubleQuotes;
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

    inline TokenType reservedLetterType(String letter) {
        if (letter == "var") {
            return TokenType::KeywordVar;
        } else if (letter == "func") {
            return TokenType::KeywordFunc;
        }

        return TokenType::Unknown;
    }

    GS_Lexer::GS_Lexer(Reader::GS_TextStream textStream)
            : _textStream(textStream), _line(1), _column(0) {}

    GS_Token GS_Lexer::getToken() {
        auto symbol = _getSymbol();

        if (symbol == eof()) {
            return {TokenType::EndOfFile, {_line, _column}};
        }

        if (symbol == '\n') {
            return {TokenType::NewLine, {_line, _column}};
        }

        if (symbol == ' ') {
            return {TokenType::SymbolSpace, {_line, _column}};
        }

        auto symbolType = reservedSymbolType(symbol);

        if (symbolType != TokenType::Unknown) {
            return {symbolType, {_line, _column}};
        }

        if (std::isalpha(symbol)) {
            String value;

            value += symbol;

            symbol = _getSymbol();

            while (std::isalpha(symbol) && symbol != eof() && symbol != ' ' && symbol != '\n') {
                value += symbol;

                symbol = _getSymbol();
            }

            auto letterType = reservedLetterType(value);

            if (letterType != TokenType::Unknown) {
                return {letterType,  value, {_line, _column}};
            }

            return {TokenType::Identifier,  value, {_line, _column}};
        }

        if (std::isdigit(symbol)) {
            String value;

            value += symbol;

            symbol = _getSymbol();

            while (std::isdigit(symbol) && symbol != eof() && symbol != ' ' && symbol != '\n') {
                value += symbol;

                symbol = _getSymbol();
            }

            return {TokenType::LiteralNumber,  value, {_line, _column}};
        }

        return {TokenType::Unknown, {_line, _column}};
    }

    Reader::SymbolT GS_Lexer::_getSymbol() {
        auto symbol = _textStream.getSymbol();

        if (symbol == '\n') {
            ++_line;

            _column = 1;
        }

        ++_column;

        return symbol;
    }

}