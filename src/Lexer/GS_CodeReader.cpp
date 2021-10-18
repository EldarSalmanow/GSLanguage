#include <GS_CodeReader.h>

namespace GSLanguageCompiler::Lexer {

    GS_CodeReader::GS_CodeReader(Reader::GS_Code code)
            : _code(std::move(code)), _codeIterator(_code.getStartIterator()), _lineIterator(_codeIterator[0].getStartIterator()) {}

    Reader::GS_Line GS_CodeReader::currentLine() {
        return _codeIterator[0];
    }

    Reader::GS_Symbol GS_CodeReader::currentSymbol() {
        return _lineIterator[0];
    }

    GS_Position GS_CodeReader::currentPosition() {
        return {currentLine().getLineAsString(), getLineNumber(), getColumnNumber()};
    }

    Void GS_CodeReader::nextLine() {
        ++_codeIterator;

        if (!codeIteratorInBounds()) {
            return;
        }

        _lineIterator = _codeIterator[0].getStartIterator();
    }

    Void GS_CodeReader::nextSymbol() {
        ++_lineIterator;

        if (!lineIteratorInBounds()) {
            return;
        }
    }

    Void GS_CodeReader::prevSymbol() {
        --_lineIterator;
    }

    Bool GS_CodeReader::codeIteratorInBounds() {
        return _codeIterator != _code.getEndIterator();
    }

    Bool GS_CodeReader::lineIteratorInBounds() {
        return _lineIterator != _codeIterator[0].getEndIterator();
    }

    IndexT GS_CodeReader::getLineNumber() {
        return currentSymbol().getLine();
    }

    IndexT GS_CodeReader::getColumnNumber() {
        return currentSymbol().getColumn();
    }

}
