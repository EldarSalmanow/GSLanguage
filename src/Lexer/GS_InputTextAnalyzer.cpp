#include <GS_InputTextAnalyzer.h>

namespace GSLanguageCompiler::Lexer {

    GS_InputTextAnalyzer::GS_InputTextAnalyzer() {
        _reservedWords.emplace("var",   TokenType::KeywordVar);
        _reservedWords.emplace("func",  TokenType::KeywordFunc);

        _reservedSymbols.emplace('(',   TokenType::SymbolLeftParen);
        _reservedSymbols.emplace(')',   TokenType::SymbolRightParen);
        _reservedSymbols.emplace('{',   TokenType::SymbolLeftBrace);
        _reservedSymbols.emplace('}',   TokenType::SymbolRightBrace);
        _reservedSymbols.emplace('\"',  TokenType::SymbolDoubleQuotes);
        _reservedSymbols.emplace(':',   TokenType::SymbolColon);
        _reservedSymbols.emplace(',',   TokenType::SymbolComma);
        _reservedSymbols.emplace('+',   TokenType::SymbolPlus);
        _reservedSymbols.emplace('-',   TokenType::SymbolMinus);
        _reservedSymbols.emplace('*',   TokenType::SymbolStar);
        _reservedSymbols.emplace('/',   TokenType::SymbolSlash);
        _reservedSymbols.emplace('=',   TokenType::SymbolEq);
    }

    Bool GS_InputTextAnalyzer::isSymbol(Reader::GS_Symbol symbol, SymbolType type) {
        return static_cast<I32>(symbol.getSymbol()) == static_cast<I32>(type);
    }

    Bool GS_InputTextAnalyzer::analyzeSymbol(Reader::GS_Symbol symbol, AnalyzingType type) {
        auto charSymbol = symbol.getSymbol();

        switch (type) {
            case AnalyzingType::IsSpace:
                return std::isspace(charSymbol);
            case AnalyzingType::IsNumber:
                return std::isdigit(charSymbol);
            case AnalyzingType::IsCharacter:
                return std::isalpha(charSymbol);
            default:
                return false;
        }
    }

    Bool GS_InputTextAnalyzer::isReserved(Reader::GS_Symbol symbol) {
        return _reservedSymbols.find(symbol.getSymbol()) != _reservedSymbols.end();
    }

    Bool GS_InputTextAnalyzer::isReserved(String &word) {
        return _reservedWords.find(word) != _reservedWords.end();
    }

    TokenType GS_InputTextAnalyzer::reservedType(Reader::GS_Symbol symbol) {
        return _reservedSymbols[symbol.getSymbol()];
    }

    TokenType GS_InputTextAnalyzer::reservedType(String &word) {
        return _reservedWords[word];
    }

}
