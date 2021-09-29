#ifndef GSLANGUAGE_GS_CODEREADER_H
#define GSLANGUAGE_GS_CODEREADER_H

#include <Reader/GS_Code.h>

#include <Lexer/GS_Token.h>

namespace GSLanguageCompiler::Lexer {

    using IndexT = U64;

    class GS_CodeReader {
    public:

        explicit GS_CodeReader(Reader::GS_Code code)
                : _code(std::move(code)), _codeIterator(_code.getStartIterator()), _lineIterator(_codeIterator[0].getStartIterator()) {}

    public:

        Reader::GS_Line currentLine() {
            return _codeIterator[0];
        }

        Reader::GS_Symbol currentSymbol() {
            return _lineIterator[0];
        }

        GS_Position currentPosition() {
            return {currentLine().getLineAsString(), getLineNumber(), getColumnNumber()};
        }

        Void nextLine() {
            ++_codeIterator;

            if (!codeIteratorInBounds()) {
                return;
            }

            _lineIterator = _codeIterator[0].getStartIterator();
        }

        Void nextSymbol() {
            ++_lineIterator;

            if (!lineIteratorInBounds()) {
                return;
            }
        }

        Void prevSymbol() {
            --_lineIterator;
        }

        Bool codeIteratorInBounds() {
            return _codeIterator != _code.getEndIterator();
        }

        Bool lineIteratorInBounds() {
            return _lineIterator != _codeIterator[0].getEndIterator();
        }

        IndexT getLineNumber() {
            return currentSymbol().getLine();
        }

        IndexT getColumnNumber() {
            return currentSymbol().getColumn();
        }

    private:

        Reader::GS_Code _code;

        VectorIterator<Reader::GS_Line> _codeIterator;

        VectorIterator<Reader::GS_Symbol> _lineIterator;
    };

}

#endif //GSLANGUAGE_GS_CODEREADER_H
