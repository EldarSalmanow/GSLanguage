#include <GS_InputTextAnalyzer.h>

namespace GSLanguageCompiler::Lexer {

    GS_InputTextAnalyzer::GS_InputTextAnalyzer() {
        _reservedWords.insert(std::make_pair("var",   TokenType::KeywordVar));
        _reservedWords.insert(std::make_pair("func",  TokenType::KeywordFunc));

        _reservedSymbols.insert(std::make_pair('(',   TokenType::SymbolLeftParen));
        _reservedSymbols.insert(std::make_pair(')',   TokenType::SymbolRightParen));
        _reservedSymbols.insert(std::make_pair('{',   TokenType::SymbolLeftBrace));
        _reservedSymbols.insert(std::make_pair('}',   TokenType::SymbolRightBrace));
        _reservedSymbols.insert(std::make_pair('\"',  TokenType::SymbolDoubleQuotes));
        _reservedSymbols.insert(std::make_pair(':',   TokenType::SymbolColon));
        _reservedSymbols.insert(std::make_pair(',',   TokenType::SymbolComma));
        _reservedSymbols.insert(std::make_pair('+',   TokenType::SymbolPlus));
        _reservedSymbols.insert(std::make_pair('-',   TokenType::SymbolMinus));
        _reservedSymbols.insert(std::make_pair('*',   TokenType::SymbolStar));
        _reservedSymbols.insert(std::make_pair('/',   TokenType::SymbolSlash));
        _reservedSymbols.insert(std::make_pair('=',   TokenType::SymbolEq));
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
