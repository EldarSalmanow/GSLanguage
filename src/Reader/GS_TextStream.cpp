#include <GS_TextStream.h>

namespace GSLanguageCompiler::Reader {

    GS_TextStream::GS_TextStream(GS_Reader reader)
            : _reader(reader) {}

    SymbolT GS_TextStream::getSymbol() {
        auto symbol = _reader.getSymbol();

        _reader.nextSymbol();

        return symbol;
    }

    SymbolT GS_TextStream::nextSymbol() {
        return _reader.nextSymbol();
    }

    SymbolT GS_TextStream::prevSymbol() {
        return _reader.prevSymbol();
    }

    GS_TextStream &GS_TextStream::operator>>(SymbolT &symbol) {
        symbol = getSymbol();

        return *this;
    }

}
