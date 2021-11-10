#include <GS_Lexer.h>

namespace GSLanguageCompiler::Lexer {

//    GS_Lexer::GS_Lexer(Reader::GS_Code code)
//            : _codeReader(std::move(code)) {}

    GS_Lexer::GS_Lexer(Reader::GS_TextStream textStream)
            : _textStream(std::move(textStream)) {}

//    GSTokenArray GS_Lexer::tokenize() {
//        GSTokenArray tokens;
//
//        for (; _codeReader.codeIteratorInBounds();) {
//            for (; _codeReader.lineIteratorInBounds();) {
//                auto symbol = _codeReader.currentSymbol();
//
//                if (_textAnalyzer.isSymbol(symbol, SymbolType::NewLine)) {
//                    _codeReader.nextLine();
//
//                    break;
//                } else if (_textAnalyzer.analyzeSymbol(symbol, AnalyzingType::IsSpace)) {
//                    _codeReader.nextSymbol();
//
//                    continue;
//                } else if (_textAnalyzer.isReserved(symbol)) {
//                    tokens.emplace_back(_textAnalyzer.reservedType(symbol), _codeReader.currentPosition());
//
//                    _codeReader.nextSymbol();
//
//                    continue;
//                } else if (_textAnalyzer.analyzeSymbol(symbol, AnalyzingType::IsCharacter)) {
//                    String word;
//
//                    word += _codeReader.currentSymbol().getSymbol();
//
//                    _codeReader.nextSymbol();
//
//                    for (; (_textAnalyzer.analyzeSymbol(_codeReader.currentSymbol(), AnalyzingType::IsCharacter)
//                            || _textAnalyzer.analyzeSymbol(_codeReader.currentSymbol(), AnalyzingType::IsNumber))
//                            && _codeReader.lineIteratorInBounds(); _codeReader.nextSymbol()) {
//                        word += _codeReader.currentSymbol().getSymbol();
//                    }
//
//                    if (_textAnalyzer.isReserved(word)) {
//                        tokens.emplace_back(_textAnalyzer.reservedType(word), _codeReader.currentPosition());
//
//                        continue;
//                    }
//
//                    tokens.emplace_back(TokenType::Identifier, word, _codeReader.currentPosition());
//
//                    continue;
//                } else if (_textAnalyzer.analyzeSymbol(symbol, AnalyzingType::IsNumber)) {
//                    String number;
//
//                    number += _codeReader.currentSymbol().getSymbol();
//
//                    _codeReader.nextSymbol();
//
//                    for (; _textAnalyzer.analyzeSymbol(_codeReader.currentSymbol(), AnalyzingType::IsNumber)
//                           && _codeReader.lineIteratorInBounds(); _codeReader.nextSymbol()) {
//                        number += _codeReader.currentSymbol().getSymbol();
//                    }
//
//                    tokens.emplace_back(TokenType::LiteralNumber, number, _codeReader.currentPosition());
//
//                    continue;
//                } else {
//                    throw std::runtime_error("Invalid symbol!"); // todo replace error to compiler error
//                }
//            }
//        }
//
//        tokens.emplace_back(TokenType::EndOfFile, GS_Position());
//
//        return tokens;
//    }

    New::GSTokenPtr GS_Lexer::getToken() {
        SymbolT symbol;

        _textStream >> symbol;

        if (std::isspace(symbol)) {
            return std::make_shared<New::GS_BaseToken>(New::TokenType::SymbolSpace);
        } else if (std::isdigit(symbol)) {
            String number;



            return std::make_shared<New::GS_TokenWithValue>(New::TokenType::LiteralNumber, number);
        }
    }

}