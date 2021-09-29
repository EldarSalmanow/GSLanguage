#include <GS_Lexer.h>

namespace GSLanguageCompiler::Lexer {

    GS_Lexer::GS_Lexer(Reader::GS_Code code)
            : _codeReader(std::move(code)) {}

    GSTokenArray GS_Lexer::tokenize() {
        GSTokenArray tokens;

        for (; _codeReader.codeIteratorInBounds();) {
            for (; _codeReader.lineIteratorInBounds();) {
                auto symbol = _codeReader.currentSymbol();

                if (GS_InputTextAnalyzer::isSymbol(symbol, SymbolType::NEW_LINE)) {
                    tokens.emplace_back(TokenType::NEW_LINE, _codeReader.currentPosition());

                    _codeReader.nextLine();

                    break;
                } else if (GS_InputTextAnalyzer::analyzeSymbol(symbol, AnalyzingType::IS_SPACE)) {
                    _codeReader.nextSymbol();

                    continue;
                } else if (GS_InputTextAnalyzer::isReserved(symbol)) {
                    tokens.emplace_back(GS_InputTextAnalyzer::reservedType(symbol), _codeReader.currentPosition());

                    _codeReader.nextSymbol();

                    continue;
                } else if (GS_InputTextAnalyzer::analyzeSymbol(symbol, AnalyzingType::IS_CHARACTER)) {
                    String word;

                    for (; GS_InputTextAnalyzer::analyzeSymbol(_codeReader.currentSymbol(), AnalyzingType::IS_CHARACTER)
                           && _codeReader.lineIteratorInBounds(); _codeReader.nextSymbol()) {
                        word += _codeReader.currentSymbol().getSymbol();
                    }

                    if (GS_InputTextAnalyzer::isReserved(word)) {
                        tokens.emplace_back(GS_InputTextAnalyzer::reservedType(word), _codeReader.currentPosition());

                        continue;
                    }

                    tokens.emplace_back(TokenType::WORD, word, _codeReader.currentPosition());

                    continue;
                } else if (GS_InputTextAnalyzer::analyzeSymbol(symbol, AnalyzingType::IS_NUMBER)) {
                    String number;

                    for (; GS_InputTextAnalyzer::analyzeSymbol(_codeReader.currentSymbol(), AnalyzingType::IS_NUMBER)
                           && _codeReader.lineIteratorInBounds(); _codeReader.nextSymbol()) {
                        number += _codeReader.currentSymbol().getSymbol();
                    }

                    tokens.emplace_back(TokenType::LITERAL_NUMBER, number, _codeReader.currentPosition());

                    continue;
                } else {
                    throw std::runtime_error("Invalid symbol!"); // todo replace error to compiler error
                }
            }
        }

        return tokens;
    }

}