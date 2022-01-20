#include <GS_Lexer.h>

namespace GSLanguageCompiler::Lexer {

    Vector<std::pair<UString, TokenType>> ReservedWords = {
            {U"var", TokenType::KeywordVar},
            {U"func", TokenType::KeywordFunc}
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

    GS_Lexer::GS_Lexer(Ptr<Reader::GS_TextStream> stream)
            : _stream(stream), _symbol(_stream->getSymbol()) {}

    GSTokenPtr GS_Lexer::getToken() {
        if (_symbol.isWhitespace()) {
            _symbol = _stream->getSymbol();

            return std::make_shared<GS_Token>(TokenType::SymbolSpace);
        }

        if (ReservedSymbolsType(_symbol) != TokenType::Unknown) {
            auto type = ReservedSymbolsType(_symbol);

            _symbol = _stream->getSymbol();

            return std::make_shared<GS_Token>(type);
        }

        if (_symbol.isIDStart()) {
            return _tokenizeWord();
        }

        if (_symbol.isDigit()) {
            return _tokenizeNumber();
        }

        return nullptr;
    }

    GSTokenPtr GS_Lexer::_tokenizeWord() {
        UString string;

        string += _symbol;

        _symbol = _stream->getSymbol();

        while (_symbol.isIDContinue()) {
            string += _symbol;

            _symbol = _stream->getSymbol();
        }

        if (ReservedWordsType(string) != TokenType::Unknown) {
            return std::make_shared<GS_Token>(ReservedWordsType(string));
        }

        return std::make_shared<GS_ValueToken>(TokenType::Identifier, string);
    }

    GSTokenPtr GS_Lexer::_tokenizeNumber() {
        UString string;

        string += _symbol;

        _symbol = _stream->getSymbol();

        while (_symbol.isDigit()) {
            string += _symbol;

            _symbol = _stream->getSymbol();
        }

        return std::make_shared<GS_ValueToken>(TokenType::LiteralNumber, string);
    }

}