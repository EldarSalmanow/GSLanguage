#ifndef GSLANGUAGE_GS_INPUTTEXTANALYZER_H
#define GSLANGUAGE_GS_INPUTTEXTANALYZER_H

#include <Reader/GS_Code.h>

#include <Lexer/GS_Keywords.h>

namespace GSLanguageCompiler::Lexer {

    /**
     * Symbol type
     */
    using SymbolT = CharType;

    /**
     * Special symbol type
     */
    enum class SymbolType {
        NewLine = 10
    };

    /**
     * Analyzing type
     */
    enum class AnalyzingType {
        IsSpace,

        IsNumber,

        IsCharacter
    };

    /**
     * Class for analyzing input data and matching data with language grammar
     */
    class GS_InputTextAnalyzer {
    public:

        /**
         * Default constructor for GS_InputTextAnalyzer
         */
        GS_InputTextAnalyzer();

    public:

        /**
         * Checking symbol type
         * @param symbol Input symbol
         * @param type Symbol type
         * @return Is the symbol suitable for symbol type
         */
        Bool isSymbol(Reader::GS_Symbol symbol, SymbolType type);

        /**
         * Analyzing symbol
         * @param symbol Input symbol
         * @param type Analyzing type
         * @return Is the symbol suitable for analysis
         */
        Bool analyzeSymbol(Reader::GS_Symbol symbol, AnalyzingType type);

        /**
         * Is reserved symbol in grammar
         * @param symbol Input symbol
         * @return Is reserved symbol
         */
        Bool isReserved(Reader::GS_Symbol symbol);

        /**
         * Is reserved string in grammar
         * @param word Input string
         * @return Is reserved string
         */
        Bool isReserved(String &word);

        /**
         * Converting symbol to reserved type
         * @param symbol Input symbol
         * @return Reserved type
         */
        TokenType reservedType(Reader::GS_Symbol symbol);

        /**
         * Converting string to reserved type
         * @param word Input string
         * @return Reserved type
         */
        TokenType reservedType(String &word);

    private:

        /**
         * Reserved words in grammar
         */
        Map<String, TokenType> _reservedWords;

        /**
         * Reserved symbols in grammar
         */
        Map<SymbolT, TokenType> _reservedSymbols;
    };

}

#endif //GSLANGUAGE_GS_INPUTTEXTANALYZER_H
