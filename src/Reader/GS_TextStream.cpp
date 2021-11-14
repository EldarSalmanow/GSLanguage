#include <GS_TextStream.h>

namespace GSLanguageCompiler::Reader {

    GS_TextStream::GS_TextStream(GS_Reader reader)
            : _reader(reader) {}

    SymbolT GS_TextStream::getSymbol() {
        return _reader.getSymbol();
    }

    GS_TextStream &GS_TextStream::operator>>(SymbolT &symbol) {
        symbol = getSymbol();

        return *this;
    }

}
