#ifndef GSLANGUAGE_GS_INPUTTEXTANALYZER_H
#define GSLANGUAGE_GS_INPUTTEXTANALYZER_H

#include <cctype>

#include <Reader/GS_Code.h>

#include <Lexer/GS_Keywords.h>

namespace GSLanguageCompiler::Lexer {

    enum class SymbolType {
        NEW_LINE = 10
    };

    enum class AnalyzingType {
        IS_SPACE,

        IS_NUMBER,

        IS_CHARACTER
    };

    class GS_InputTextAnalyzer {
    public:

        GS_InputTextAnalyzer() = default;

    public:

        static Bool isSymbol(Reader::GS_Symbol symbol, SymbolType type) {
            return static_cast<I32>(symbol.getSymbol()) == static_cast<I32>(type);
        }

        static Bool analyzeSymbol(Reader::GS_Symbol symbol, AnalyzingType type) {
            auto charSymbol = symbol.getSymbol();

            switch (type) {
                case AnalyzingType::IS_SPACE:
                    return std::isspace(charSymbol);
                case AnalyzingType::IS_NUMBER:
                    return std::isdigit(charSymbol);
                case AnalyzingType::IS_CHARACTER:
                    return std::isalpha(charSymbol);
                default:
                    return false;
            }
        }

        static Bool isReserved(Reader::GS_Symbol symbol) {
            return reservedSymbols.find(symbol.getSymbol()) != reservedSymbols.end();
        }

        static Bool isReserved(StringRef word) {
            return reservedWords.find(word) != reservedWords.end();
        }

        static TokenType reservedType(Reader::GS_Symbol symbol) {
            return reservedSymbols[symbol.getSymbol()];
        }

        static TokenType reservedType(StringRef word) {
            return reservedWords[word];
        }
    };

}

#endif //GSLANGUAGE_GS_INPUTTEXTANALYZER_H
