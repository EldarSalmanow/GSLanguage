#include <GS_Code.h>

namespace GSLanguageCompiler::Reader {

    GS_Symbol::GS_Symbol(SymbolT symbol, IndexT line, IndexT column)
            : _symbol(symbol), _line(line), _column(column) {}

    SymbolT GS_Symbol::getSymbol() {
        return _symbol;
    }

    IndexT GS_Symbol::getLine() {
        return _line;
    }

    IndexT GS_Symbol::getColumn() {
        return _column;
    }

    GS_Line::GS_Line(Vector<GS_Symbol> symbols)
            : _symbols(std::move(symbols)) {}

    GS_Symbol GS_Line::getSymbol(IndexT index) {
        return _symbols[index];
    }

    VectorIterator<GS_Symbol> GS_Line::getStartIterator() {
        return _symbols.begin();
    }

    VectorIterator<GS_Symbol> GS_Line::getEndIterator() {
        return _symbols.end();
    }

    VectorIterator<GS_Symbol> GS_Line::begin() {
        return getStartIterator();
    }

    VectorIterator<GS_Symbol> GS_Line::end() {
        return getEndIterator();
    }

    String GS_Line::getLineAsString() {
        String string;

        for (auto &symbol : _symbols) {
            string += symbol.getSymbol();
        }

        return string;
    }

    GS_Code::GS_Code(Vector<GS_Line> lines)
            : _lines(std::move(lines)) {}

    GS_Line GS_Code::getLine(IndexT index) {
        return _lines[index];
    }

    VectorIterator<GS_Line> GS_Code::getStartIterator() {
        return _lines.begin();
    }

    VectorIterator<GS_Line> GS_Code::getEndIterator() {
        return _lines.end();
    }

    VectorIterator<GS_Line> GS_Code::begin() {
        return getStartIterator();
    }

    VectorIterator<GS_Line> GS_Code::end() {
        return getEndIterator();
    }

    GS_TextStream::GS_TextStream(std::stringstream stream)
            : _sources(std::move(stream)) {}

    Void GS_TextStream::operator>>(SymbolT &symbol) {
        _sources >> symbol;
    }

}
